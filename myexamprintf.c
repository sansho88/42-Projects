/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: exam <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 15:42:03 by exam              #+#    #+#             */
/*   Updated: 2022/01/06 17:44:24 by exam             ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <unistd.h>

int	ft_putstr(const char *s)
{
	int res = 0;
	if (s && *s)
		while(*s)
		{
			res += write(1, s, 1);
			s++;
		}
	else
		res += write(1, "(null)", 6);
	return (res);
}

int ft_putchar(char c)
{
	return (write(1, &c, 1));
}

int	ft_putnbr(long long int nb)
{
	int	res = 0;
	if (nb < 0)
	{
		res += write(1, "-", 1);
		nb *= -1;
	}
	if (nb > 10)
		res += ft_putnbr(nb / 10);
	return (res + ft_putchar('0' + nb % 10)); 
}

int	ft_putx(long long int nb)
{
	int res = 0;
	char *base = "0123456789abcdef";

	if (nb < 0)
		nb *= -1;
	if (nb > 15)
		res += ft_putx(nb / 16);
	nb %= 16;
	return (res + ft_putchar(base[nb]));
}

int	ft_printf(const char *format, ...)
{
	int res = 0;
	va_list list;

	va_start(list, format);
	while( *format)
	{
		if (*format + 1 && *format == '%')
		{
			if (*(format +1) == 's')
				res += ft_putstr(va_arg(list, const char *));
			else if (*(format + 1) == 'd')
				res += ft_putnbr(va_arg(list, int));
			else if (*(format + 1) == 'x')
				res += ft_putx(va_arg(list, int));
			else
				res += ft_putchar(*format);
			format++;
		}
		else
			res += ft_putchar(*format);
		format++;
	}
	va_end(list);
	return (res);
}

#include <stdio.h>
int main(void)
{
	printf("[result: %d]\n", ft_printf("Hello %s, 42 = %d, -84 = %d, 128 en hexa = %x", "", 1958945038, -2066088285, -10));
}
