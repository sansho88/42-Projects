/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriffit <tgriffit@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 12:44:36 by tgriffit          #+#    #+#             */
/*   Updated: 2022/03/08 20:34:48 by tgriffit         ###   ########.fr       */
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
void	push_a(int *stacka, size_t *sizea, int *stackb, size_t *sizeb)
{
	int	*newnumbers;
	int	i;

	if (*sizeb == 0)
		return ;
	/*newnumbers = ft_calloc(sizeof(int), *sizea + 1);
	if (!newnumbers)
		quitps(&stacka, &stackb, EXIT_FAILURE);
	i = -1;
	while (++i < *sizea)
		newnumbers[i + 1] = stacka[i];
	newnumbers[0] = stackb[0];
	while (i >= 0)
	{
		stacka[i] = newnumbers[i];
		i--;
	}
	i = -1;
	while (++i < *sizeb){
		stackb[i] = stackb[i + 1];
	}
	free(newnumbers);*/
	stacka = stackcpy(stacka, (int)*sizea, (int)*sizea + 1);
	stacka[0] = stackb[0];
	stackb = stackcpy(stackb, (int)*sizeb, (int)*sizeb - 1);
	printf("stackb[0] = %d, stackb[max] = %d\n", stackb[0], stackb[*sizeb - 1]);
	(*sizea)++;
	(*sizeb)--;
	ft_putendl_fd("pa", 1);
}

/**
 * Take the first element at the top of a and put it at the top of b.
 * Do nothing if a is empty
 */
void	push_b(int *stacka, size_t *sizea, int *stackb, size_t *sizeb)
{
	int	*newnumbers;
	int	i;

	if (*sizea == 0)
		return ;
	/*newnumbers = ft_calloc(sizeof(int), *sizeb + 1);
	if (!newnumbers)
		quitps(&stacka, &stackb, EXIT_FAILURE);
	i = -1;
	while (++i < *sizeb)
		newnumbers[i + 1] = stackb[i];
	newnumbers[0] = stacka[0];
	while (i >= 0)
	{
		stackb[i] = newnumbers[i];
		i--;
	}
	i = -1;
	while (++i < *sizea)
		stacka[i] = stacka[i + 1];
	free(newnumbers);*/
	stackb = stackcpy(stackb, (int)*sizeb, (int)*sizeb + 1);
	stackb[0] = stacka[0];
	stacka = stackcpy(stacka, (int)*sizea, (int)*sizea - 1);
	(*sizea)--;
	(*sizeb)++;
	ft_putendl_fd("pb", 1);
}

/*
#include <stdio.h>
int main(void)
{
	int	*stacka, *stackb, sizea, sizeb;

	stacka = ft_calloc(sizeof(int), 100);
	stackb = ft_calloc(sizeof(int), 10);
	sizea = 40;
	sizeb = 2;
	for (int i = 0; i <= sizea; ++i) {
		stacka[i] = i +5;
	}
	for (int i = 0; i < sizeb; ++i) {
		stackb[i] = 1 * 8 + i;
	}
	*/
/*printf("Size of arr a = %lu; %d\n", sizeof(*stacka), stacka[82]);*//*

	printf("Stacka[0] = %d | Stacka[1] = %d |stackb[0] = %d | stackb[1] = %d\n", stacka[0], stacka[1], stackb[0], stackb[1]);
	push_a(stacka, &sizea, stackb, &sizeb);
	printf("Stacka[0] = %d | Stacka[1] = %d |stackb[0] = %d | stackb[1] = %d\n", stacka[0], stacka[1], stackb[0], stackb[1]);
}*/
