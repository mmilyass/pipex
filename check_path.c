/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: safae <safae@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 11:50:59 by safae             #+#    #+#             */
/*   Updated: 2025/01/27 15:56:21 by safae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char **return_line_path(char **envp)
{
    int i;
    char **hold_env;

    i = 0;
    while(envp[i] != NULL)
    {
        if (ft_strncmp(envp[i], "PATH=", 5) == 0)       // take the line that have the path only
            break;
        i++;
    }
    hold_env = ft_split(envp[i] + 5, ':');              // split it with ':' to get each path and + 5 to not involve "PATH="
    if (hold_env == NULL)
        return (NULL);
    return(hold_env);
}

int check_path(char *name, char **envp, t_data *data)
{
    int i;
    char **hold_env;
    char *path;
    
    i = 0;
    hold_env = return_line_path(envp);        // take an array of strings that have paths for checks
    if (hold_env == NULL)
        return(clean_up(data), -1);
    while (hold_env[i] != NULL)
    {
        hold_env[i] = ft_strjoin(hold_env[i], "/");     // add '/' at the beginning to go to it as dir
        if (hold_env[i] == NULL)
            return(clean_up(data), -1);
        path = ft_strjoin(hold_env[i], name);       // then add to it the program name 
        if (hold_env[i] == NULL)
            return(-1);
        if (access(path, F_OK & X_OK) == 0)         // the access fnct will look for this program in the path 
        {
            data->path = path;
            return(0);                              // it will return 0 if it find it and i will do the same
        }
        free(path);
        i++;
    }
    return(-1);
}
