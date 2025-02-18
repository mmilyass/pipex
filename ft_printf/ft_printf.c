/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imeftah- <imeftah-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 12:52:28 by imeftah-          #+#    #+#             */
/*   Updated: 2024/11/16 09:47:19 by imeftah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_conversion(char c, va_list args)
{
	int	i;

	i = 0;
	if (c == '%')
		i = write(1, "%%", 1);
	else if (c == 'c')
		i = ft_putchar(va_arg(args, int));
	else if (c == 's')
		i = ft_putstr_if_null(va_arg(args, char *));
	else if (c == 'd' || c == 'i')
		i = ft_putnbr(va_arg(args, int));
	else if (c == 'u')
		i = ft_putnbr_unsigned(va_arg(args, unsigned int));
	else if (c == 'p')
		i = ft_putaddress((unsigned long long)va_arg(args, void *));
	else if (c == 'x')
		i = ft_putnbr_hex_low(va_arg(args, unsigned int));
	else if (c == 'X')
		i = ft_putnbr_hex(va_arg(args, unsigned int));
	return (i);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		i;
	int		t;

	va_start(args, format);
	i = 0;
	t = 0;
	if (write(1, "it will fail", 0) == -1)
		return (-1);
	while (format[i])
	{
		if (format[i] == '%')
		{
			i++;
			t = t + ft_conversion(format[i], args);
		}
		else
			t = t + write(1, &format[i], 1);
		i++;
	}
	va_end(args);
	return (t);
}
