/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_files_open_close.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imeftah- <imeftah-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 10:59:33 by imeftah-          #+#    #+#             */
/*   Updated: 2025/02/18 10:20:17 by imeftah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	open_outfile(t_data *data)
{
	if (data->here_doc == YES)
		data->fd_outfile = open(data->argv[data->argc],
				O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		data->fd_outfile = open(data->argv[data->argc - 1],
				O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (data->fd_outfile == -1)
		other_error(data, data->argv[data->argc - 1]);
}

void	open_infile(t_data *data)
{
	data->fd_infile = open(data->argv[1], O_RDONLY);
	if (data->fd_infile == -1)
		other_error(data, data->argv[1]);
}

void	open_unlink_ran_file(t_data *data)
{
	data->fd_ran_file = open(data->random_file, O_RDONLY);
	if (data->fd_ran_file == -1)
		other_error(data, data->random_file);
	if (unlink(data->random_file) == -1)
		other_error(data, NULL);
}
