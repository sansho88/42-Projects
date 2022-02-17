/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriffit <tgriffit@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 11:23:26 by tgriffit          #+#    #+#             */
/*   Updated: 2021/12/15 18:56:09 by tgriffit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	checkarg(char arg, va_list lst, int *charsprinted)
{
	if (arg == 'c')
		ft_putchar_ret(va_arg(lst, int), charsprinted);
	else if (arg == 's')
		ft_putstr_ret(va_arg(lst, char *), charsprinted);
	else if (arg == 'd' || arg == 'i')
		ft_putnbr_ret(va_arg(lst, int), charsprinted);
	else if (arg == 'u')
		ft_putnbr_ret(va_arg(lst, unsigned int), charsprinted);
	else if (arg == 'p')
	{
		write(1, "0x", 2);
		ft_putnbr_base_ret(va_arg(lst, unsigned long), "0123456789abcdef",
			charsprinted, 16);
		(*charsprinted += 2);
	}
	else if (arg == 'x')
		ft_putnbr_base_ret(va_arg(lst, unsigned int), "0123456789abcdef",
			charsprinted, 16);
	else if (arg == 'X')
		ft_putnbr_base_ret(va_arg(lst, unsigned int), "0123456789ABCDEF",
			charsprinted, 16);
	else if (arg == '%')
		ft_putchar_ret('%', charsprinted);
	else
		ft_putchar_ret(arg, charsprinted);
}

/**
 * Formats and prints its arguments, after the first, under control of the
 * format.\n
 * The format is a character string which contains three types of
 * objects: plain characters, which are simply copied to standard output,
 * character escape sequences which are converted and copied to the standard
 * output, and format specifications, of which causes printing of the next
 * successive argument.
 * @param format = The string and %arg within.\n
 * Args accepted: %c, %s, %d, %i, %p, %x, %X, %%,
 * @param ... = variables used in the format.
 * @return The total amount of characters printed.
 */
int	ft_printf(const char *format, ...)
{
	va_list	lst;
	int		nbchars;
	int		i;

	va_start(lst, format);
	nbchars = 0;
	i = 0;
	while (format[i])
	{
		if (format[i] != '%')
			ft_putchar_ret(format[i], &nbchars);
		else if (format[i + 1] && format[++i])
			checkarg(format[i], lst, &nbchars);
		i++;
	}
	va_end(lst);
	return (nbchars);
}
