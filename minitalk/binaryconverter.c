/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binaryconverter.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriffit <tgriffit@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 12:10:54 by tgriffit          #+#    #+#             */
/*   Updated: 2022/01/04 17:41:34 by tgriffit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

/**
 * Convert a char to an array of NB_BITS int
 * @param c = char to convert
 * @return The array of bits like [00001111]
 */
int	*chartobinary(char c)
{
	int	*res;
	int	i;

	i = NB_BITS;
	res = malloc(NB_BITS * sizeof(char));
	if (res)
	{
		while (i > 0)
		{
			res[--i] = c % 2;
			c /= 2;
		}
	}
	return (res);
}

/**
 * Convert an array of NB_BITS int into a char
 * @param bin
 * @return The binaries converted to a char
 */
char	binarytochar(int *bin)
{
	char	c;
	int		i;
	int		powerbin;

	i = NB_BITS;
	powerbin = 1;
	c = 0;
	while (i > 0)
	{
		c += bin[--i] * powerbin;
		powerbin *= 2;
	}
	return (c);
}
