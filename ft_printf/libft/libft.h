/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriffit <tgriffit@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 14:35:46 by tgriffit          #+#    #+#             */
/*   Updated: 2021/12/15 19:06:40 by tgriffit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef LIBFT_H
# define LIBFT_H

# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>

unsigned int	ft_strlen(const char *str);
void			ft_putchar_ret(char c, int *nbcharstoprint);
void			ft_putstr_ret(char *s, int *nbcharstoprint);
void			ft_putnbr_ret(long long n, int *nbcharstoprint);

#endif