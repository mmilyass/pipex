/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imeftah- <imeftah-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 13:36:40 by imeftah-          #+#    #+#             */
/*   Updated: 2024/11/06 12:38:19 by imeftah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*str;
	unsigned char	t;
	size_t			i;

	str = (unsigned char *)s ;
	t = (unsigned char)c;
	i = 0;
	while (i < n)
	{
		if (str[i] == t)
			return (&str[i]);
		i++;
	}
	return (NULL);
}
