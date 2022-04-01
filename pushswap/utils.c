/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriffit <tgriffit@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 11:10:14 by tgriffit          #+#    #+#             */
/*   Updated: 2022/04/01 12:09:55 by tgriffit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

/**
 * Free all the values and indices stocked in the both stacks.
 */
void	cleanstacks(t_stack *stack_a, t_stack *stack_b)
{
	free(stack_a->arr);
	free(stack_b->arr);
	free(stack_a->indices);
	free(stack_b->indices);
}

/**
 * Quit push swap and free the stacks if the params aren't NULL, and set the
 * exitcode as:
 * @param \exitcodes
 * MEM_ERROR = -8
 * \n DOUBLE_ARG ERROR = -4
 * \n WRONG_ARG_ERROR = -5
 * \n ALREADY_SORTED = 0
 */
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

/**
 * @param check_sb = If set to true, it will check the stack b and returns
 * false if B isn't empty.
 * @return True if the indices are sorted (only in the stack a).
 */
bool	is_sorted(t_stack stacka, t_stack stackb, bool check_sb)
{
	size_t	i;

	i = -1;
	if (check_sb == true && stackb.size > 0)
		return (false);
	while (stacka.size > 1 && ++i < stacka.size - 1)
		if (stacka.indices[i] > stacka.indices[i + 1])
			return (false);
	return (true);
}

/**
 * @return True if there's a double in the array, else false.
 */
static bool	checkdouble(int const *array, size_t size)
{
	size_t		i;
	size_t		j;
	int			nbchecked;
	int			cntnumber;

	if (size < 2)
		return (false);
	i = -1;
	while (++i < size)
	{
		cntnumber = 0;
		nbchecked = array[i];
		j = -1;
		while (++j <= i)
			if (array[j] == nbchecked)
				cntnumber++;
		if (cntnumber > 1)
			return (true);
	}
	return (false);
}

/**
 * Take all the args and transform them in an int array.\n Quit push_swap if
 * there's a double or an arg isn't an integer.
 * @param argc = Amount of args. It's recommended to put there the main's argc.
 * @param argv = Args. It's recommended to put there the main's argv.
 * @return The argv into an array of integers.
 */
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
		if (!ft_is_integer(ft_atoll(argv[i])) || ft_strlen(argv[i]) > 11)
			quitps(&numbers, NULL, WRONG_ARG_ERROR);
	}
	if (checkdouble(numbers, i))
		quitps(&numbers, NULL, DOUBLE_ARG_ERROR);
	return (numbers);
}
