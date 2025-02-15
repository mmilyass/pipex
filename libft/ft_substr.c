/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imeftah- <imeftah-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 09:13:41 by imeftah-          #+#    #+#             */
/*   Updated: 2025/02/09 12:03:45 by imeftah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*check(const char *s, unsigned int start, size_t len)
{
	char	*str;

	if (s[0] == '\0' || start >= ft_strlen(s))
	{
		str = malloc(sizeof(char));
		if (str == NULL)
			return (NULL);
		str[0] = '\0';
		return (str);
	}
	if ((ft_strlen(s) - start) < len)
	{
		str = malloc((ft_strlen(s) - start + 1) * sizeof(char));
		if (str == NULL)
			return (NULL);
	}
	else
	{
		str = malloc((len + 1) * sizeof(char));
		if (str == NULL)
			return (NULL);
	}
	return (str);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*str;

	if (s == NULL)
		return (NULL);
	if (start >= ft_strlen(s))
		return (check(s, start, len));
	i = 0;
	str = check(s, start, len);
	if (str == NULL)
		return (NULL);
	while ((i < len && s[start] && s[i]))
	{
		str[i] = s[start];
		i++;
		start++;
	}
	str[i] = '\0';
	return (str);
}
