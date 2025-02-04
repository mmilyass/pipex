/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imeftah- <imeftah-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 10:10:12 by imeftah-          #+#    #+#             */
/*   Updated: 2025/02/04 11:48:23 by imeftah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
#define PIPEX_H
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <sys/wait.h>

typedef struct s_data
{
    char **first_cmd;
    char **sec_cmd;
    char *read_end;
    char *tmp_file;
    char *path;
    int fd_pipe[2];
    int fd_infile;
    int fd_outfile;
    int fd_tmp_file;
    int id_fork;
}   t_data;
char	**ft_split(char *s1, char c);
int	ft_strlen(char *str);
char	*ft_strdup(char *string);
char	*ft_strjoin(char *s1, char *s2);
int	ft_strncmp(char *s1, char *s2, unsigned int n);
int check_path(char *name, char **envp, t_data *data);
t_data  *initialize_data(char **argv);
void    clean_up(t_data *data);
void    print_error(t_data *data, int err_no, char *str);

#endif