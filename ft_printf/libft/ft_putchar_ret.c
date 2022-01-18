/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriffit <tgriffit@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 12:07:43 by tgriffit          #+#    #+#             */
/*   Updated: 2021/12/15 12:05:53 by tgriffit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Write the string ’s’ and updates the amount of chars written.
 * @param c = The character to write.
 * @param charsprinted = Pointer to the char counter
 */
void	ft_putchar_ret(char c, int *charsprinted)
{
	write(1, &c, 1);
	(*charsprinted)++;
}
