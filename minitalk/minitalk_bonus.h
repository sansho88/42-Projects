/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriffit <tgriffit@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 12:19:32 by tgriffit          #+#    #+#             */
/*   Updated: 2022/01/04 17:31:59 by tgriffit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_BONUS_H
# define MINITALK_BONUS_H
# define NB_BITS 8

# include "libft/libft.h"
# include <signal.h>

pid_t	server_start(void);
void	client_start(pid_t pidsrvr, const char *msg);
int		*chartobinary(char c);
char	binarytochar(int *bin);
void	sendbnry(pid_t pidsrvr, int *bin);

#endif
