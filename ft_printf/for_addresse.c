/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   for_addresse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imeftah- <imeftah-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 12:08:20 by imeftah-          #+#    #+#             */
/*   Updated: 2024/11/15 15:29:15 by imeftah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	for_addresse(unsigned long long arg)
{
	int		n;
	int		i;
	char	*str;

	str = "0123456789abcdef";
	i = 0;
	if (arg >= 16)
		i = i + for_addresse(arg / 16);
	n = arg % 16;
	write(1, &str[n], 1);
	return (i + 1);
}
