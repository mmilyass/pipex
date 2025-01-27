#include "pipex.h"

void    *run_fcmd_pipe(t_data *data, int fd, int fd2, char **first_cmd)
{
    int check;
    check = dup2(fd, STDOUT_FILENO);        // redirect the stout to the write end of the pipe
    if (check < 0)
        return(print_error(data, errno, NULL), NULL);
    check = dup2(fd2, STDIN_FILENO);        // redirect the stdin to the file so it will take from it
    if (check < 0)
        return(print_error(data, errno, NULL), NULL);
    close(fd);
    close(fd2);
    check = execve(data->path, first_cmd, NULL);    // replace the process with the program in the execve
    if (check < 0)
        return(print_error(data, errno, data->first_cmd[0]), NULL);

}

void    *run_scmd_pipe(t_data *data, int fd, int fd2, char **sec_cmd)
{
    int check;
    check = dup2(fd2, STDIN_FILENO);            // redirect the stdin to the file to take from it the "tmp_file"
    if (check < 0)
        return(print_error(data, errno, NULL), NULL);
    check = dup2(fd, STDOUT_FILENO);            // redirect the stout to put the output in the file "outfile"
    if (check < 0)
        return(print_error(data, errno, NULL), NULL);
    close(fd2);
    close(fd);
    check = unlink(data->tmp_file);             // remove the "tmp_file" after using it but not closing it mean we can access its content
    if (check < 0)
        return(print_error(data, errno, data->tmp_file), NULL);
    check = execve(data->path, sec_cmd, NULL);  // run the new program that will replace the process
    if (check < 0)
        return(print_error(data, errno, data->sec_cmd[0]), NULL);
}

static  char    *read_end(int fd)   //this function read from the read_end_pipe
{
    char *buffer;
    char *holder;
    char *tmp_holder;
    int size;

    holder = calloc(1,sizeof(char));
    if (holder == NULL)
        return(NULL);
    while(1)
    {
        buffer = calloc(2, sizeof(char));
        if (buffer == NULL)
            return(NULL);
        size = read(fd, buffer, 1);
        if (size == -1)
            return (free(buffer), NULL);
        if (size == 0)
            break;
        tmp_holder = ft_strjoin(holder, buffer);
        free(buffer);
        free(holder);
        holder = tmp_holder;
    }
    return(holder);
}

static  int parent_process(t_data *data, char **envp)
{
    int check;
    wait(NULL);                             // wait for the child process
    close(data->fd_pipe[1]);
    data->read_end = read_end(data->fd_pipe[0]);    // read from the read_end of the pipe
    if(data->read_end == NULL)
        return(clean_up(data), -1);
    write(data->fd_tmp_file,  data->read_end, ft_strlen(data->read_end));   // write the data read from the pipe to "tmp_file"
    data->fd_tmp_file = open(data->tmp_file, O_RDONLY);                     // reopen the file because it will index at the end after write()
    if (data->fd_tmp_file < 0)
        return(clean_up(data), -1);
    check = check_path(data->sec_cmd[0], envp, data);                       // check the path of the command in the PATH envp
    if (check == -1)
        return(printf("%s: %s\n", data->sec_cmd[0], "command not found"), clean_up(data),1);
    run_scmd_pipe(data, data->fd_outfile, data->fd_tmp_file,  data->sec_cmd);   //run the second command 
    return(0);
}
int main(int argc, char **argv, char **envp) 
{
    if (argc == 5)
    {
        t_data *data;
        int check;

        data = initialize_data(argv);       // initialize the struct
        if (data == NULL)
            return(1);
        data->id_fork = fork();             // create a child process
        if (data->id_fork < 0)
            return(print_error(data, errno, NULL), 1);
        if (data->id_fork == 0)             // in the child process (fork return 0 mean we are in the child process)
        {
            close(data->fd_pipe[0]);        // close the read end we dont need it now            
            check = check_path(data->first_cmd[0], envp, data);     // if it return 0 then it find it in the PATH
            if (check == -1)
                return(printf("%s: %s\n", data->first_cmd[0], "command not found"),clean_up(data),1);
            run_fcmd_pipe(data, data->fd_pipe[1], data->fd_infile, data->first_cmd);   // put the command in the write end of the pipe
        }
        else
        {
            check = parent_process(data, envp);
            if (check == -1)
                return(1);
        }
    }
}
