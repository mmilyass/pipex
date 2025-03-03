/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_touch.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imeftah- <imeftah-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 10:49:46 by imeftah-          #+#    #+#             */
/*   Updated: 2025/02/19 11:08:21 by imeftah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	my_touch(t_data *data)
{
	int		check;
	int		id;
	char	*name[2];

	name[0] = "cat";
	name[1] = NULL;
	id = fork();
	if (id == 0)
	{
		open_outfile(data);
		open_unlink_ran_file(data);
		check = dup2(data->fd_outfile, STDOUT_FILENO);
		if (check == -1)
			other_error(data, NULL);
		check = dup2(data->fd_ran_file, STDIN_FILENO);
		if (check == -1)
			other_error(data, NULL);
		close(data->fd_outfile);
		close(data->fd_ran_file);
		check = execve("/usr/bin/cat", name, NULL);
		if (check == -1)
			other_error(data, NULL);
		exit(0);
	}
	wait(&check);
}
