/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imeftah- <imeftah-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 10:10:12 by imeftah-          #+#    #+#             */
/*   Updated: 2025/02/18 11:01:33 by imeftah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# define YES 'Y'
# define NO 'N'
# include "./ft_printf/ft_printf.h"
# include "./libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_data
{
	char	***command;
	char	**argv;
	char	**envp;
	char	*buffer_hdoc;
	char	*random_file;
	char	*path;
	char	here_doc;
	int		*pids;
	int		pipes[2];
	int		other_pipe;
	int		fd_infile;
	int		fd_outfile;
	int		fd_ran_file;
	int		argc;
	int		id_fork;
}			t_data;

int			check_path(char *name, char **envp, t_data *data);
char		**ft_split(char *s1, char c);
t_data		*initialize_data(int argc, char **argv, char **envp);
void		clean_up(t_data *data);
void		execve_error(t_data *data, char *cmd);
void		access_error(t_data *data, int err_code, char *cmd);
void		parent_exit(t_data *data, int err_code);
void		other_error(t_data *data, char *name);
void		initialize_with_hdoc(t_data *data);
void		initialize_args(t_data *data);
void		check_herdoc(t_data *data, char *argument);
void		read_from_stdin(t_data *data);
char		*get_next_line(int fd);
void		close_files(t_data *data);
char		*generate_path(char *str, char *name);
void		my_touch(t_data *data);
void		open_outfile(t_data *data);
void		open_infile(t_data *data);
void		open_unlink_ran_file(t_data *data);

#endif
