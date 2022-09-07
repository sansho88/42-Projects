/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   day&night.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriffit <tgriffit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 15:29:14 by tgriffit          #+#    #+#             */
/*   Updated: 2022/09/07 12:15:56 by tgriffit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->fork);
	print_act("has taken his fork", *philo, philo->world);
	if (philo->world->nb_philos == 1)
	{
		printf("[%d]\t%i %s\n", philo->lifetime, philo->id, "died");
		pthread_mutex_lock(&philo->world->check_go);
		philo->world->go = false;
		pthread_mutex_unlock(&philo->world->check_go);
		return ;
	}
	pthread_mutex_lock(philo->nextfork);
	pthread_mutex_lock(&philo->has_eaten);
	gettimeofday(&philo->lastmeal, NULL);
	pthread_mutex_unlock(&philo->has_eaten);
	print_act("has taken an other fork", *philo, philo->world);
	print_act("is eating", *philo, philo->world);
	myusleep(philo->time4eat);
	philo->nb_meals++;
	pthread_mutex_unlock(&philo->fork);
	pthread_mutex_unlock(philo->nextfork);
}

void	dream(t_philo *philo)
{
	print_act("is sleeping", *philo, philo->world);
	myusleep(philo->sleeptime);
}

void	*routine(void	*philosoph)
{
	t_philo	*philo;

	philo = philosoph;
	while (!try_to_use(&philo->world->check_go, &philo->world->go))
		usleep('*');
	usleep((philo->id % 2 == 0) * 2000);
	while (try_to_use(&philo->world->check_go, &philo->world->go))
	{
		print_act("is thinking", *philo, philo->world);
		eat(philo);
		if (philo->world->nb_meals_max != 0 && philo->nb_meals
			== philo->world->nb_meals_max)
			return (NULL);
		dream(philo);
	}
	return (NULL);
}
