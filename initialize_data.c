#include "pipex.h"

t_data  *initialize_data(char **argv)
{
    t_data *data;
    int check;
    data = malloc(sizeof(t_data));
    data->fd_infile = open(argv[1], O_RDONLY);
    if (data->fd_infile < 0)
        return(printf("%s: %s\n",strerror(errno), argv[1]), NULL);
    data->fd_outfile = open(argv[4], O_RDWR | O_CREAT | O_TRUNC, 0777);
    if (data->fd_outfile < 0)
        return(printf("%s\n",strerror(errno)), NULL);
    data->first_cmd = ft_split(argv[2], ' ');
    if (data->first_cmd == NULL)
        return(printf("%s\n",strerror(errno)), NULL);
    data->sec_cmd = ft_split(argv[3], ' ');
    if (data->sec_cmd == NULL)
        return(printf("%s\n",strerror(errno)), NULL);
    check = pipe(data->fd_pipe);
    if (check < 0)
        return(printf("%s\n",strerror(errno)), NULL);
    return(data);
}
