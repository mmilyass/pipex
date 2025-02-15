/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imeftah- <imeftah-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 16:23:37 by imeftah-          #+#    #+#             */
/*   Updated: 2024/11/08 09:57:53 by imeftah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char			*to;
	const char		*from;
	size_t			i;

	if (dest == NULL && src == NULL)
		return (NULL);
	if (n == 0)
		return (dest);
	to = (char *)dest;
	from = (const char *)src;
	i = 0;
	while (i < n)
	{
		to[i] = from[i];
		i++;
	}
	return (to);
}
