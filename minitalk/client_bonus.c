/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriffit <tgriffit@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 12:20:02 by tgriffit          #+#    #+#             */
/*   Updated: 2022/01/14 11:37:06 by tgriffit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

pid_t	g_pidserver = 0;

/**
 * If a signal is lost, try to send again the same signal. It can help only if
 * the signal was lost before the server receives it.
 * @param signal
 */
void	sigresent(int signal)
{
	unsigned int	elapsedtime;
	static int		nbtries;

	elapsedtime = alarm(2);
	if (elapsedtime <= 1)
	{
		write(1, "Last signal resent.\n", 21);
		kill(signal, g_pidserver);
		nbtries++;
	}
	if (nbtries > 5)
	{
		write(1, "Too many signals lost.\n", 23);
		exit(42);
	}
}

/**
 * Used for confirm the reception of the signal from the server before to send
 * the next one.
 * @param sig = Signal received by the server. Supports only SIGUSR1 and SIGUSR2.
 */
static void	pingpong(int sig)
{
	if (sig == SIGUSR1)
		write(1, "bit '0' received by the server\n", 32);
	else if (sig == SIGUSR2)
		write(1, "bit '1' received by the server\n", 32);
	sigresent(sig);
	usleep(45);
}

/**
 * Sends a char (represented as an array of integers) as bits
 * with SIGUSR1 (=0) and SIGUSR2 (=1).
 * @param pidsrvr = The PID of the program which will receive the char.
 * @param bin = The char to send, which has to be converted as an int[8].
 */
void	sendbnry(pid_t pidsrvr, int *bin)
{
	int	i;

	i = NB_BITS;
	while (i > 0)
	{
		if (bin[--i] == 1)
		{
			kill(pidsrvr, SIGUSR2);
			write(1, "SIGUSR2 sent\n", 14);
		}
		else
		{
			kill(pidsrvr, SIGUSR1);
			write(1, "SIGUSR1 sent\n", 14);
		}
		pause();
	}
	free(bin);
}

/**
 * Reads the string passed in the program's arguments, prepares it to be sent
 * to the server and manage some special characters.
 * ('\\n', '\\r', '\\t', '\\0', '\\' ')
 * @param pidsrvr
 * @param msg
 */
void	client_start(pid_t pidsrvr, const char *msg)
{
	while (*msg)
	{
		if (*(msg) == '\\')
		{
			if (*(msg + 1) == 'n')
				sendbnry(pidsrvr, chartobinary('\n'));
			else if (*(msg + 1) == 'r')
				sendbnry(pidsrvr, chartobinary('\r'));
			else if (*(msg + 1) == 't')
				sendbnry(pidsrvr, chartobinary('\t'));
			else if (*(msg + 1) == '0')
				sendbnry(pidsrvr, chartobinary('\0'));
			else if (*(msg + 1) == '\'')
				sendbnry(pidsrvr, chartobinary('\''));
			msg += 2;
		}
		else
			sendbnry(pidsrvr, chartobinary(*(msg)++));
	}
	sendbnry(pidsrvr, chartobinary(0));
	ft_putendl_fd("[End Of Transmission]", 2);
}

int	main(int argc, char **argv)
{
	signal(SIGUSR1, pingpong);
	signal(SIGUSR2, pingpong);
	signal(SIGALRM, sigresent);
	if (argc > 2 && argc < 4)
	{
		g_pidserver = ft_atoi(argv[1]);
		client_start(g_pidserver, argv[2]);
	}
	else
		ft_putendl_fd("Correct usage:./client_bonus [SERVER PID][MESSAGE]", 2);
}
