/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_data.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imeftah- <imeftah-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 10:18:58 by imeftah-          #+#    #+#             */
/*   Updated: 2025/02/18 10:54:42 by imeftah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_data	*initialize_data(int argc, char **argv, char **envp)
{
	t_data	*data;

	data = ft_calloc(1, sizeof(t_data));
	if (data == NULL)
		return (NULL);
	data->argc = argc;
	data->argv = argv;
	data->envp = envp;
	return (data);
}

void	generate_file(t_data *data)
{
	int		i;
	char	*holder;

	holder = ft_itoa((unsigned long long)&i);
	if (holder == NULL)
		other_error(data, NULL);
	data->random_file = ft_strjoin("/tmp/", holder);
	free(holder);
	if (data->random_file == NULL)
		other_error(data, NULL);
	data->fd_ran_file = open(data->random_file, O_RDWR | O_CREAT | O_TRUNC,
			0777);
	if (data->fd_ran_file < 0)
		other_error(data, NULL);
}

char	*generate_path(char *str, char *name)
{
	char	*holder;
	char	*tmp;

	tmp = ft_strjoin(str, "/");
	if (tmp == NULL)
		return (NULL);
	holder = ft_strjoin(tmp, name);
	free(tmp);
	if (holder == NULL)
		return (NULL);
	return (holder);
}

void	initialize_args(t_data *data)
{
	int	i;

	i = 0;
	data->pids = malloc((data->argc - 3) * sizeof(int));
	if (data->pids == NULL)
		other_error(data, NULL);
	data->command = malloc((data->argc - 2) * sizeof(char **));
	if (data->command == NULL)
		other_error(data, NULL);
	while (i < data->argc - 3)
	{
		data->command[i] = ft_split(data->argv[i + 2], ' ');
		if (data->command[i] == NULL)
			other_error(data, NULL);
		i++;
	}
	data->command[i] = NULL;
}

void	initialize_with_hdoc(t_data *data)
{
	int	i;

	i = 0;
	data->pids = malloc((data->argc - 4) * sizeof(int));
	if (data->pids == NULL)
		other_error(data, NULL);
	generate_file(data);
	data->command = malloc((data->argc - 3) * sizeof(char **));
	if (data->command == NULL)
		other_error(data, NULL);
	while (i < data->argc - 4)
	{
		data->command[i] = ft_split(data->argv[i + 3], ' ');
		if (data->command[i++] == NULL)
			other_error(data, NULL);
	}
	data->command[i] = NULL;
	read_from_stdin(data);
	data->argc -= 1;
}
