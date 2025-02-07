#include "pipex.h"

void    check_write(t_data *data, int check)
{
    if (check == -1)
        other_error(data);
}
void    execve_error(t_data *data, char *cmd)
{
    int check;
    check = write(2, "zsh: command not found: ",25);
    check_write(data, check);
    check = write(2, cmd ,ft_strlen(cmd));
    check_write(data, check);
    check = write(2, "\n", 1);
    check_write(data, check);
    clean_up(data);
    exit(127);
}

void    access_error(t_data *data, int err_code, char *cmd)
{
    int check;

    if(err_code == 126)
    {
        check = write(2, "zsh: permission denied: ", 25);
        check_write(data, check);
        check = write(2, cmd, ft_strlen(cmd));
        check_write(data, check);
        check = write(2, "\n", 1);
        check_write(data, check);
        clean_up(data);
        exit(126);
    }
    if(err_code == 127)
    {
        check = write(2, "zsh: command not found: ", 25);
        check_write(data, check);
        check = write(2, cmd, ft_strlen(cmd));
        check_write(data, check);
        check = write(2, "\n", 1);
        check_write(data, check);
        clean_up(data);
        exit(127);
    }
}

void    parent_exit(t_data *data, int err_code)
{
    if (err_code == 0)
    {
        clean_up(data);
        exit(0);
    }
    if (err_code != 0)
    {
        clean_up(data);
        exit(1);
    }
}

void    other_error(t_data *data)
{
    perror("zsh");
    clean_up(data);
    exit(2);
}