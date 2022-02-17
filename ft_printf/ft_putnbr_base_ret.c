/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base_ret.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriffit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 20:53:56 by tgriffit          #+#    #+#             */
/*   Updated: 2021/12/15 18:56:01 by tgriffit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"

/**
 * Write the number converted to the base passed in parameters,
 * in the standard output, and updates the amount of chars written.
 * @param nb = The number to convert
 * @param base = The base reference (ex: 0123, 0123abcd, UnIcOrN, etc)
 * @param nbchars  = Pointer to the char counter
 * @param lenbase = Length of the base (placed there for optimization)
 */
void	ft_putnbr_base_ret(unsigned long long int nb, char *base, int *nbchars,
			size_t lenbase)
{
	if (nb > lenbase - 1)
		ft_putnbr_base_ret(nb / (int)lenbase, base, nbchars, lenbase);
	nb %= (int)lenbase;
	*nbchars += write(1, &base[nb], 1);
}
