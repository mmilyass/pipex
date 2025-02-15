/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imeftah- <imeftah-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 16:35:48 by imeftah-          #+#    #+#             */
/*   Updated: 2024/11/07 11:10:32 by imeftah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	h;
	size_t	t;

	if (size == 0 && !dest)
		return (ft_strlen(src));
	i = 0;
	h = ft_strlen(dest);
	t = ft_strlen(dest);
	if (size <= h)
		return (size + ft_strlen(src));
	while (src[i] && h < size - 1)
	{
		dest[h] = src[i];
		h++;
		i++;
	}
	dest[h] = '\0';
	return (t + ft_strlen((char *)src));
}
