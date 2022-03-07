/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotatenreverse.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriffit <tgriffit@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 11:14:42 by tgriffit          #+#    #+#             */
/*   Updated: 2022/03/02 15:32:52 by tgriffit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

/**
 *  Shift up all elements of arr a by 1.
 *  The first element becomes the last one.
 * @param stacka
 */
void	rotate_a(int *stacka, size_t size)
{
	int	tmp;
	int	i;

	tmp = stacka[0];
	i = 0;
	while (i < size - 1)
	{
		stacka[i] = stacka[i + 1];
		i++;
	}
	stacka[i] = tmp;
	ft_putendl_fd("ra", 1);
}

/**
 *  Shift up all elements of arr b by 1.
 *  The first element becomes the last one.
 * @param stackb
 */
void	rotate_b(int *stackb, size_t size)
{
	int	tmp;
	int	i;

	tmp = stackb[0];
	i = 0;
	while (i < size - 1)
	{
		stackb[i] = stackb[i + 1];
		i++;
	}
	stackb[i] = tmp;
	ft_putendl_fd("rb", 1);
}

/**
 * ra and rb at the same time.
 * @param stacka
 * @param sizea
 * @param stackb
 * @param sizeb
 */
void	rr(int *stacka, size_t sizea, int *stackb, size_t sizeb)
{
	int	tmp;
	int	i;

	tmp = stacka[0];
	i = 0;
	while (i < sizea - 1)
	{
		stacka[i] = stacka[i + 1];
		i++;
	}
	stacka[i] = tmp;
	tmp = stackb[0];
	i = 0;
	while (i < sizeb - 1)
	{
		stackb[i] = stackb[i + 1];
		i++;
	}
	stackb[i] = tmp;
	ft_putendl_fd("rr", 1);
}

/**
 *  Shift down all elements of arr a by 1.
 *  The last element becomes the first one.
 * @param stacka
 * @param size
 */
void	reverse_rotate_a(int *stacka, size_t size)
{
	int	tmp;
	int	i;

	tmp = stacka[size - 1];
	i = size - 1;
	while (i > 0)
	{
		stacka[i] = stacka[i - 1];
		i--;
	}
	stacka[i] = tmp;
	ft_putendl_fd("rra", 1);
}

/**
 *  Shift down all elements of arr b by 1.
 *  The last element becomes the first one.
 * @param stackb
 * @param size
 */
void	reverse_rotate_b(int *stackb, size_t size)
{
	int	tmp;
	int	i;

	tmp = stackb[size - 1];
	i = size - 1;
	while (i > 0)
	{
		stackb[i] = stackb[i - 1];
		i--;
	}
	stackb[i] = tmp;
	ft_putendl_fd("rrb", 1);
}
