/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imeftah- <imeftah-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 11:05:46 by imeftah-          #+#    #+#             */
/*   Updated: 2024/11/05 11:00:24 by imeftah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	where_start(const char *s1, const char *set)
{
	int	i;
	int	h;
	int	t;

	i = 0;
	h = 1;
	while (s1[i] && h == 1)
	{
		h = 0;
		t = 0;
		while (set[t])
		{
			if (s1[i] == set[t])
			{
				h = 1;
				break ;
			}
			t++;
		}
		if (h == 0)
			break ;
		i++;
	}
	return (i);
}

static int	where_end(const char *s1, const char *set)
{
	int	len;
	int	h;
	int	t;

	h = 1;
	len = ft_strlen(s1) - 1;
	while (len >= 0 && h == 1)
	{
		h = 0;
		t = 0;
		while (set[t])
		{
			if (s1[len] == set[t])
			{
				h = 1;
				break ;
			}
			t++;
		}
		if (h == 0)
			break ;
		len--;
	}
	return (len);
}

static int	check_start(const char *s1, const char *set)
{
	int	len;
	int	start;
	int	end;
	int	p;

	len = ft_strlen(s1);
	start = where_start(s1, set);
	end = where_end(s1, set);
	end++;
	if (start == len)
		p = 0;
	else
	{
		p = end - start;
	}
	return (p);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		start;
	int		len;
	char	*str;

	if (s1 == NULL)
		return (NULL);
	if (set == NULL)
		return (ft_strdup(s1));
	i = 0;
	start = where_start(s1, set);
	len = check_start(s1, set);
	str = malloc((len + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	if (len == 0)
	{
		str[0] = '\0';
		return (str);
	}
	while (i < len)
		str[i++] = s1[start++];
	str[i] = '\0';
	return (str);
}
