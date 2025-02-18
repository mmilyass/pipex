/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_unsigned.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imeftah- <imeftah-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 12:13:04 by imeftah-          #+#    #+#             */
/*   Updated: 2024/11/14 12:13:23 by imeftah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbr_unsigned(unsigned long n)
{
	int	i;

	i = 0;
	if (n >= 10)
		i = i + ft_putnbr_unsigned(n / 10);
	n = (n % 10) + '0';
	write(1, &n, 1);
	return (i + 1);
}
