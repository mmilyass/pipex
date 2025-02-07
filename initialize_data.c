#include "pipex.h"

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
void print_error(t_data *data, int err_no, char *str)
{
    if (str == NULL)
    {
        printf("%s\n", strerror(err_no));
        clean_up(data);
        exit(-1);
    }
    else
    {
        printf("%s: %s\n", str, strerror(err_no));
        clean_up(data);
        exit(-1);
    }
}

void clean_up(t_data *data)
{
    int i;
    int j;

    i = 0;
    if (!data)
        return;
    if (data->command)
    {
        while (data->command[i])
        {
            j = 0;
            while (data->command[i][j])
            {
                free(data->command[i][j]);
                j++;
            }
            free(data->command[i]);
            i++;
        }
    }
    free(data);
}

t_data *initialize_args(t_data *data, char **argv, int argc)
{
    int i;
    i = 0;
    data->fd_outfile = open(argv[argc - 1], O_RDWR | O_CREAT | O_TRUNC, 0777); // open the outfile with o_create to creat it and with trunc to clear it
    if (data->fd_outfile < 0)
        other_error(data);
    data->fd_infile = open(argv[1], O_RDONLY); // open the infile for take the input
    if (data->fd_infile < 0)
        other_error(data);
    data->command = malloc((argc - 2) * sizeof(char **));
    if (data->command == NULL)
        other_error(data);
    while (i < argc - 3)
    {
        data->command[i] = ft_split(argv[i + 2], ' ');
        if (data->command[i] == NULL)
            other_error(data);
        i++;
    }
    data->command[i] = NULL;
    return (data);
}

t_data *initialize_data(int argc, char **argv)
{
    t_data *data;
    int check;
    data = ft_calloc(1, sizeof(t_data)); // initialize the struct
    if (data == NULL)
        return (NULL);
    data = initialize_args(data, argv, argc);
    return (data);
}
