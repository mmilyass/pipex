/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imeftah- <imeftah-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 17:43:57 by imeftah-          #+#    #+#             */
/*   Updated: 2025/02/11 11:14:38 by imeftah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, unsigned int n)
{
	unsigned int	i;

	i = 0;
	if (n == 0)
		return (0);
	while (i < n - 1 && (s1[i] == s2[i]) && s1[i] != '\0')
	{
		i++;
	}
	if (s1[i] != s2[i])
		return (s1[i] - s2[i]);
	return (0);
}

char	*ft_strcpy(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s2[i])
	{
		s1[i] = s2[i];
		i++;
	}
	s1[i] = s2[i];
	return (s1);
}

int	ft_strcmp(char *s1, char *s2)
{
	int		i;
	int		t;
	char	*str;

	i = 0;
	str = ft_strdup(s1);
	while (str[i])
	{
		if (str[i] == '\n')
		{
			str[i] = '\0';
			break ;
		}
		i++;
	}
	i = 0;
	while (str[i] == s2[i] && str[i] != '\0' && s2[i] != '\0' && str[i] != '\n')
	{
		i++;
	}
	t = (int)str[i];
	return (free(str), t - s2[i]);
}
/*
i did a special thing here that in the first string
i remove the new_line and then compare because in the
here_doc i will compare the "dilimetre" with the the string
in the here_doc and this last one have a new line and the
dilimeter not and although if they are the same so i need to
handle this
*/