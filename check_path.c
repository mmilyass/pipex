/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imeftah- <imeftah-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 11:50:59 by safae             #+#    #+#             */
/*   Updated: 2025/02/10 16:52:05 by imeftah-         ###   ########.fr       */
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
        return(127);
    else if (access(path, X_OK) == -1)
        return(126);
    else if (access(path, X_OK && F_OK) == 0)
    {
        data->path = path;
        return(0);
    }
    return(0);
}
int    check_here_and_slash(t_data *data, char *name)   // check whether the user enter a path like ("/usr/bin/ls" or "./program" or "folder/program_name") if so i will check in this path
{
    int code;
    int check;

    int i = 0;
    check = 0;
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
    }
    return(-1);
}

char *generate_path(char *str, char *name)
{
    char *holder;
    char *tmp;

    tmp = ft_strjoin(str, "/");
    if (tmp == NULL)
        return(NULL);
    holder = ft_strjoin(tmp, name);
    free(tmp);
    if (holder == NULL)
        return(NULL);
    return(holder);
}

int check_path(char *name, char **envp, t_data *data)
{
    char **paths_array;
    char *holder;
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
        holder = generate_path(paths_array[i], name);
        if (holder == NULL)
            return(free_array(paths_array), -1);
        code = access_return(data, holder);
        if (code == 0)
            return(0);
        free(holder);
        i++;
    }
    return(free_array(paths_array), code);
}

/* yesterday i fixed the leaks i thing and i need to understand my code more and exactely the pipe part when i store the last one in the othe_pipe
and i need to fix the >> in the outfiel with it should ovewrite and nor and leak and understand the concept 

*/