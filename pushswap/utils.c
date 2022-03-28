/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriffit <tgriffit@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 11:10:14 by tgriffit          #+#    #+#             */
/*   Updated: 2022/03/28 18:36:14 by tgriffit         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

void	cleanstacks(t_stack *stack_a, t_stack *stack_b)
{
	if (stack_a->indices)
	{
		free(stack_a->indices);
		free(stack_a->arr);
	}
	if (stack_b->indices)
	{
		free(stack_b->indices);
		free(stack_b->arr);
	}
}

void	quitps(int **stacka, int **stackb, int exitcode)
{
	if (stacka)
		free(*stacka);
	if (stackb)
		free(*stackb);
	if (exitcode == MEM_ERROR)
		ft_putendl_fd("Error: Not enough memory available.", 2);
	else if (exitcode == ALREADY_SORTED)
		exit(exitcode);
	else
		ft_putendl_fd("Error", 2);
	exit(exitcode);
}

bool	is_sorted(t_stack stacka, t_stack stackb, bool check_sb)
{
	int	i;

	i = -1;
	if (check_sb == true && stackb.size > 0)
		return (false);
	while (stacka.size > 1 && ++i < stacka.size - 1)
		if (stacka.indices[i] > stacka.indices[i + 1])
			return (false);
	return (true);
}

/**

 * @param array
 * @param size
 * @return True if there's a double in the array, else false.
 */
static bool	checkdouble(int *array, size_t size)
{
	int		i;
	int		j;
	int		nbchecked;
	int		cntnumber;

	if (size < 2)
		return (false);
	i = -1;
	while (++i < size)
	{
		cntnumber = 0;
		nbchecked = array[i];
		j = -1;
		while (++j <= i)
		{
			if (array[j] == nbchecked)
				cntnumber++;
		}
		if (cntnumber > 1)
			return (true);
	}
	return (false);
}

int	*parseargs(int argc, char **argv)
{
	int	*numbers;
	int	i;

	numbers = ft_calloc(sizeof(int), argc - 1);
	if (!numbers)
		quitps(NULL, NULL, MEM_ERROR);
	i = -1;
	while (++i < argc - 1)
	{
		if (!checkdouble(numbers, i))
			numbers[i] = ft_atoi(argv[i]);
		else
			quitps(&numbers, NULL, DOUBLE_ARG_ERROR);
		if (!ft_is_integer(ft_atoll(argv[i])))
			quitps(&numbers, NULL, WRONG_ARG_ERROR);
	}
	if (checkdouble(numbers, i))
		quitps(&numbers, NULL, DOUBLE_ARG_ERROR);
	return (numbers);
}
