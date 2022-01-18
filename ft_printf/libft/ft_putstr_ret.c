/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriffit <tgriffit@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 16:02:58 by tgriffit          #+#    #+#             */
/*   Updated: 2021/12/15 18:46:12 by tgriffit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

/**
 * Write the string ’s’ and updates the amount of chars written.
 * @param s = The string to write
 * @param nbcharstoprint = Pointer to the char counter
 */
void	ft_putstr_ret(char *s, int *nbcharstoprint)
{
	size_t	slen;

	if (s)
	{
		slen = ft_strlen(s);
		*nbcharstoprint += (int)write(1, s, slen);
	}
	else
		*nbcharstoprint += write(1, "(null)", 6);
}
