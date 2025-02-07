/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imeftah- <imeftah-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 11:50:59 by safae             #+#    #+#             */
/*   Updated: 2025/02/07 16:44:50 by imeftah-         ###   ########.fr       */
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

int access_return(t_data *data, char *path)
{
    if (access(path, F_OK) == -1)
    {
        return(127);
    }
    else if (access(path, X_OK) == -1)
        return(126);
    else if (access(path, X_OK && F_OK) == 0)
    {
        data->path = path;
        return(0);
    }
    free(path);                               // if you wonder at the bottow where i free holder2 i do it here
}
int    check_here_and_slash(t_data *data, char *name)   // check whether the user enter a path like ("/usr/bin/ls" or "./program" or "folder/program_name") if so i will check in this path
{
    int code;
    int check;
    int i = 0;
    while(name[i])
    {
        if (name[i] == '/')
            check = -1;
        i++;
    }
    if(check == -1)
    {
        code = access_return(data, name);
        return(code);
        printf("%s\n",name);
    }
    return(-1);
}

int check_path(char *name, char **envp, t_data *data) // this function checks the path of the program to be executed 
{
    char **paths_array;
    char *holder;
    char *holder2;
    int code;
    int i;
    
    i = 0;
    code = check_here_and_slash(data, name);
    if(code != -1)
        return(code);
    paths_array = return_line_path_splited(envp);
    if(paths_array == NULL)
        other_error(data);
    while(paths_array[i])
    {
        holder = ft_strjoin(paths_array[i], "/");
        if (holder == NULL)
            return(free_array(paths_array), other_error(data), -1);
        holder2 = ft_strjoin(holder, name);
        free(holder);
        if (holder2 == NULL)
            return(free_array(paths_array), -1);
        code = access_return(data, holder2);
        if (code == 0)
            return(0);
        i++;
    }
    return(free_array(paths_array), code);
}
