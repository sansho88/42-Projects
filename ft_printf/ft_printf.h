/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriffit <tgriffit@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 11:21:56 by tgriffit          #+#    #+#             */
/*   Updated: 2021/12/15 19:05:25 by tgriffit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft/libft.h"
# include <stdarg.h>

void	checkarg(char arg, va_list lst, int *charsprinted);
void	ft_putnbr_base_ret(unsigned long long int nb, char *base, int *nbchars,
			size_t lenbase);
int		ft_printf(const char *format, ...);

#endif
