/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriffit <tgriffit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 11:37:22 by tgriffit          #+#    #+#             */
/*   Updated: 2022/08/25 15:57:16 by tgriffit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_world		world;
	t_philo		*cavern;
	t_corpse	dead_philo;

	if (!check_args(argc, argv))
		return (-2);
	init_world(&world, argc, argv);
	if (world.nb_philos < 1 || world.nb_philos > 200)
	{
		printf("Wrong amount of philos. Please test between 1 and 200\n");
		return (8);
	}
	world.dead_philo = &dead_philo;
	cavern = malloc(sizeof(t_philo) * world.nb_philos);
	if (!cavern)
		return (MALLOC_ERR);
	place_philos_in_cavern(cavern, &world);
	light_on_cavern(cavern, &world, world.nb_philos);
	unchain_philos(cavern);
	free(cavern);
}
