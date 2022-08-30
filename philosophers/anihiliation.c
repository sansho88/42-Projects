/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriffit <tgriffit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 14:48:39 by tgriffit          #+#    #+#             */
/*   Updated: 2022/08/25 14:50:38 by tgriffit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	unchain_philos(t_philo *cavern)
{
	size_t	i;

	i = 0;
	while (i < cavern->world->nb_philos)
	{
		pthread_join(cavern[i].philo, NULL);
		pthread_mutex_destroy(&cavern[i].fork);
		pthread_mutex_destroy(&cavern[i].has_eaten);
		i++;
	}
	if (cavern->world->dead_philo != NULL)
		announce_death_to_family(*cavern->world->dead_philo, cavern->world);
	pthread_mutex_destroy(&cavern->world->check_go);
	pthread_mutex_destroy(&cavern->world->god_voice);
}

void	put_in_coffin(t_corpse *corpse, t_philo *philo, t_world	*world)
{
	if (philo->nb_meals != world->nb_meals_max || world->nb_meals_max == 0)
	{
		corpse->dead_philo = philo;
		corpse->time_of_death = ft_timer(*world);
		world->dead_philo = corpse;
	}
}

void	announce_death_to_family(t_corpse corpse, t_world *world)
{
	if (corpse.dead_philo != NULL)
	{
		pthread_mutex_lock(&world->god_voice);
		printf("[%ld]\t%i %s\n", corpse.time_of_death, corpse.dead_philo->id,
			"died");
		pthread_mutex_unlock(&world->god_voice);
	}
}
