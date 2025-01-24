/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imeftah- <imeftah-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 10:12:21 by imeftah-          #+#    #+#             */
/*   Updated: 2025/01/23 10:12:24 by imeftah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

static char	*fill_string(char *s1, char *s2, char *str)
{
	int	i;
	int	t;

	i = 0;
	t = 0;
	while (s1[t])
	{
		str[i] = s1[t];
		i++;
		t++;
	}
	t = 0;
	while (s2[t])
	{
		str[i] = s2[t];
		i++;
		t++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_strdup(char *string)
{
	int		i;
	int		len;
	char	*new;
	char	*stringg;

	stringg = (char *)string;
	i = 0;
	len = ft_strlen(stringg);
	new = malloc((len + 1) * sizeof(char));
	if (new == NULL)
		return (NULL);
	while (i < len)
	{
		new[i] = stringg[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*join_str;
	int		j_len;

	if (s1 == NULL && s2 == NULL)
		return (NULL);
	if (s1 == NULL)
		return (ft_strdup(s2));
	if (s2 == NULL)
		return (ft_strdup(s1));
	j_len = ft_strlen(s1) + ft_strlen(s2);
	join_str = malloc((j_len + 1) * sizeof(char));
	if (join_str == NULL)
		return (NULL);
	join_str = fill_string(s1, s2, join_str);
	return (join_str);
}
