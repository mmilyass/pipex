#include "pipex.h"

void    initialize_args(t_data *data)
{
    int i;
    i = 0;
    data->fd_outfile = open(data->argv[data->argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0777); // open the outfile with o_create to creat it and with trunc to clear it
    if (data->fd_outfile < 0)
        other_error(data);
    data->fd_infile = open(data->argv[1], O_RDONLY); // open the infile for take the input
    if (data->fd_infile < 0)
        other_error(data);
    data->command = malloc((data->argc - 2) * sizeof(char **));
    if (data->command == NULL)
        other_error(data);
    while (i < data->argc - 3)
    {
        data->command[i] = ft_split(data->argv[i + 2], ' ');
        if (data->command[i] == NULL)
            other_error(data);
        i++;
    }
    data->command[i] = NULL;
}

void    generate_file(t_data *data)
{
    int i;
    char *holder;
    holder = ft_itoa((unsigned long long)&i);
    if (holder == NULL)
        other_error(data);
    data->random_file = ft_strjoin("/tmp/", holder);
    free(holder);
    if (data->random_file == NULL)
        other_error(data);
    data->fd_ran_file = open(data->random_file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
    if (data->fd_ran_file < 0)
        other_error(data);
}

void    initialize_with_hdoc(t_data *data)
{
    int i;

    i = 0;
    data->fd_outfile = open(data->argv[data->argc - 1], O_WRONLY | O_CREAT, 0777); // open the outfile with o_create to creat it and without trunc cause need to read under
    if (data->fd_outfile < 0)
        other_error(data);
    generate_file(data);                    // this is the file tha it will take the input from the here_doc
    data->command = malloc((data->argc - 3) * sizeof(char **));   // -4 for (executable, here_doc, dili, outfile) and +1 to make a NULL at the end so -3
    if (data->command == NULL)
        other_error(data);
    while (i < data->argc - 4)          // -4 to put only cmds 
    {
        data->command[i] = ft_split(data->argv[i + 3], ' ');   // start from the third param so there where the first cmd is
        if (data->command[i] == NULL)
            other_error(data);
        i++;
    }
    data->command[i] = NULL;
    data->buffer_hdoc = read_from_stdin(data);
    if (!data->buffer_hdoc)
        other_error(data);
    i = write(data->fd_ran_file, data->buffer_hdoc, ft_strlen(data->buffer_hdoc));
    if (i < 0)
        other_error(data);
    data->argc -= 1;        // you may wonder about this i did it for the same as the -4 above to evitate the 3 first args and the last 
}

t_data *initialize_data(int argc, char **argv, char **envp)
{
    t_data *data;
    data = ft_calloc(1, sizeof(t_data)); // initialize the struct
    if (data == NULL)
        return (NULL);
    data->argc = argc;
    data->argv = argv;
    data->envp = envp;
    return (data);
}
