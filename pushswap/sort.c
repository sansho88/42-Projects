/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriffit <tgriffit@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 18:25:37 by tgriffit          #+#    #+#             */
/*   Updated: 2022/04/04 20:07:12 by tgriffit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

/**
 * Sort the stack_a by using the stack_b. Use less instructions if the amount
 * of numbers is less or equal than 3, and ofc the same for 5.
 * @param argc = Amount of numbers to sort in the stack_a
 */
void	ft_sort(t_stack *stack_a, t_stack *stack_b, int argc)
{
	if (is_sorted(*stack_a, *stack_b, 0) || argc < 2)
		quitps(&stack_a->indices, &stack_b->indices, ALREADY_SORTED);
	if (stack_a->size <= 3)
		ft_sort_less_than3(stack_a, stack_b);
	else if (stack_a->size <= 5 && stack_a->size > 3)
		ft_sort_less_than5(stack_a, stack_b);
	else
		radix(stack_a, stack_b);
	while (stack_b->size > 0)
		push_a(stack_a, stack_b);
}

void	free_argv(char **argv, int argc)
{
	int	i;

	i = 0;
	while (i < argc)
		free(argv[i++]);
}

bool	check_arg(char *arg)
{
	if (!arg || !*arg)
		quitps(NULL, NULL, ALREADY_SORTED);
	if ((*arg != '0' && !(arg[0] == '-' && arg[1] == '0')) && ft_atoi(arg) == 0)
		quitps(NULL, NULL, WRONG_ARG_ERROR);
	if ((ft_strncmp(arg, ft_itoa(ft_atoi(arg)), ft_strlen(arg) + 1)))
		quitps(NULL, NULL, WRONG_ARG_ERROR);

	/*else if (ft_atoi(arg + 1) == 0 && arg[1] != '0')
		quitps(NULL, NULL, WRONG_ARG_ERROR);*/
	return (true);
}
