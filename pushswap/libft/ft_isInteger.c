/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_integer.c                                     :+:      :+:    :+:  */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriffit <tgriffit@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 19:30:25 by tgriffit          #+#    #+#             */
/*   Updated: 2022/03/23 20:30:42 by tgriffit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @param nb = The number to check
 * @return True if nb >= INT32_MIN && nb <= INT32_MAX
 */
bool	ft_is_integer(long long nb)
{
	return (nb >= INT32_MIN && nb <= INT32_MAX);
}
