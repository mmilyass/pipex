/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: safae <safae@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 11:50:59 by safae             #+#    #+#             */
/*   Updated: 2025/01/24 16:10:11 by safae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char **return_line_path(char *name, char **envp)
{
    int i;
    char **hold_env;

    i = 0;
    while(envp[i] != NULL)
    {
        if (ft_strncmp(envp[i], "PATH=", 5) == 0)
            break;
        i++;
    }
    hold_env = ft_split(envp[i] + 5, ':');
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
    hold_env = return_line_path(name, envp);
    if (hold_env == NULL)
        return(-1);
    while (hold_env[i] != NULL)
    {
        hold_env[i] = ft_strjoin(hold_env[i], "/");
        if (hold_env[i] == NULL)
            return(-1);
        path = ft_strjoin(hold_env[i], name);
        if (hold_env[i] == NULL)
            return(-1);
        if (access(path, F_OK & X_OK) == 0)
        {
            data->path = path;
            return(0);
        }
        free(path);
        i++;
    }
    return(-1);
}
