/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imeftah- <imeftah-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 10:12:08 by imeftah-          #+#    #+#             */
/*   Updated: 2025/02/15 10:25:39 by imeftah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	fill_index_array(char *str, char *src, int start, int end)
{
	int	x;

	x = 0;
	while (x < end)
	{
		str[x] = src[start];
		x++;
		start++;
	}
	str[x] = '\0';
}

static void	*free_array(char **array, int index)
{
	int	i;

	i = 0;
	while (i < index)
	{
		free(array[i]);
		i++;
	}
	array[index] = NULL;
	return (NULL);
}

void	i_and_end_incremenation(int *i, int *end, char *s, char c)
{
	int	tmp_i;
	int	tmp_end;

	tmp_i = *i;
	tmp_end = *end;
	if (s[tmp_i] == '"' || s[tmp_i] == '\'')
	{
		tmp_i++;
		tmp_end++;
		while (s[tmp_i] != '"' && s[tmp_i] != '\'')
		{
			tmp_end++;
			tmp_i++;
		}
		tmp_i++;
		tmp_end++;
	}
	while (s[tmp_i] != c && s[tmp_i] != '\0' && s[tmp_i] != '"'
		&& s[tmp_i] != '\'' && s[tmp_i - 1] != '\'')
	{
		tmp_end++;
		tmp_i++;
	}
	*i = tmp_i;
	*end = tmp_end;
}

static char	**fill_array(char **array, char *s, char c, int words)
{
	int	i;
	int	end;
	int	index;

	index = 0;
	i = 0;
	while (index < words)
	{
		while (s[i] == c && s[i] != '\0' && s[i] != '"' && s[i] != '\'')
			i++;
		end = 0;
		i_and_end_incremenation(&i, &end, s, c);
		array[index] = malloc((end + 1) * sizeof(char));
		if (array[index] == NULL)
			return (free_array(array, index));
		fill_index_array(array[index], s, i - end, end);
		index++;
	}
	array[index] = NULL;
	return (array);
}

char	**ft_split(char *s1, char c)
{
	int		words;
	char	**array;
	char	*s;

	if (s1 == NULL)
		return (NULL);
	if (s1[0] == '\0')
		return (NULL);
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
