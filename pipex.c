#include "pipex.h"

int    wait_children(t_data *data)
{
    int i;
    int status;
    int last_status;
    int check;
    
    i = 0;
    last_status = 0;
    while (i < data->argc - 3)
    {
        check = wait(&status);
        if (check == -1)
            other_error(data);
        if(WIFEXITED(status))
            last_status = WEXITSTATUS(status);
        i++;
    }
    return (last_status);
}

void     run_cmd(t_data *data, int outfile, int infile, char **cmd, char **envp)
{
    int check;
    int code;

    code = check_path(cmd[0], envp, data);
    if (code != 0)
        access_error(data, code, cmd[0]);
    check = dup2(infile, STDIN_FILENO);
    if (check < 0)
    {
        other_error(data);
    }
    check = dup2(outfile, STDOUT_FILENO);
    if (check < 0)
        other_error(data);
    close(outfile);
    close(infile);
    check = execve(data->path, cmd, NULL);
    if (check < 0)
        execve_error(data, cmd[0]);
    exit(1);
}

void    handle_children(t_data *data, char **envp, int argc, int i)
{
    if (i == 0 && data->here_doc == 'y')
    {
        close(data->pipes[0]);
        data->fd_ran_file = open(data->random_file, O_RDONLY);
        if (data->fd_ran_file < 0)
            other_error(data);
        if (unlink(data->random_file) == -1)
            other_error(data);
        run_cmd(data, data->pipes[1], data->fd_ran_file, data->command[i], envp);
    }
    if( i == 0 && data->here_doc != 'y')
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

void    still_process(t_data *data)
{
    int i;

    i = 0;
    while (i < data->argc - 3)
    {
        if (i != data->argc - 4)
        {
            if (pipe(data->pipes) < 0)
                other_error(data);
        }
        data->id_fork = fork();
        if (data->id_fork < 0)
            other_error(data);
        if (data->id_fork == 0)
            handle_children(data, data->envp, data->argc, i);
        else
        if (i > 0)
            close(data->other_pipe);
        data->other_pipe = data->pipes[0];
        close(data->pipes[1]);
        data->here_doc = '\0';
        i++;
    }
}

int main(int argc, char **argv, char **envp)
{
    if (argc > 3)
    {
        t_data *data;

        data = initialize_data(argc, argv, envp);    // this only allocate it and those args in theire vars
        if (data == NULL)
            other_error(data);
        check_herdoc(data, argv[1]);                    // this will see whether the first arg is "here_doc"
        if (data->here_doc == 'y')                      // if yes treat it another way in init_with_hdoc();   
            initialize_with_hdoc(data);
        else
            initialize_args(data);
        still_process(data);                        // this function inside it i handle children and the cmds
        int last_status = wait_children(data);
        close_files(data);
        parent_exit(data, last_status);
    }
    else
        printf("you mistakely forgot to enter more that 3 argument !!\n");
}




























/* i fix the here_doc and i did this by checking whether the second argument is like the name "here_doc" if yes 
i put in the data->here_doc the 'y' so when i will inistialize the command and open the files i will do and i am
handling that i will work with the here_doc.doc.
-so what i did i created a file name by taking an address of a variable and then open it with o_creat to create it 
and i put in it what i will read from the stdin till i come across the "dilimeter".
so when i will run the first cmd i will take its input from this file because this is the job of the here_doc 
and then continue normally and you can see this in the handle_children() function
*/

// there is something in this main i need to address is that i wait for all children and then see whether the last one exit with an error if yes i exit in the standart error with -
// - error that it happened and this is what you see in the last while loop in the main function.
// another thing is that i see each child and it exit status to make sure the message will be correct and i handle the message in the (error_message.c) file you can go and see it
// another thing is 


