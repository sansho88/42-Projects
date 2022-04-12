/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pushswap.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriffit <tgriffit@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 12:40:12 by tgriffit          #+#    #+#             */
/*   Updated: 2022/03/30 19:04:23 by tgriffit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSHSWAP_H
# define PUSHSWAP_H
# include "libft/libft.h"
# include <stdbool.h>

# include <stdio.h>

# define MEM_ERROR -8
# define DOUBLE_ARG_ERROR -4
# define WRONG_ARG_ERROR -5
# define ALREADY_SORTED 0

typedef struct s_stack
{
	int					*arr;
	int					*indices;
	int					min;
	int					max;
	int					posmin;
	int					posmax;
	size_t				size;
	struct s_stack_a	*next;
}	t_stack;

///////////////////////////////// FUNCTIONS ////////////////////////////////////

// [op_utils.c]
void	swap(int *a, int *b);

// [utils.c]
void	quitps(int **stacka, int **stackb, int exitcode);
void	cleanstacks(t_stack *stack_a, t_stack *stack_b);
int		*parseargs(int argc, char **argv);

// [rotatenreverse.c]
void	rotate_a(int *stacka, size_t size);
void	rotate_b(int *stackb, size_t size);
void	rr(int *stacka, size_t sizea, int *stackb, size_t sizeb);
void	reverse_rotate_a(int *stacka, size_t size);
void	reverse_rotate_b(int *stackb, size_t size);

// [swapush.c]
void	swap_a(int *stacka, size_t size);
void	swap_b(int *stackb, size_t size);
void	ss(int *stacka, size_t sizea, int *stackb, size_t sizeb);
void	push_a(t_stack *stacka, t_stack *stackb);
void	push_b(t_stack *stack_a, t_stack *stack_b);

// [radix.c]
void	radix(t_stack *stack_a, t_stack *stack_b);
void	ft_sort_less_than3(t_stack *stack_a, t_stack *stack_b);
void	ft_sort_less_than5(t_stack *stack_a, t_stack *stack_b);

// [sort.c]
void	ft_sort(t_stack *stack_a, t_stack *stack_b, int argc);
void	free_argv(char **argv, int argc);
bool	check_arg(char *arg);

size_t	countnmbrsconcerned(int *arr, size_t size, int digit, int exp);
int		*stackcpy(int *oldstack, int oldsize, int newsize, int target);
bool	is_sorted(t_stack stacka, t_stack stackb, bool check_stack_b);

#endif
