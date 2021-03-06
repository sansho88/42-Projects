/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriffit <tgriffit@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 13:09:50 by tgriffit          #+#    #+#             */
/*   Updated: 2022/03/23 14:55:26 by tgriffit         ###   ########.fr       */
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

int	*stackcpy(int *oldstack, int oldsize, int newsize, int target)
{
	int		i;
	int		*res;
	bool	trgtfnd;

	res = ft_calloc(sizeof(int), newsize);
	if (!res)
		quitps(NULL, NULL, MEM_ERROR);
	i = -1;
	while (++i <= oldsize + 1)
	{
		if (oldsize > newsize && i > 0 && i < newsize && oldstack[i - 1]
			== target)
			trgtfnd = true;
		if (oldsize < newsize && i < oldsize)
			res[i + 1] = oldstack[i];
		else if (oldsize > newsize && i < newsize)
			res[i - trgtfnd] = oldstack[i];
	}
	if (oldsize < newsize)
		res[0] = target;
	else if (newsize > 0)
		res[newsize - 1] = oldstack[newsize];
	free(oldstack);
	return (res);
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
