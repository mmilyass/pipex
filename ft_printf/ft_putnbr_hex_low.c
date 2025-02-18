/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_hex_low.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imeftah- <imeftah-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 12:50:47 by imeftah-          #+#    #+#             */
/*   Updated: 2024/11/16 08:38:44 by imeftah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "limits.h"

int	ft_putnbr_hex_low(unsigned int arg)
{
	int		n;
	int		i;
	char	*str;

	str = "0123456789abcdef";
	i = 0;
	if (arg >= 16)
		i = i + ft_putnbr_hex_low(arg / 16);
	n = arg % 16;
	write(1, &str[n], 1);
	return (i + 1);
}
