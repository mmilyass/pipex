/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_message.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imeftah- <imeftah-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 10:16:15 by imeftah-          #+#    #+#             */
/*   Updated: 2025/02/18 11:32:41 by imeftah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	check_write(t_data *data, int check)
{
	if (check == -1)
		other_error(data, NULL);
}

void	execve_error(t_data *data, char *cmd)
{
	int	check;

	check = write(2, "./pipex: command not found: ", 25);
	check_write(data, check);
	check = write(2, cmd, ft_strlen(cmd));
	check_write(data, check);
	check = write(2, "\n", 1);
	check_write(data, check);
	clean_up(data);
	exit(127);
}

void	access_error(t_data *data, int err_code, char *cmd)
{
	int	check;

	if (err_code == 126)
	{
		check = write(2, "./pipex: permission denied: ", 25);
		check_write(data, check);
		check = write(2, cmd, ft_strlen(cmd));
		check_write(data, check);
		check = write(2, "\n", 1);
		check_write(data, check);
		clean_up(data);
		exit(126);
	}
	if (err_code == 127)
	{
		check = write(2, "./pipex: command not found: ", 29);
		check_write(data, check);
		check = write(2, cmd, ft_strlen(cmd));
		check_write(data, check);
		check = write(2, "\n", 1);
		check_write(data, check);
		clean_up(data);
		exit(127);
	}
}

void	parent_exit(t_data *data, int err_code)
{
	if (err_code == 0)
	{
		close_files(data);
		clean_up(data);
		exit(0);
	}
	if (err_code != 0)
	{
		close_files(data);
		clean_up(data);
		exit(err_code);
	}
}

void	other_error(t_data *data, char *name)
{
	if (name == NULL)
		ft_printf("./pipex: %s\n", strerror(errno));
	else
		ft_printf("./pipex: %s: %s\n", strerror(errno), name);
	clean_up(data);
	exit(1);
}

/*
this file is responsible for each error will be printer
i handle (permission denied, no such file or dire, and other files)
and i handle too the	exit(status) by returning the right one
*/
