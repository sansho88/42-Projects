/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriffit <tgriffit@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 16:35:47 by tgriffit          #+#    #+#             */
/*   Updated: 2022/03/09 18:00:24 by tgriffit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	killfdf(t_drawer *drawer)
{
	cleanmatrices(drawer->map->map, drawer->map->ymax);
	free(drawer->window);
	exit(0);
}

static float	setzoom(float zoom, int keycode)
{
	if (keycode == KEY_PLUS)
		++(zoom);
	else if (keycode == KEY_MINUS)
		--(zoom);
	if (zoom <= 0)
		zoom = 1;
	return (zoom);
}

/**
 * Manage some keys hit. This functions is actually used for quit the app or
 * zoom in/out
 * @param keycode
 * @param drawer
 * @return Always 0.
 */
int	key_hook(int keycode, t_drawer *drawer)
{
	drawer->zoom = setzoom(drawer->zoom, keycode);
	if (keycode == KEY_PLUS || keycode == KEY_MINUS)
	{
		drawimage(drawer);
		putlines(drawer->map, drawer);
	}
	if (keycode == KEY_ESC)
		killfdf(drawer);
	return (0);
}
