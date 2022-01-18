/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriffit <tgriffit@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 12:59:56 by tgriffit          #+#    #+#             */
/*   Updated: 2021/12/02 18:55:18 by tgriffit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strjoin(char const *s1, char *s2)
{
	char	*res;
	size_t	s1size;
	size_t	s2size;

	if (!s1 || !s2)
		return (0);
	s1size = ft_strlen(s1);
	s2size = ft_strlen(s2);
	res = malloc((ft_strlen(s1) + ft_strlen(s2)) * sizeof(char) + 1);
	if (res)
	{
		ft_memcpy(res, s1, s1size);
		ft_memcpy(res + s1size, s2, s2size + 1);
	}
	free((void *)s1);
	while (*s2)
				*s2++ = 0;
	return (res);
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t		i;
	char		*resdst;
	char		*ressrc;

	if (dst == 0 && src == 0)
		return (0);
	resdst = (char *)dst;
	ressrc = (char *)src;
	i = 0;
	while (i < n)
	{
		resdst[i] = ressrc[i];
		i++;
	}
	return (resdst);
}

char	*ft_strdup(const char *s1)
{
	char	*res;
	size_t	i;

	i = 0;
	res = malloc(ft_strlen(s1) * sizeof(char) + 1);
	if (!res)
		return (0);
	while (s1[i])
	{
		res[i] = s1[i];
		i++;
	}
	res[i] = 0;
	return (res);
}

char	*ft_strnstr(const char *haystack, const char *needle, size_t n)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!needle[0])
		return ((char *)haystack);
	if (n == 0)
		return (0);
	while (haystack[i] && i < n)
	{
		while ((haystack[i + j] == needle[j]) && (i + j) < n)
		{
			if (!needle[j - 1])
				return ((char *)&haystack[i + n]);
			j++;
		}
		j = 0;
		i++;
	}
	return (0);
}
