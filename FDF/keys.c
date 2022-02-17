/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriffit <tgriffit@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 16:35:47 by tgriffit          #+#    #+#             */
/*   Updated: 2022/02/17 18:23:20 by tgriffit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

#include <stdio.h>

int	key_hook(int keycode, t_drawer *drawer)
{
	drawer->zoom = setzoom(drawer->zoom, keycode);
	//setoffset(*drawer->offset, keycode);
	//printf("zoom = %f\n |\t offset[0] = %f , offset[1] = %f", drawer->zoom, *drawer->offset[0], *drawer->offset[1]);
	if (keycode == KEY_PLUS || keycode == KEY_MINUS)
	{
		drawimage(drawer);
		putlines(drawer->map, drawer);
	}
	if (keycode == KEY_ESC)
		killfdf(drawer);
	return (0);
}

float	setzoom(float zoom, int keycode)
{
	if (keycode == KEY_PLUS)
		++(zoom);
	else if (keycode == KEY_MINUS)
		--(zoom);
	if (zoom <= 0)
		zoom = 1;
	return (zoom);
}

void setoffset(float *offset, int keycode)
{
	if (keycode == KEY_RIGHT)
		offset[0] += 10;
	if (keycode == KEY_LEFT)
		offset[0] -= 10;
	if (keycode == KEY_UP)
		offset[1] += 10;
	if (keycode == KEY_DOWN)
		offset[1] -= 10;
}
