/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imeftah- <imeftah-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 17:38:38 by imeftah-          #+#    #+#             */
/*   Updated: 2024/11/02 18:52:13 by imeftah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*fill_string(const char *s1, const char *s2, char *str)
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

char	*ft_strjoin(char const *s1, char const *s2)
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
