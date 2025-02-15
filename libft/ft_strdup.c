/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imeftah- <imeftah-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 18:48:25 by imeftah-          #+#    #+#             */
/*   Updated: 2025/02/12 10:19:58 by imeftah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *string)
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

int	count_words(char *str, char c)
{
	int	i;
	int	x;

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
