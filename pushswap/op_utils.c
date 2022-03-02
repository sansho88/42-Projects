/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriffit <tgriffit@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 13:09:50 by tgriffit          #+#    #+#             */
/*   Updated: 2022/03/01 13:09:50 by tgriffit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

void	swap(int *a, int *b)
{
	int	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

void	rotate_reverse_r(int *stacka, int sizea, int *stackb, int sizeb)
{
	int	tmp;
	int	i;

	tmp = stacka[sizea - 1];
	i = sizea - 1;
	while (i > 0)
	{
		stacka[i] = stacka[i - 1];
		i--;
	}
	stacka[i] = tmp;
	tmp = stackb[sizeb - 1];
	i = sizeb - 1;
	while (i > 0)
	{
		stackb[i] = stackb[i - 1];
		i--;
	}
	stackb[i] = tmp;
	ft_putendl_fd("rr", 1);
}
