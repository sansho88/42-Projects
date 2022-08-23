/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriffit <tgriffit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 11:37:22 by tgriffit          #+#    #+#             */
/*   Updated: 2022/08/23 18:36:56 by tgriffit         ###   ########.fr       */
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
	pthread_mutex_init(&world->god_voice, NULL);
	world->go = false;
	gettimeofday(&world->start, NULL);
	world->argv = argv;
	world->argc = argc;
	world->nb_philos = ft_atoi(world->argv[1]);
	world->lifetime = ft_atoi(world->argv[2]);
	world->time4eat = ft_atoi(world->argv[3]);
	world->sleeptime = ft_atoi(world->argv[4]);
}

bool	give_birth_to_philo(t_philo *philo, t_world *world)
{
	philo->lifetime = world->lifetime;
	philo->time4eat = world->time4eat;
	philo->sleeptime = world->time4eat;
	gettimeofday(&philo->lastmeal, NULL);
	philo->world = world;
	pthread_mutex_init(&philo->fork, NULL);
	if (world->argc == 6)
		philo->nb_meals = ft_atoi(world->argv[5]);
	if (philo->lifetime <= 0 || philo->time4eat <= 0 || philo->sleeptime <= 0)
		return (false);
	return (true);
}

bool	place_philos_in_cavern(t_philo *cavern, t_world *world)
{
	size_t	i;

	i = 0;
	while (i < world->nb_philos)
	{
		if (!give_birth_to_philo(&cavern[i], world))
			return (false);
		cavern[i].id = i + 1;
		i++;
	}
	i = 0;
	while (i < world->nb_philos)
	{
		if (world->nb_philos > 1)
			cavern[i].nextfork = &cavern[(i + 1) % world->nb_philos].fork;
		i++;
	}
	return (true);
}

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

void	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->fork);
	print_act("has taken his fork", *philo, philo->world);
	if (philo->world->nb_philos == 1)
	{
		print_act("died", *philo, philo->world);
		pthread_mutex_lock(&philo->world->check_go);
		philo->world->go = false;
		pthread_mutex_unlock(&philo->world->check_go);
		return ;
	}
	pthread_mutex_lock(philo->nextfork);
	print_act("has taken an other fork", *philo, philo->world);
	print_act("is eating", *philo, philo->world);
	gettimeofday(&philo->lastmeal, NULL);
	myusleep(philo->time4eat);
//	usleep(philo->time4eat * 1000);
	pthread_mutex_unlock(&philo->fork);
	pthread_mutex_unlock(philo->nextfork);
}

void	dream(t_philo *philo)
{
	print_act("is sleeping", *philo, philo->world);
	myusleep(philo->sleeptime);
	//usleep(philo->sleeptime * 1000);
}

void	*routine(void	*philosoph)
{
	t_philo	*philo;

	philo = philosoph;
	while (!try_to_use(&philo->world->check_go, &philo->world->go))
		usleep('*');
	while (try_to_use(&philo->world->check_go, &philo->world->go))
	{
	//	if (try_to_use(&philo->world->check_go, &philo->world->go))
			print_act("is thinking", *philo, philo->world);
		//else
		//	return (NULL);
	//	if (try_to_use(&philo->world->check_go, &philo->world->go))
			eat(philo);
	//	else
	//		return (NULL);
	//	if (try_to_use(&philo->world->check_go, &philo->world->go))
			dream(philo);
	//	else
	}
	return (NULL);
}

void *health_checker(void	*void_world)
{
	t_world	*world;
	t_philo	*cavern;
	long	lastmealtime;
	size_t	i;

	world = (t_world *)void_world;
	cavern = world->cavern;
	i = 0;
	while (true)
	{
		lastmealtime = (cavern[i].lastmeal.tv_sec * 1000
				+ cavern[i].lastmeal.tv_usec / 1000)
			- (world->start.tv_sec * 1000 + world->start.tv_usec / 1000);
		if (ft_timer(*world) - lastmealtime >= cavern[i].lifetime)
		{
			pthread_mutex_lock(&world->check_go);
			put_in_coffin(world->dead_philo, &cavern[i], cavern->world);
			world->go = false;
			pthread_mutex_unlock(&world->check_go);
			return (NULL);
		}
		i = ((i + 1) % world->nb_philos) - 1;
		usleep('*');
	}
}

void	light_on_cavern(t_philo *cavern, t_world *world, size_t nb_philos)
{
	size_t		i;
	pthread_t	doctor;

	i = 0;
	pthread_mutex_lock(&world->check_go);
	while (i < nb_philos)
	{
		if (pthread_create((&cavern[i].philo), NULL, &routine, &cavern[i]) != 0)
			return ;
		i++;
	}
	gettimeofday(&world->start, NULL);
	world->cavern = cavern;
	dprintf(2, "[%s]&cavern=%p\n",__func__, &world->cavern);
	pthread_create(&doctor, NULL, &health_checker, world);
	world->go = true;
	dprintf(2, "go go go %d\n", world->go);
	pthread_mutex_unlock(&world->check_go);
	pthread_join(doctor, NULL);
}

void	unchain_philos(t_philo *cavern)
{
	size_t	i;

	i = 0;
	while (i < cavern->world->nb_philos)
	{
		pthread_join(cavern[i].philo, NULL);
		pthread_mutex_destroy(&cavern[i].fork);
		i++;
	}
	announce_death_to_family(*cavern->world->dead_philo, cavern->world);
	pthread_mutex_destroy(&cavern->world->check_go);
	pthread_mutex_destroy(&cavern->world->god_voice);
}

void put_in_coffin(t_corpse *corpse, t_philo *philo, t_world	*world)
{
	corpse->dead_philo = philo;
	corpse->time_of_death = ft_timer(*world);
	world->dead_philo = corpse;
}

void announce_death_to_family(t_corpse corpse, t_world *world)
{
	pthread_mutex_lock(&world->god_voice);
	printf("[%ld]\t%i %s\n", corpse.time_of_death, corpse.dead_philo->id, "died");
	pthread_mutex_unlock(&world->god_voice);
}

int	main(int argc, char **argv)
{
	t_world		world;
	t_philo		*cavern;
	t_corpse	dead_philo;

	if (!check_args(argc, argv))
		return (-2);
	init_world(&world, argc, argv);
	world.dead_philo = &dead_philo;
	cavern = malloc(sizeof(t_philo) * world.nb_philos);
	if (!cavern)
		return (MALLOC_ERR);
	place_philos_in_cavern(cavern, &world);
	light_on_cavern(cavern, &world, world.nb_philos);
	unchain_philos(cavern);
}
