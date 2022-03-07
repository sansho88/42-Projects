/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriffit <tgriffit@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 11:10:14 by tgriffit          #+#    #+#             */
/*   Updated: 2022/03/02 11:10:14 by tgriffit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

void	quitps(int **stacka, int **stackb, int exitcode)
{
	if (*stacka)
		free(*stacka);
	if (*stackb)
		free(*stackb);
	if (exitcode == -1)
		ft_putendl_fd("Error", 2);
	exit(exitcode);
}