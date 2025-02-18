/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imeftah- <imeftah-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 10:57:22 by imeftah-          #+#    #+#             */
/*   Updated: 2025/02/18 10:54:19 by imeftah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	wait_children(t_data *data)
{
	int	i;
	int	status;
	int	last_status;
	int	check;

	i = 0;
	last_status = 0;
	while (i < data->argc - 3)
	{
		check = waitpid(data->pids[i], &status, 0);
		if (check == -1)
			other_error(data, NULL);
		if (WIFEXITED(status))
			last_status = WEXITSTATUS(status);
		i++;
	}
	return (last_status);
}

void	run_cmd(t_data *data, int outfile, int infile, char **cmd)
{
	int	check;
	int	code;

	if (data->argc == 4)
	{
		outfile = data->fd_outfile;
	}
	if (cmd[0] == NULL)
		other_error(data, cmd[0]);
	code = check_path(cmd[0], data->envp, data);
	if (code != 0)
		access_error(data, code, cmd[0]);
	check = dup2(infile, STDIN_FILENO);
	if (check < 0)
		other_error(data, cmd[0]);
	check = dup2(outfile, STDOUT_FILENO);
	if (check < 0)
		other_error(data, NULL);
	close(outfile);
	close(infile);
	check = execve(data->path, cmd, NULL);
	if (check < 0)
		execve_error(data, cmd[0]);
	exit(1);
}

void	handle_children(t_data *data, int i)
{
	if (i == 0 && data->here_doc == YES)
	{
		close(data->pipes[0]);
		open_unlink_ran_file(data);
		run_cmd(data, data->pipes[1], data->fd_ran_file, data->command[i]);
	}
	else if (i == 0 && data->here_doc != YES)
	{
		close(data->pipes[0]);
		open_infile(data);
		run_cmd(data, data->pipes[1], data->fd_infile, data->command[i]);
	}
	else if (i == data->argc - 4)
	{
		open_outfile(data);
		run_cmd(data, data->fd_outfile, data->other_pipe, data->command[i]);
	}
	close(data->pipes[0]);
	run_cmd(data, data->pipes[1], data->other_pipe, data->command[i]);
}

void	still_process(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->argc - 3)
	{
		if (i != data->argc - 4)
		{
			if (pipe(data->pipes) < 0)
				other_error(data, NULL);
		}
		data->id_fork = fork();
		if (data->id_fork < 0)
			other_error(data, NULL);
		if (data->id_fork == 0)
			handle_children(data, i);
		else
		{
			data->pids[i] = data->id_fork;
			if (i++ > 0)
				close(data->other_pipe);
			data->other_pipe = data->pipes[0];
			if (data->argc != 4)
				close(data->pipes[1]);
		}
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_data	*data;
	int		last_status;

	if (argc > 3)
	{
		data = initialize_data(argc, argv, envp);
		if (data == NULL)
			other_error(data, NULL);
		check_herdoc(data, argv[1]);
		if (data->here_doc == YES)
		{
			initialize_with_hdoc(data);
			data->fd_ran_file = open(data->random_file, O_RDWR);
			if (argc == 4)
				my_touch(data);
		}
		else
			initialize_args(data);
		still_process(data);
		last_status = wait_children(data);
		parent_exit(data, last_status);
	}
	else if (argc <= 3)
		perror("you enter less than 4 arguments");
}
/*
-> this is the main part and in it i have the importent functions.
and my concept in this project that i firts see whether the user
enter more that 4 argument because this is mandatory and if not
i sent the message you see at the end and dont do anything
and if here enter the code argument i initialize the data
with the function "init_data" and then i check whether
the first argument is "here_doc" if yes i put in a var
"data->here_doc = 'y" and then i check if the "data->here_doc"
to initilize the argument and open files diffrnetly and this
is what you can see in the "init_args_hdoc" and then call
the "still_process"  and in it i handel the children
//
-> i wanna explain how i work with pipes. and how i hanle them
https://excalidraw.com/#json=sBKGLHdLQNGZGwjK0apyW,94J5l5nWEwsJixyZhi0KVA
//
-> i handled also when the infile is not exist and there is a valid command,
it should show off .
-> and i handle when there is one command only or no command in the here_doc
*/