/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_message.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imeftah- <imeftah-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 10:16:15 by imeftah-          #+#    #+#             */
/*   Updated: 2025/02/15 10:30:02 by imeftah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	check_write(t_data *data, int check)
{
	if (check == -1)
		other_error(data);
}

void	execve_error(t_data *data, char *cmd)
{
	int	check;

	check = write(2, "zsh: command not found: ", 25);
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
		check = write(2, "zsh: permission denied: ", 25);
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
		check = write(2, "zsh: command not found: ", 25);
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

void	other_error(t_data *data)
{
	if (errno == 0)
	{
		clean_up(data);
		exit(0);
	}
	perror("zsh");
	clean_up(data);
	exit(1);
}

/*
this file is responsible for each error will be printer
i handle (permission denied, no such file or dire, and other files)
and i handle too the	exit(status) by returning the right one
*/