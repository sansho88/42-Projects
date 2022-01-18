/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriffit <tgriffit@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 12:20:00 by tgriffit          #+#    #+#             */
/*   Updated: 2022/01/04 17:29:19 by tgriffit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

pid_t	server_start(void)
{
	pid_t	pidsrvr;
	char	*txtpid;

	pidsrvr = getpid();
	txtpid = ft_itoa(pidsrvr);
	write(1, "SERVER PID => ", 14);
	ft_putendl_fd(txtpid, 1);
	free(txtpid);
	return (pidsrvr);
}

/**
 * Manage the signals received with the help of sigaction().
 * Once the full message is received bit-by-bit, the handler prints it in the
 * standard input.
 * @param signom = signal received. Supports only SIGUSR1 and SIGUSR2.
 */
static void	handler(int signom)
{
	int			bin[NB_BITS];
	static int	i;
	static char	*res;

	if (!i || i <= 0)
		i = NB_BITS;
	if (signom == SIGUSR1)
		bin[--i] = 0;
	else if (signom == SIGUSR2)
		bin[--i] = 1;
	if (i == 0)
	{
		res = ft_chrjoinfree(res, binarytochar(bin), 1);
		if (binarytochar(bin) == '\0')
		{
			ft_putstr_fd(res, 1, res != NULL);
			res = NULL;
		}
	}
}

int	main(void)
{
	server_start();
	while (1)
	{
		signal(SIGUSR1, handler);
		signal(SIGUSR2, handler);
		pause();
	}
}
