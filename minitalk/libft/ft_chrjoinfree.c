/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriffit <tgriffit@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 16:24:51 by tgriffit          #+#    #+#             */
/*   Updated: 2022/01/04 17:36:42 by tgriffit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

/**
 * Allocate (with malloc(3)) and returns a new string, reesult of the
 * concatenation of s1 and c, and free s1 if needed with mode.
 * @param s1
 * @param c
 * @param mode = if mode = 1, the string is free
 * @return The new string. NULL if malloc fails.
 */
char	*ft_chrjoinfree(char *s1, char c, _Bool mode)
{
	char	*res;
	size_t	s1size;

	s1size = ft_strlen(s1);
	res = malloc(1 + s1size * sizeof(char) + 1);
	if (res)
	{
		ft_memcpy(res, s1, s1size);
		res[s1size] = c;
		res[s1size + 1] = '\0';
		if (mode == 1)
			free(s1);
	}
	return (res);
}
