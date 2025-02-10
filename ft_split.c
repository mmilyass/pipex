/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imeftah- <imeftah-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 10:12:08 by imeftah-          #+#    #+#             */
/*   Updated: 2025/02/10 16:29:45 by imeftah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "pipex.h"

static int      count_words(char *str, char c)
{
        int     i;
        int     x;

        i = 0;
        x = 0;
        while (str[i])
        {
                if (str[i] == '"' || str[i] == '\'')
                {
                        i++;
                        while (str[i] != '"' && str[i] != '\'')
                                i++;
                        i++;
                        x++;
                }
                if ((str[i] != c && (str[i + 1] == c || str[i + 1] == '\0')))
                        x++;
                i++;
        }
        return (x);
}

static void     fill_index_array(char *str, char *src, int start, int end)
{
        int     x;

        x = 0;
        while (x < end)
        {
                str[x] = src[start];
                x++;
                start++;
        }
        str[x] = '\0';
}

static void     *free_array(char **array, int index)
{
        int     i;

        i = 0;
        while (i < index)
        {
                free(array[i]);
                i++;
        }
        array[index] = NULL;
        return (NULL);
}

static char     **fill_array(char **array, char *s, char c, int words)
{
        int     i;
        int     end;
        int     index;

        index = 0;
        i = 0;
        while (index < words)
        {
                while (s[i] == c && s[i] != '\0' && s[i] != '"' && s[i] != '\'')
                        i++;
                end = 0;
                while (s[i] != c && s[i] != '\0' && s[i] != '"' && s[i] != '\'')
                {
                        end++;
                        i++;
                }
                if (s[i] == '"' || s[i] == '\'')
                {
                        i++;
                        end++;
                        while (s[i] != '"' && s[i] != '\'')
                        {
                                end++;
                                i++;
                        }
                        i++;
                        end++;
                }
                array[index] = malloc((end + 1) * sizeof(char));
                if (array[index] == NULL)
                        return (free_array(array, index));
                fill_index_array(array[index], s, i - end, end);
                index++;
        }
        array[index] = NULL;
        return (array);
}

char    **ft_split(char *s1, char c)
{
        int             words;
        char    **array;
        char    *s;
        if (s1 == NULL)
                return (NULL);
        if (s1[0] == '\0')
        {
                array = malloc(1 * sizeof(char *));
                if (array == NULL)
                        return (NULL);
                array[0] = NULL;
                return (array);
        }
        s = (char *)s1;
        words = count_words(s, c);
        if (words == -2)
                return (NULL);
        array = malloc((words + 1) * sizeof(char *));
        if (array == NULL)
                return (NULL);
        if (fill_array(array, s, c, words) == NULL)
                return (free(array), NULL);
        return (array);
}

// int main()
// {
//         char **array = ft_split("awk '{print $1}'", ' ');
//         while (*array)
//         {
//                 printf("%s\n",*array);
//                 array++;
//         }
// }