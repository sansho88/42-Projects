/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriffit <tgriffit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 11:37:22 by tgriffit          #+#    #+#             */
/*   Updated: 2022/08/19 12:36:54 by tgriffit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	ft_timer(t_world world)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000 + time.tv_usec / 1000)
		- (world.start.tv_sec * 1000 + world.start.tv_usec / 1000));
}

void	myusleep(useconds_t time)
{
	struct timeval	temps;
	struct timeval	start;
	useconds_t		timestamp;

	gettimeofday(&temps, NULL);
	start = temps;
	timestamp = (temps.tv_sec * 1000 + temps.tv_usec / 1000)
		- (start.tv_sec * 1000 + start.tv_usec / 1000);
	while (timestamp < time)
	{
		usleep(10);
		gettimeofday(&temps, NULL);
		timestamp = (temps.tv_sec * 1000 + temps.tv_usec / 1000)
			- (start.tv_sec * 1000 + start.tv_usec / 1000);
	}
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

void	init_world(t_world *world, int argc, char **argv)
{
	pthread_mutex_init(&world->check_go, NULL);
	world->go = false;
	gettimeofday(&world->start, NULL);
	world->argv = argv;
	world->argc = argc;
}

bool	give_birth_to_philo(t_philo *philo, t_world *world)
{
	dprintf(2, "[%s]Lait avant les cereales\n", __func__ );
	philo->lifetime = ft_atoi(world->argv[2]);
	philo->time4eat = ft_atoi(world->argv[3]);
	philo->sleeptime = ft_atoi(world->argv[4]);
	dprintf(2, "[%s]Chocapic\n", __func__ );
	if (world->argc == 6)
		philo->nb_meals = ft_atoi(world->argv[5]);
	dprintf(2, "[%s]Nesquick\n", __func__ );
	if (philo->lifetime <= 0 || philo->time4eat <= 0 || philo->sleeptime <= 0)
		return (false);
	dprintf(2, "[%s]Miel Pops\n", __func__ );
	return (true);
}

bool	place_philos_in_cavern(t_philo **cavern, t_world *world)
{
	size_t	i;

	i = 0;
	while (i < world->nb_philos)
	{
		if (!give_birth_to_philo(cavern[i], world))
		{
			puts("et merde");
			return (false);
		}
		if (i > 0 && world->nb_philos > 1)
			cavern[i - 1]->nextfork = &cavern[i]->fork;
		else
			cavern[0]->nextfork = &cavern[0]->fork;
		cavern[i]->nextfork = &cavern[(i + 1) % world->nb_philos]->fork; //fixme
		i++;
	}
	return (true);
}

bool	try_to_use(pthread_mutex_t *mutex, bool value_to_check)
{
	bool	answer;

	pthread_mutex_lock(mutex);
	answer = value_to_check;
	pthread_mutex_unlock(mutex);
	return (answer);
}

void	print_act(char *msg, t_philo philo, t_world *world)
{
	if (try_to_use(&world->check_go, world->go))
		printf("[%ld]\t%i %s\n", ft_timer(*world), philo.id, msg);
}

void	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->fork);
	print_act("has taken his fork", *philo, philo->world);
	pthread_mutex_lock(philo->nextfork);
	print_act("has taken an other fork", *philo, philo->world);
	print_act("is eating", *philo, philo->world);
	gettimeofday(&philo->lastmeal, NULL);
	myusleep(philo->time4eat);
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
	dprintf(2, "[%s]before while\n", __func__ );
	while (!try_to_use(&philo->world->check_go, philo->world->go))
		usleep('*');
	dprintf(2, "[%s]after while\n", __func__ );
	while (try_to_use(&philo->world->check_go, philo->world->go))
	{
		print_act("is thinking", *philo, philo->world);
		eat(philo);
		dream(philo);
	}
	return (NULL);
}

void	light_on_cavern(t_philo *cavern, t_world *world)
{
	size_t	i;

	i = 0;
	pthread_mutex_lock(&world->check_go);
	dprintf(2, "[%s]world->nb_philos = %zu\n", __func__, world->nb_philos);
	while (i < world->nb_philos)
	{
		printf("%p\n",&cavern[i].philo);
		if (!pthread_create(&cavern[i].philo, NULL, &routine, &cavern[i]))
		{
			printf("[%i]\n",cavern[i].id);
			//return ;
		}
		i++;
	}
	gettimeofday(&world->start, NULL);
	world->go = true;
	pthread_mutex_unlock(&world->check_go);
}

int	main(int argc, char **argv)
{
	t_world	world;
	t_philo	*cavern;

	if (!check_args(argc, argv))
		return (-2);
	init_world(&world, argc, argv);
	dprintf(2, "world initiated\n");
	world.nb_philos = ft_atoi(argv[1]);
	cavern = malloc(sizeof(t_philo) * world.nb_philos);
	dprintf(2, "cavern construite\n");
	if (!cavern)
		return (MALLOC_ERR);
	place_philos_in_cavern(&cavern, &world);
	dprintf(2, "philos dans la cavern\n");
	light_on_cavern(cavern, &world);
	//todo: health_checker
}
