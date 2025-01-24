#include "pipex.h"

void    write_end_pipe(int fd, int fd2, char **first_cmd)
{
    int check;
    check = dup2(fd, STDOUT_FILENO);
    check = dup2(fd2, STDIN_FILENO);
    if (check < 0)
    {
        printf("Error\ndup2 function fails\n");
        exit(0);
    }
    close(fd);
    execve(ft_strjoin("/bin/",first_cmd[0]), first_cmd, NULL);
}
char    *read_end_pipe(int fd)
{
    char *buffer;
    char *holder;
    char *tmp_holder;
    int b_read = 1;

    holder = malloc(1);
    holder[0] = '\0';
    while(b_read == 1)
    {
        buffer = malloc(2);
        if (buffer == NULL)
            return (NULL);
        b_read = read(fd, buffer, 1);
        printf("%d\n",b_read);
        if (b_read == 0)
        {
        printf("ilyass\n");
            free(buffer);
            break;
        }
        if(b_read < 0)
            return(free(buffer), NULL);
        buffer[b_read] = '\0';
        tmp_holder = ft_strjoin(holder, buffer);
        if (tmp_holder == NULL)
            return(free(buffer), free(holder), NULL);
        free(holder);
        holder = tmp_holder;
        free(buffer);
    }
    return(holder);
}

int main(int argc, char **argv) 
{
    if (argc == 5)
    {
        int fd_pipe[2];
        char **first_cmd;
        char **sec_cmd;
        char *read_end;
        int fd_infile;
        int fd_outfile;
        int check;
        int id;
        fd_infile = open(argv[1], O_RDONLY);
        if (fd_infile < 0)
            return(printf("%s: %s\n",strerror(errno), argv[1]), 0);
        fd_outfile = open(argv[4], O_RDWR | O_CREAT | O_TRUNC, 0777);
        if (fd_outfile < 0)
            return(printf("%s\n",strerror(errno)), 0);
        first_cmd = ft_split(argv[2], ' ');
        if (first_cmd == NULL)
            return(printf("Error\n%s\n",strerror(errno)), 0);
        sec_cmd = ft_split(argv[3], ' ');
        if (sec_cmd == NULL)
            return(printf("%s\n",strerror(errno)), 0);
        check = pipe(fd_pipe);
        if (check < 0)
            return(printf("%s\n",strerror(errno)), 0);
        id = fork();
        if (id < 0)
            return(printf("%s\n",strerror(errno)), 0);
        if (id == 0)
        {
            close(fd_pipe[0]);
            write_end_pipe(fd_pipe[1], fd_infile, first_cmd);
        }
        else
        {
            wait(NULL);
            read_end = read_end_pipe(fd_pipe[0]);
            if (read_end == NULL)
                return(strerror(errno), 0);
            printf("%s",read_end);
        }
    }
}