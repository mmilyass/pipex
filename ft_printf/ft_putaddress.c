/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putaddress.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imeftah- <imeftah-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 12:10:16 by imeftah-          #+#    #+#             */
/*   Updated: 2024/11/14 12:10:21 by imeftah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putaddress(unsigned long long arg)
{
	int	i;

	write(1, "0x", 2);
	i = 2;
	i = i + for_addresse(arg);
	return (i);
}
