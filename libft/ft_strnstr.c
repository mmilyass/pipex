/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imeftah- <imeftah-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 17:46:38 by imeftah-          #+#    #+#             */
/*   Updated: 2024/11/08 10:30:34 by imeftah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_strncmpp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
		{
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		}
		i++;
	}
	return (0);
}

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	char	*haystackk;
	char	*needlee;

	if (haystack == NULL && len == 0 && needle != NULL)
		return (NULL);
	if (needle[0] == '\0')
		return ((char *)haystack);
	haystackk = (char *)haystack;
	needlee = (char *)needle;
	i = 0;
	while (haystackk[i] && len >= ft_strlen(needle))
	{
		if (haystackk[i] == needlee[0])
		{
			if (ft_strncmpp(&haystackk[i], needlee, ft_strlen(needlee)) == 0)
			{
				return (&haystackk[i]);
			}
		}
		i++;
		len--;
	}
	return (NULL);
}
