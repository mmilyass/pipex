#include "pipex.h"

void print_error(t_data *data, int err_no, char *str)
{
    if (str == NULL)
    {
        printf("%s\n", strerror(err_no));
        clean_up(data);
    }
    else
    {
        printf("%s: %s\n", str, strerror(err_no));
        clean_up(data);
    }
}

void clean_up(t_data *data)
{
    int i;

    i = 0;
    if (!data)
        return;
    if (data->first_cmd)
    {
        while (data->first_cmd[i])
        {
            if (data->first_cmd[i])
                free(data->first_cmd[i++]);
        }
        free(data->first_cmd);
    }
    i = 0;
    if (data->sec_cmd)
    {
        while (data->sec_cmd[i])
        {
            if (data->sec_cmd[i])
                free(data->sec_cmd[i++]);
        }
        free(data->sec_cmd);
    }
    if (data->read_end)
        free(data->read_end);
    free(data);
}

t_data *initialize_args(t_data *data, char **argv)
{
    data->fd_outfile = open(argv[4], O_RDWR | O_CREAT | O_TRUNC, 0777); // open the outfile with o_create to creat it and with trunc to clear it
    if (data->fd_outfile < 0)
        return (print_error(data, errno, argv[4]), NULL);
    data->fd_infile = open(argv[1], O_RDONLY); // open the infile for take the input
    if (data->fd_infile < 0)
        return (print_error(data, errno, argv[1]), NULL);
    data->first_cmd = ft_split(argv[2], ' '); // take the first arg and split it to use it as a command
    if (data->first_cmd == NULL)
        return (print_error(data, errno, NULL), NULL);
    data->sec_cmd = ft_split(argv[3], ' '); // do the same thing to the second argument
    if (data->sec_cmd == NULL)
        return (print_error(data, errno, NULL), NULL);
    return (data);
}
void    *ft_calloc(size_t count, size_t size)
{
        char    *ptr;
        size_t  total_size;
        size_t  i;

        total_size = count * size;
        ptr = malloc(total_size);
        if (!ptr)
                return (NULL);
        i = 0;
        while (i < total_size)
        {
                ptr[i] = 0;
                i++;
        }
        return ((void *)ptr);
}
t_data *initialize_data(char **argv)
{
    t_data *data;
    int check;
    data = ft_calloc(1, sizeof(t_data)); // initialize the struct
    if (data == NULL)
        return (NULL);
    data = initialize_args(data, argv);
    if (data == NULL)
        return (NULL);
    check = pipe(data->fd_pipe); // create the pipe for the communication of the two processes
    if (check < 0)
        return (print_error(data, errno, NULL), NULL);
    return (data);
}
