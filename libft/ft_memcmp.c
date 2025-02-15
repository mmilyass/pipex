/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imeftah- <imeftah-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 14:38:41 by imeftah-          #+#    #+#             */
/*   Updated: 2024/11/08 09:45:15 by imeftah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*str;
	unsigned char	*strr;
	size_t			i;

	str = (unsigned char *)s1;
	strr = (unsigned char *)s2;
	i = 0;
	while (i < n)
	{
		if (str[i] != strr[i])
			return (str[i] - strr[i]);
		i++;
	}
	return (0);
}
