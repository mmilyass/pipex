/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imeftah- <imeftah-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 11:50:59 by safae             #+#    #+#             */
/*   Updated: 2025/02/17 12:07:49 by imeftah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

char	**return_line_path_splited(char **envp)
{
	int		i;
	char	**hold_env;

	i = 0;
	while (envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			break ;
		i++;
	}
	hold_env = ft_split(envp[i] + 5, ':');
	if (hold_env == NULL)
		return (NULL);
	return (hold_env);
}

int	access_return(t_data *data, char *path)
{
	if (access(path, F_OK) == -1)
		return (127);
	else if (access(path, X_OK) == -1)
		return (126);
	else if (access(path, X_OK && F_OK) == 0)
	{
		data->path = path;
		return (0);
	}
	return (0);
}

int	check_here_and_slash(t_data *data, char *name)
{
	int	code;
	int	check;
	int	i;

	i = 0;
	check = 0;
	while (name[i])
	{
		if (name[i] == '/')
			check = -1;
		i++;
	}
	if (check == -1)
	{
		code = access_return(data, name);
		return (code);
	}
	return (-1);
}

int	check_path(char *name, char **envp, t_data *data)
{
	char	**paths_array;
	char	*holder;
	int		code;
	int		i;

	i = 0;
	code = check_here_and_slash(data, name);
	if (code != -1)
		return (code);
	paths_array = return_line_path_splited(envp);
	if (paths_array == NULL)
		other_error(data, NULL);
	while (paths_array[i])
	{
		holder = generate_path(paths_array[i], name);
		if (holder == NULL)
			return (free_array(paths_array), -1);
		code = access_return(data, holder);
		if (code == 0)
			return (0);
		free(holder);
		i++;
	}
	return (free_array(paths_array), code);
}
/*
what do this file is that he take the program's name
that the user enter it enter it after the "infile"
and see whether it is existed in a certain path in "PATH"
and if it find it and find that it is executable with
access(void) "F_OK && X_OK"
it take the path that it find it in and put it in "data->path"
that with it i will run the "execve"
and if an error happen of the file is not found or not excutable
i return the error code to print it r
*/