/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   secretary.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriffit <tgriffit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 15:32:21 by tgriffit          #+#    #+#             */
/*   Updated: 2022/08/25 16:09:37 by tgriffit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	try_to_use(pthread_mutex_t *mutex, const bool *value_to_check)
{
	bool	answer;

	pthread_mutex_lock(mutex);
	answer = *value_to_check;
	pthread_mutex_unlock(mutex);
	return (answer);
}

void	print_act(char *msg, t_philo philo, t_world *world)
{
	if (!try_to_use(&world->check_go, &world->go))
		return ;
	pthread_mutex_lock(&world->god_voice);
	printf("[%ld]\t%i %s\n", ft_timer(*world), philo.id, msg);
	pthread_mutex_unlock(&world->god_voice);
}

bool	check_args(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
	{
		printf("Correct usage: ./philo [number_of_philosophers] [time_to_die] "
			"[time_to_eat] [time_to_sleep] "
			"(number_of_times_each_philosopher_must_eat)\n");
		return (false);
	}
	if (!ft_str_isdigit(argv + 1, argc - 1))
	{
		printf("At least one of the args isn't a number. "
			"Be kind, philos aren't aliens.\n");
		return (false);
	}
	return (true);
}

bool	check_arg_value(const char *argv)
{
	if (ft_atoi(argv) == 0 && ft_strchr(argv, '-') && ft_strlen(argv) > 7)
		return (false);
	return (true);
}
