/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriffit <tgriffit@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 16:09:15 by tgriffit          #+#    #+#             */
/*   Updated: 2021/12/15 19:06:40 by tgriffit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Write the integer ’n’ and updates the amount of chars written.
 * @param n = The integer to write.
 * @param nbchars  = Pointer to the char counter
 */
void	ft_putnbr_ret(long long n, int *nbcharsprinted)
{
	if (n <= LONG_MIN)
	{
		write(1, "-2147483648", 11);
		(*nbcharsprinted += 11);
		return ;
	}
	if (n < 0)
	{
		write(1, "-", 1);
		(*nbcharsprinted)++;
		n *= -1;
	}
	if (n > 9)
		ft_putnbr_ret(n / 10, nbcharsprinted);
	n %= 10;
	ft_putchar_ret((char)(n + '0'), nbcharsprinted);
}
