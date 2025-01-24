/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: safae <safae@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 10:10:12 by imeftah-          #+#    #+#             */
/*   Updated: 2025/01/24 16:01:24 by safae            ###   ########.fr       */
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
    char *path;
    int fd_pipe[2];
    int fd_infile;
    int fd_outfile;
    int id_fork;
}   t_data;
char	**ft_split(char *s1, char c);
int	ft_strlen(char *str);
char	*ft_strdup(char *string);
char	*ft_strjoin(char *s1, char *s2);
int	ft_strncmp(char *s1, char *s2, unsigned int n);
int check_path(char *name, char **envp, t_data *data);
t_data  *initialize_data(char **argv);

#endif