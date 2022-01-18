/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriffit <tgriffit@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 12:20:00 by tgriffit          #+#    #+#             */
/*   Updated: 2022/01/05 11:03:54 by tgriffit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

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
 * Manage the signals received with the help of sigaction(), and confirms each
 * bit received to the sender.\n
 * Once the full message is received bit-by-bit, the handler prints it in the
 * standard input.
 * @remark Signals between the client and this program can be lost.
 * @param signom = signal received. Supports only SIGUSR1 and SIGUSR2.
 * @param sinfo = informations about the signal received
 * @param context
 */
static void	handler(int signom, siginfo_t *sinfo, void *context)
{
	int				bin[NB_BITS];
	static int		i;
	pid_t			pidsnder;
	static char		*res;

	pidsnder = sinfo->si_pid;
	context = NULL;
	if (!i || i < 0)
		i = NB_BITS;
	bin[--i] = signom - SIGUSR1;
	usleep(25);
	kill(pidsnder, signom);
	if (i == 0)
	{
		res = ft_chrjoinfree(res, binarytochar(bin), res != NULL);
		if (binarytochar(bin) == '\0')
		{
			ft_putstr_fd(res, 1, 0);
			free(res);
			res = NULL;
		}
	}
}

int	main(void)
{
	struct sigaction	sa;

	sa.sa_flags = SA_SIGINFO | SA_RESTART | SA_NODEFER;
	sa.sa_sigaction = &handler;
	server_start();
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
	{
		pause();
	}
}
