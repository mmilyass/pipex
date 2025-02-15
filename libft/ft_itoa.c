/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imeftah- <imeftah-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 15:58:11 by imeftah-          #+#    #+#             */
/*   Updated: 2024/11/02 18:50:38 by imeftah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <limits.h>

static int	count_number(int nbr)
{
	int	i;

	i = 0;
	while (nbr != 0)
	{
		nbr = nbr / 10;
		i++;
	}
	return (i);
}

static void	reverse(char *str)
{
	int		i;
	int		len;
	char	swap;

	i = 0;
	len = 0;
	while (str[len])
		len++;
	len = len - 1;
	while (i < len)
	{
		swap = str[i];
		str[i] = str[len];
		str[len] = swap;
		i++;
		len--;
	}
}

static char	*if_negative(long n, int len)
{
	char	*str;
	int		i;
	int		t;

	len = len + 1;
	str = malloc((len + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	str[0] = '-';
	i = 1;
	n = -n;
	while (n != 0)
	{
		t = n % 10;
		str[i] = t + '0';
		n = n / 10;
		i++;
	}
	str[i] = '\0';
	reverse(&str[1]);
	return (str);
}

static char	*ft_positive(int n, int len)
{
	char	*str;
	int		i;
	int		t;

	str = malloc((len + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	i = 0;
	while (n != 0)
	{
		t = n % 10;
		str[i] = t + '0';
		n = n / 10;
		i++;
	}
	str[i] = '\0';
	reverse(str);
	return (str);
}

char	*ft_itoa(int nbr)
{
	char	*str;
	long	n;
	int		len;

	n = nbr;
	if (nbr == 0)
	{
		str = malloc(2 * sizeof(char));
		if (!str)
			return (NULL);
		str[0] = '0';
		str[1] = '\0';
		return (str);
	}
	len = count_number(n);
	if (n < 0)
		str = if_negative(n, len);
	else
		str = ft_positive(n, len);
	return (str);
}
