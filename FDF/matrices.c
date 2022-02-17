/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrices.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriffit <tgriffit@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 11:46:22 by tgriffit          #+#    #+#             */
/*   Updated: 2022/02/17 11:01:02 by tgriffit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/**
 * Free the allocated matrices
 * @param matrix
 * @param size
 */
void	cleanmatrices(int **matrix, size_t	size)
{
	size_t	i;

	if (!matrix || size == 0)
		return ;
	i = 0;
	while (i < size)
	{
		if (matrix[i])
			free(matrix[i]);
		i++;
	}
	free(matrix);
}

int	**setprojectionmatrix(unsigned int zoom)
{
	int	**projectionmatrix;
	int	i;

	projectionmatrix = ft_calloc(sizeof(int **), 3);
	if (!projectionmatrix)
		return (NULL);
	i = -1;
	while (++i < 3)
	{
		projectionmatrix[i] = ft_calloc(sizeof(int *), 3);
		if (!projectionmatrix[i])
		{
			while (projectionmatrix[--i] && i > -1)
				free(projectionmatrix[i]);
			return (NULL);
		}
	}
	projectionmatrix[0][0] = zoom;
	projectionmatrix[1][1] = zoom;
	projectionmatrix[2][2] = zoom;
	return (projectionmatrix);
}

float	*matrix_mul(int **projmatrix, float *coords)
{
	int		i;
	int		j;
	float	*res;

	i = 0;
	res = ft_calloc(sizeof(float), 3);
	res[i] = 0;
	while (i < 3)
	{
		j = 0;
		while (j < 3)
		{
			res[i] += (float)projmatrix[i][j] * (float)coords[j];
			j++;
		}
		i++;
	}
	free(coords);
	return (res);
}

// Ordre matrices: zoom -> rotation puis offset
