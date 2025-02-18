/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imeftah- <imeftah-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 12:09:33 by imeftah-          #+#    #+#             */
/*   Updated: 2024/11/14 12:15:43 by imeftah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>

int	ft_printf(const char *format, ...);
int	ft_putnbr_hex(unsigned int arg);
int	ft_putnbr_hex_low(unsigned int arg);
int	ft_putaddress(unsigned long long arg);
int	ft_putnbr(int i);
int	ft_putstr_if_null(char *s);
int	ft_putchar(char c);
int	ft_putnbr_unsigned(unsigned long n);
int	for_addresse(unsigned long long arg);

#endif
