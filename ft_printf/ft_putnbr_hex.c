/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_hex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imeftah- <imeftah-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 15:38:00 by imeftah-          #+#    #+#             */
/*   Updated: 2024/11/15 15:25:14 by imeftah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbr_hex(unsigned int arg)
{
	char	n;
	int		i;
	char	*str;

	str = "0123456789ABCDEF";
	i = 0;
	if (arg >= 16)
	{
		i = i + ft_putnbr_hex(arg / 16);
		arg = arg % 16;
	}
	n = str[arg];
	write(1, &n, 1);
	return (i + 1);
}
