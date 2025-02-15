/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imeftah- <imeftah-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 18:27:10 by imeftah-          #+#    #+#             */
/*   Updated: 2024/11/06 16:47:21 by imeftah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *pointer, int value, size_t count)
{
	size_t			i;
	unsigned char	*ptr;

	ptr = (unsigned char *)pointer ;
	i = 0 ;
	if (count == 0)
		return (pointer);
	while (i < count)
	{
		ptr[i] = (unsigned char)value;
		i++;
	}
	return (pointer);
}
