/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriffit <tgriffit@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 16:02:58 by tgriffit          #+#    #+#             */
/*   Updated: 2022/01/04 17:34:01 by tgriffit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

/**
 * Write the string S on the given File Descriptor
 * @param s = The string to write
 * @param fd
 */
void	ft_putstr_fd(char *s, int fd, _Bool mode)
{
	if (s)
	{
		write(fd, s, ft_strlen(s));
		if (mode == 1)
			free(s);
	}
}
