/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriffit <tgriffit@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 12:19:24 by tgriffit          #+#    #+#             */
/*   Updated: 2022/02/17 14:00:02 by tgriffit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>

void	killfdf(t_drawer *drawer)
{
	printf("&drawer->map->map[0] = %p\t&drawer->map = %p\n", &drawer->map->map[0], &drawer->map);
	cleanmatrices(drawer->map->map, drawer->map->ymax);
	//free(drawer->map);
	free(drawer->window);
	exit(0);
}