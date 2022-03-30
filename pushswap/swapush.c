/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriffit <tgriffit@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 12:44:36 by tgriffit          #+#    #+#             */
/*   Updated: 2022/03/23 16:10:17 by tgriffit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

/**
 *  Swap the first 2 elements at the top of arr a.
 *  Do nothing if there is only one or no elements
 * @param stacka
 * @param size : Size of stack_a
 */
void	swap_a(int *stacka, size_t size)
{
	if (size < 2)
		return ;
	swap(&stacka[0], &stacka[1]);
	ft_putendl_fd("sa", 1);
}

/**
 *  Swap the first 2 elements at the top of arr b.
 *  Do nothing if there is only one or no elements
 * @param stacka
 * @param size : Size of stack_a
 */
void	swap_b(int *stackb, size_t size)
{
	if (size < 2)
		return ;
	swap(&stackb[0], &stackb[1]);
	ft_putendl_fd("sb", 1);
}

/**
 * sa and sb at the same time
 * @param stacka
 * @param sizea
 * @param stackb
 * @param sizeb
 */
void	ss(int *stacka, size_t sizea, int *stackb, size_t sizeb)
{
	if (sizea < 2 && sizeb < 2)
		return ;
	if (sizea > 1)
		swap(&stacka[0], &stacka[1]);
	else
	{
		swap(&stackb[0], &stackb[1]);
		ft_putendl_fd("sb", 1);
		return ;
	}
	if (sizeb < 2)
	{
		ft_putendl_fd("sa", 1);
		return ;
	}
	ft_putendl_fd("ss", 1);
}

/**
 * Take the first element at the top of b and put it at the top of a.
 * Do nothing if b is empty
 */
void	push_a(t_stack *stacka, t_stack *stackb)
{
	if (stackb->size == 0)
		return ;
	stacka->indices = stackcpy(stacka->indices, stacka->size, stacka->size + 1,
			stackb->indices[0]);
	stackb->indices = stackcpy(stackb->indices, stackb->size, stackb->size - 1,
			stacka->indices[0]);
	stacka->size++;
	stackb->size--;
	ft_putendl_fd("pa", 1);
}

/**
 * Take the first element at the top of a and put it at the top of b.
 * Do nothing if a is empty
 */
void	push_b(t_stack *stacka, t_stack *stackb)
{
	if (stacka->size == 0)
		return ;
	stackb->indices = stackcpy(stackb->indices, stackb->size, stackb->size + 1,
			stacka->indices[0]);
	stacka->indices = stackcpy(stacka->indices, stacka->size, stacka->size - 1,
			stackb->indices[0]);
	if (stacka->size > 0)
		stacka->size--;
	stackb->size++;
	ft_putendl_fd("pb", 1);
}
