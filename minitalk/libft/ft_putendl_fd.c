/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriffit <tgriffit@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 16:06:26 by tgriffit          #+#    #+#             */
/*   Updated: 2022/01/04 14:59:53 by tgriffit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Write the string S on the given File Descriptor and skip a line
 * @param s = The string to write
 * @param fd
 */
void	ft_putendl_fd(char *s, int fd)
{
	ft_putstr_fd(s, fd, 0);
	write(fd, &"\n", 1);
}
