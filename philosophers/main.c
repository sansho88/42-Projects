/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriffit <tgriffit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 11:37:22 by tgriffit          #+#    #+#             */
/*   Updated: 2022/08/23 11:35:29 by tgriffit         ###   ########.fr       */
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
		if (i > 0 && world->nb_philos > 1)
			cavern[i - 1].nextfork = &cavern[i].fork;
		else
			cavern[i].nextfork = &cavern[i].fork;
		cavern[i].nextfork = &cavern[(i + 1) % world->nb_philos].fork;
		i++;
	}
	return (true);
}

bool	try_to_use(pthread_mutex_t *mutex, bool *value_to_check)
{
	bool	answer;

	pthread_mutex_lock(mutex);
	answer = *value_to_check;
	pthread_mutex_unlock(mutex);
	return (answer);
}

void	print_act(char *msg, t_philo philo, t_world *world)
{
	pthread_mutex_lock(&world->god_voice);
	printf("[%ld]\t%i %s\n", ft_timer(*world), philo.id, msg);
	pthread_mutex_unlock(&world->god_voice);
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
	while (!try_to_use(&philo->world->check_go, &philo->world->go))
		usleep('*');
	while (true)
	{
		if (try_to_use(&philo->world->check_go, &philo->world->go))
			print_act("is thinking", *philo, philo->world);
		else
			return (NULL);
		if (try_to_use(&philo->world->check_go, &philo->world->go))
			eat(philo);
		else
			return (NULL);
		if (try_to_use(&philo->world->check_go, &philo->world->go))
			dream(philo);
		else
			return (NULL);
	}
}

void *health_checker(void	*void_world)
{
	t_world	*world;
	t_philo	*cavern;
	long	lastmealtime;
	size_t	i;

	world = (t_world *)void_world;
	dprintf(2, "[%s]&cavern=%p\n",__func__, world->cavern);
	cavern = world->cavern; //fixme : AddressSanitizer: heap-buffer-overflow
	i = 0;
	while (i < world->nb_philos)
	{
		//dprintf(2, "[%s]philo->id = %d\n",__func__, cavern[i].id);
		lastmealtime = (cavern[i].lastmeal.tv_sec * 1000
				+ cavern[i].lastmeal.tv_usec / 1000)
			- (world->start.tv_sec * 1000 + world->start.tv_usec / 1000);
		//dprintf(2, "[%s]ft_timer(*world) - lastmealtime = %ld\n", __func__, ft_timer(*world) - lastmealtime);
		if (ft_timer(*world) - lastmealtime >= cavern[i].lifetime)
		{
			pthread_mutex_lock(&world->check_go);
			print_act("died", cavern[i], world);
			world->go = false;
			pthread_mutex_unlock(&world->check_go);
			return (NULL);
		}
		i++;
		i %= world->nb_philos - 1;
		usleep('*');
		//puts("CHOCAPIC");
	}
	return (NULL);
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
	pthread_create(&doctor, NULL, &health_checker, world); //fixme: not same address
	world->go = true;
	dprintf(2, "go go go %d\n", world->go);
	pthread_mutex_unlock(&world->check_go);
	pthread_join(doctor, NULL);
}


int	main(int argc, char **argv)
{
	t_world	world;
	t_philo	*cavern;

	if (!check_args(argc, argv))
		return (-2);
	init_world(&world, argc, argv);
	cavern = malloc(sizeof(t_philo) * world.nb_philos);
	if (!cavern)
		return (MALLOC_ERR);
	place_philos_in_cavern(cavern, &world);
	light_on_cavern(cavern, &world, world.nb_philos);
	//todo: health_checker
	while (1) {
		usleep('-');
	}
}
