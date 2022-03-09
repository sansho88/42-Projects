/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pushswap.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriffit <tgriffit@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 12:40:12 by tgriffit          #+#    #+#             */
/*   Updated: 2022/03/08 20:10:24 by tgriffit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSHSWAP_H
# define PUSHSWAP_H
# include "libft/libft.h"
# include <stdbool.h>

# define MEM_ERROR -8

typedef struct s_stack
{
	int					*arr;
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
void	push_a(int *stacka, size_t *sizea, int *stackb, size_t *sizeb);
void	push_b(int *stacka, size_t *sizea, int *stackb, size_t *sizeb);

size_t	countnmbrsconcerned(int *arr, size_t size, int digit, int exp);
int		*stackcpy(int *oldstack, int oldsize, int newsize);

#endif
