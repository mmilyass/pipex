/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_rest.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imeftah- <imeftah-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 11:08:30 by imeftah-          #+#    #+#             */
/*   Updated: 2025/02/15 15:24:17 by imeftah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	clean_up(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	if (!data)
		return ;
	if (data->command)
	{
		while (data->command[i])
		{
			j = 0;
			while (data->command[i][j])
				free(data->command[i][j++]);
			free(data->command[i]);
			i++;
		}
		free(data->command);
	}
	if (data->buffer_hdoc)
		free(data->buffer_hdoc);
	if (data->random_file)
		free(data->random_file);
	free(data);
}

char	*read_from_stdin(t_data *data)
{
	char	*buffer;
	char	*holder;
	char	*tmp_holder;

	holder = calloc(1, sizeof(char));
	if (holder == NULL)
		other_error(data);
	while (1)
	{
		buffer = get_next_line(0);
		if (buffer == NULL)
			return (free(holder), NULL);
		if (ft_strcmp(buffer, data->argv[2]) != 0)
		{
			tmp_holder = ft_strjoin(holder, buffer);
			free(holder);
			free(buffer);
			if (tmp_holder == NULL)
				return (NULL);
			holder = tmp_holder;
		}
		else
			break ;
	}
	return (free(buffer), holder);
}

void	check_herdoc(t_data *data, char *argument)
{
	int	check;

	check = ft_strcmp(argument, "here_doc");
	if (check == 0)
		data->here_doc = 'y';
	else
		return ;
}

void	close_files(t_data *data)
{
	if (data->fd_infile)
		close(data->fd_infile);
	if (data->fd_ran_file)
		close(data->fd_ran_file);
	close(data->fd_outfile);
	close(data->other_pipe);
}
