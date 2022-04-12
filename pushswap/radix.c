/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   radix.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriffit <tgriffit@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 11:12:35 by tgriffit          #+#    #+#             */
/*   Updated: 2022/04/04 19:40:01 by tgriffit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

/**Used mainly and only for the radix_sort
 * @param stack = Only the stack which contains the numbers if useful there.
 * @return The places of each numbers initially in the stack_a in an array of
 * integers
 */
static int	*convert_to_indx(t_stack stack)
{
	size_t		i;
	size_t		j;
	int			idx;
	int			*indices;

	indices = ft_calloc(sizeof(int), stack.size);
	if (!indices)
		quitps(NULL, NULL, MEM_ERROR);
	i = -1;
	while (++i < stack.size)
	{
		idx = 0;
		j = -1;
		while (++j < stack.size)
			if (stack.arr[i] > stack.arr[j])
				idx++;
		indices[i] = idx;
	}
	return (indices);
}

void	ft_sort_less_than3(t_stack *stack_a, t_stack *stack_b)
{
	while (!is_sorted(*stack_a, *stack_b, false))
	{
		if (stack_a->size == 2)
		{
			swap_a(stack_a->indices, stack_a->size);
			break ;
		}
		if (stack_a->indices[0] > stack_a->indices[1])
			swap_a(stack_a->indices, stack_a->size);
		if (stack_a->indices[1] > stack_a->indices[2])
			reverse_rotate_a(stack_a->indices, stack_a->size);
	}
}

void	ft_sort_less_than5(t_stack *stack_a, t_stack *stack_b)
{
	while (!is_sorted(*stack_a, *stack_b, false))
	{
		if (stack_a->indices[0] > stack_a->indices[stack_a->size - 1])
			reverse_rotate_a(stack_a->indices, stack_a->size);
		else if (stack_a->size > 1 && stack_a->indices[0] > stack_a->indices[1])
			swap_a(stack_a->indices, stack_a->size);
		else
			push_b(stack_a, stack_b);
		if (stack_a->size == 3)
			ft_sort_less_than3(stack_a, stack_b);
		if (stack_b->size > 0 && stack_b->indices[0] > stack_a->indices[0])
			push_a(stack_a, stack_b);
		while (is_sorted(*stack_a, *stack_b, true) && stack_b->size > 0)
			push_a(stack_a, stack_b);
	}
}

/**
 * The radix sort by using the binaries in the numbers. It checks column by
 * column of binary and groups the numbers together if the column of the
 * binary checked is equal to 0 or 1.\n
 * It's HIGHLY recommended to use the indexes of the numbers rather than the
 * numbers themselves (else there are A LOT more of binaries to check).
 * @param stack_a = ->indices and ->size
 * @param stack_b  = ->indices and ->size
 */
void	radix(t_stack *stack_a, t_stack *stack_b)
{
	size_t		i;
	size_t		j;
	size_t		maxsize;

	maxsize = stack_a->size;
	i = 0;
	while (!is_sorted(*stack_a, *stack_b, true))
	{
		j = -1;
		while (++j < maxsize && !is_sorted(*stack_a, *stack_b, false))
		{
			if (stack_a->size <= 5 && stack_a->size > 3)
				ft_sort_less_than5(stack_a, stack_b);
			else if (stack_a->size == 3)
				ft_sort_less_than3(stack_a, stack_b);
			if ((stack_a->indices[0] >> i) & 1)
				rotate_a(stack_a->indices, stack_a->size);
			else
				push_b(stack_a, stack_b);
		}
		while (stack_b->size > 0)
			push_a(stack_a, stack_b);
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_stack	stack;
	t_stack	stackb;
	bool	argvmalloced;

	argvmalloced = false;
	if (argc == 2 && check_arg(argv[1]))
	{
		argv = ft_split(argv[1], ' ', &argc);
		argvmalloced = true;
	}
	if (!ft_str_isdigit(&argv[1 - argvmalloced], argc - 1))
		quitps(NULL, NULL, WRONG_ARG_ERROR);
	stack.size = argc - ft_striseq(argv[0], "./push_swap");
	stack.arr = parseargs(stack.size + 1, &argv[ft_striseq(argv[0],
				"./push_swap")]);
	if (argvmalloced)
	{
		free_argv(argv, argc);
		free(argv);
	}
	stackb.size = 0;
	stackb.arr = NULL;
	stack.indices = convert_to_indx(stack);
	ft_sort(&stack, &stackb, argc);
	cleanstacks(&stack, &stackb);
}
