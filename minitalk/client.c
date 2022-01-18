/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriffit <tgriffit@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 12:20:02 by tgriffit          #+#    #+#             */
/*   Updated: 2022/01/14 11:32:57 by tgriffit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

/**
 * Sends a char (represented as an array of integers) as bits
 * with SIGUSR1 (=0) and SIGUSR2(=1)
 * @param pidsrvr = The PID of the program which will receive the char.
 * @param bin
 */
void	sendbnry(pid_t pidsrvr, int *bin)
{
	int	i;

	i = NB_BITS;
	while (i > 0)
	{
		if (bin[--i] == 1)
			kill(pidsrvr, SIGUSR2);
		else
			kill(pidsrvr, SIGUSR1);
		usleep(84);
	}
	free(bin);
}

void	client_start(pid_t pidsrvr, const char *msg)
{
	while (*msg)
		sendbnry(pidsrvr, chartobinary(*(msg)++));
	sendbnry(pidsrvr, chartobinary(0));
}

int	main(int argc, char **argv)
{
	if (argc > 2 && argc < 4)
		client_start(ft_atoi(argv[1]), argv[2]);
	else
		ft_putendl_fd("Correct usage: ./client [SERVER PID] [MESSAGE]", 2);
}
