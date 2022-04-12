/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isdigit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriffit <tgriffit@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 12:00:38 by tgriffit          #+#    #+#             */
/*   Updated: 2022/04/04 19:41:53 by tgriffit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "stdio.h"

/**	Tests for a decimal digit character.*/
int	ft_str_isdigit(char **str, size_t size)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (i < size)
	{
		if ((str[i][j] == '-' && !ft_isdigit((str)[i][j + 1])) || (!ft_isdigit
		(str[i][j]) && str[i][j] != '-'))
			return (0);
		j++;
		if (!str[i][j])
		{
			i++;
			j = 0;
		}
	}
	return (1);
}
