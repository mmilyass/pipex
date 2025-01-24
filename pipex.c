#include "pipex.h"

void    write_end_pipe(int fd, int fd2, char **first_cmd, t_data *data)
{
    int check;
    check = dup2(fd, STDOUT_FILENO);
    check = dup2(fd2, STDIN_FILENO);
    close(fd);
    int s = execve(data->path, first_cmd, NULL);
}

int main(int argc, char **argv, char **envp) 
{
    if (argc == 5)
    {
        t_data *data;
        data = initialize_data(argv);
        if (data == NULL)
            return(0);
        data->id_fork = fork();
        if (data->id_fork < 0)
            return(printf("%s\n",strerror(errno)), 0);
        if (data->id_fork == 0)
        {
            close(data->fd_pipe[0]);            
            int h = check_path(data->first_cmd[0], envp, data);
            if (h == -1)
                return(0);
            write_end_pipe(data->fd_pipe[1], data->fd_infile, data->first_cmd, data);
        }
        else
        {
            wait(NULL);
            printf("this will be printed \n");
            // data->read_end = read_end_pipe(data->fd_pipe[0]);
            // if (data->read_end == NULL)
            //     return(strerror(errno), 0);
            // printf("%s",data->read_end);
        }
    }
    


















// char    *read_end_pipe(int fd)
// {
//     char *buffer;
//     char *holder;
//     char *tmp_holder;
//     int b_read = 1;

//     holder = malloc(1);
//     hol-fsanitize=address -g3der[0] = '\0';
//     while(b_read == 1)
//     {
//         buffer = malloc(2);
//         if (buffer == NULL)
//             return (NULL);
//         b_read = read(fd, buffer, 1);
//         printf("%d\n",b_read);
//         if (b_read == 0)
//         {
//         printf("ilyass\n");
//             free(buffer);
//             break;
//         }
//         if(b_read < 0)
//             return(free(buffer), NULL);
//         buffer[b_read] = '\0';
//         tmp_holder = ft_strjoin(holder, buffer);
//         if (tmp_holder == NULL)
//             return(free(buffer), free(holder), NULL);
//         free(holder);
//         holder = tmp_holder;
//         free(buffer);
//     }
//     return(holder);
// }
}