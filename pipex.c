#include "pipex.h"

void     run_cmd(t_data *data, int fd, int fd2, char **cmd, char **envp)
{
    int check;
    int code;

    code = check_path(cmd[0], envp, data);
    if (code == 126 || code == 127)
        access_error(data, code, cmd[0]);
    check = dup2(fd2, STDIN_FILENO);        // redirect the stdin to the file so it will take from it
    if (check < 0)
        other_error(data);
    check = dup2(fd, STDOUT_FILENO);        // redirect the stout to the write end of the pipe
    if (check < 0)
        other_error(data);
    close(fd);
    close(fd2);
    check = execve(data->path, cmd, NULL);    // replace the process with the program in the execve
    if (check < 0)
        execve_error(data, cmd[0]);
    exit(1);
}

void    handle_children(t_data *data, char **envp, int argc, int i)
{
    if(i == 0)
    {
        close(data->pipes[0]);
        run_cmd(data, data->pipes[1], data->fd_infile, data->command[i], envp);
    }
    else if (i == argc - 4)
    {
        close(data->pipes[1]);
        run_cmd(data, data->fd_outfile, data->other_pipe, data->command[i], envp);
    }
    else
    {
        close(data->pipes[0]);
        run_cmd(data, data->pipes[1], data->other_pipe, data->command[i], envp);            
    }
}
int main(int argc, char **argv, char **envp)
{
    if (argc > 4)
    {
        t_data *data;
        int check;
        int i = 0;

        data = initialize_data(argc, argv);
        if (data == NULL)
            other_error(data);
        
        while (i < argc - 3)
        {
            if (i != argc - 4)
            {
                check = pipe(data->pipes);
                if (check < 0)
                    other_error(data);
            }
            data->id_fork = fork();
            if (data->id_fork < 0)
                other_error(data);

            if (data->id_fork == 0)
            {
                handle_children(data, envp, argc, i);
            }
            else
            {
                if (i > 0)
                    close(data->other_pipe);
                data->other_pipe = data->pipes[0];
                close(data->pipes[1]);
            }
            i++;
        }
        close(data->other_pipe);
        close(data->pipes[0]);
        int status;
        int last_status;
        for (int s = 0; s < i; s++) 
        {
            wait(&status);
            if (WIFEXITED(status)) {
                last_status = WEXITSTATUS(status);
            }
        }
        // printf("%d\n", last_status);
        parent_exit(data, last_status);
    }
    else
        printf("you mistakely forgot to enter more that 4 argument !!\n");
}


// i was dividing the main function and what i made today is handling entering a path in the args and i handled the errors what still is the leaks and dividing
// tommorow fix the cleen_up function and learn about the herdoc and what it is and do it and organize the code okey ?

// there is something in this main i need to address is that i wait for all children and then see whether the last one exit with an error if yes i exit in the standart error with -
// - error that it happened and this is what you see in the last while loop in the main function.
// another thing is that i see each child and it exit status to make sure the message will be correct and i handle the message in the (error_message.c) file you can go and see it
// another thing is 