/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pushswap.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriffit <tgriffit@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 12:40:12 by tgriffit          #+#    #+#             */
/*   Updated: 2022/03/01 12:44:30 by tgriffit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSHSWAP_H
# define PUSHSWAP_H
# include "libft/libft.h"

typedef struct s_stack_a
{
	int					current;
	struct s_stack_a	*next;
}	t_stack_a;

typedef struct s_stack_b
{
	int					current;
	struct s_stack__b	*next;
}	t_stack_b;

///////////////////////////////// FUNCTIONS ////////////////////////////////////

// [op_utils.c]
void	swap(int *a, int *b);

// [utils.c]
void	quitps(int **stacka, int **stackb, int exitcode);

// [rotatenreverse.c]
void	rotate_a(int *stacka, int size);

#endif
