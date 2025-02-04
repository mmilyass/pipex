/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imeftah- <imeftah-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 11:50:59 by safae             #+#    #+#             */
/*   Updated: 2025/02/03 09:24:56 by imeftah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void free_array(char **array)
{
    int i;

    i = 0;
    while (array[i])
    {
        free(array[i]);
        i++;
    }
    free(array);
}

char **return_line_path_splited(char **envp)
{
    int i;
    char **hold_env;

    i = 0;
    while (envp[i] != NULL)
    {
        if (ft_strncmp(envp[i], "PATH=", 5) == 0)       // Take the line that has the PATH variable
            break;
        i++;
    }
    hold_env = ft_split(envp[i] + 5, ':');              // Split with ':' to get each path, skipping "PATH="
    if (hold_env == NULL)
        return (NULL);
    return (hold_env);
}

int check_path(char *name, char **envp, t_data *data) // this function check the path of the program to be executed 
{
    char **paths_array;
    char *holder;
    char *holder2;
    int i;
    
    i = 0;
    paths_array = return_line_path_splited(envp);
    if(paths_array == NULL)
        return(-1);
    while(paths_array[i])
    {
        holder = ft_strjoin(paths_array[i], "/");
        if (holder == NULL)
            return(free_array(paths_array), -1);
        holder2 = ft_strjoin(holder, name);
        free(holder);
        if (holder2 == NULL)
            return(free_array(paths_array), -1);
        if (access(holder2, F_OK && X_OK) == 0)
        {
            data->path = holder2;
            free_array(paths_array);
            return(0);
        }
        free(holder2);
        i++;
    }
    return(free_array(paths_array), -1);
}
