/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imeftah- <imeftah-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 18:28:46 by imeftah-          #+#    #+#             */
/*   Updated: 2024/11/05 11:00:27 by imeftah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	unsigned int	i;
	unsigned int	t;
	char			*str;

	str = (char *)s;
	i = ft_strlen(s);
	t = ft_strlen(s);
	while (i > 0)
	{
		if (str[i - 1] == (char)c)
			return (&str[i - 1]);
		i--;
	}
	if ((char)c == '\0')
		return (&str[t]);
	return (NULL);
}
