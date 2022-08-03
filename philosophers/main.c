/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriffit <tgriffit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 12:03:55 by tgriffit          #+#    #+#             */
/*   Updated: 2022/04/15 17:50:13 by tgriffit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
int nb_locks = 0;

size_t	ft_strlen(const char *string)
{
	size_t i;

	i = 0;
	while (string[i])
		i++;
	return (i);
}

void	myusleep(useconds_t time)
{
	struct timeval	temps;
	useconds_t		start;

	gettimeofday(&temps, NULL);
	start = temps.tv_usec;
	while (temps.tv_usec - start < time)
		gettimeofday(&temps, NULL);
}

void	print_act(t_philo philosoph, const char *act)
{
	useconds_t		timestamp;
	struct timeval	realtime;
	pthread_mutex_t	mtx;

	pthread_mutex_init(&mtx, NULL);
	if (philosoph.isalive)
	{
		pthread_mutex_lock(&mtx);
		gettimeofday(&realtime, NULL);
		timestamp = realtime.tv_usec / 1000 - philosoph.birth.tv_usec / 1000;
		printf("[%dms]\t%d is %sing\n",timestamp, (int)philosoph.id, act);
		pthread_mutex_unlock(&mtx);
	}
	pthread_mutex_destroy(&mtx);
}

bool	eat(t_philo *philo, useconds_t time) //todo: thread_detach for check if philo is alive
{
	struct timeval	temps;

	gettimeofday(&temps, NULL);
	pthread_mutex_lock(&philo->fork);
	pthread_mutex_lock(&philo->nextfork);
	nb_locks += 2;
	printf("[%ldms]\t%zu has taken an other fork\n",
		   (temps.tv_sec * 1000 + temps.tv_usec / 1000) - (philo->birth.tv_sec * 1000 + philo->birth.tv_usec / 1000), philo->id);
	printf("philo->fork vs nextfork = %p vs %p\n", &philo->fork, &philo->nextfork);
	/*while (!philo->fork && !philo->nextfork)
	{
		printf("Philo[%zu] is trying to eat, but fork[%zu] is taken\n",
			philo->id, philo->id + 1);
		myusleep(1);
	}*/
	if ((temps.tv_usec / 100 - philo->lastmeal.tv_usec / 100) >= philo->starve)
	{
		nb_locks -= 2;
		philo->isalive = false;
		printf("[%ldms]\t%d died (time vs starve = %ld vs %ld)\n", (temps.tv_usec / 1000 - philo->birth.tv_usec / 1000),
			   (int)philo->id, (temps.tv_usec / 100 - philo->lastmeal.tv_usec / 100), philo->starve);
		return (false);
	}
	dprintf(2,"doubidou\n");
	print_act(*philo, __func__);
	gettimeofday(&philo->lastmeal, NULL);
	myusleep(time);
	/*philo->fork = true;
	philo->nextfork = true;*/
	pthread_mutex_unlock(&philo->fork);
	pthread_mutex_unlock(&philo->nextfork);
	nb_locks -= 2;
	return (true);
}

void	dream(t_philo philo, useconds_t time)
{
	struct timeval	realtime;

	gettimeofday(&realtime, NULL);
	print_act(philo, "sleep");
	myusleep(time);
}

void	think(t_philo philosoph, useconds_t time)
{
	struct timeval	realtime;

	gettimeofday(&realtime, NULL);
	print_act(philosoph, __func__);
	myusleep(time);
}

bool	check_args(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
	{
		puts("Correct usage: ./philo [number_of_philosophers] [time_to_die] "
			"[time_to_eat] [time_to_sleep] "
			"(number_of_times_each_philosopher_must_eat)\n");
		return (false);
	}
	if (!ft_str_isdigit(argv + 1, argc - 1))
	{
		puts("At least one of the args isn't a number. "
			"Be kind, philos aren't aliens.\n");
		return (false);
	}
	return (true);
}

void	*check_philo_health(void *philosoph) //fixme: faire en sorte que la mort stop tout (mutex?)
{
	struct timeval	temps;
	t_philo			*philo;
	
	philo = (t_philo *)philosoph;
	while (philo->isalive) {
		gettimeofday(&temps, NULL);
		if ((temps.tv_usec / 100 - philo->lastmeal.tv_usec / 100) >= philo->starve) {
			philo->isalive = false;
			printf("[%ldms]\t%d died (philo health checker)\n", (temps.tv_usec / 1000 - philo->birth.tv_usec / 1000),
				   (int) philo->id);
			//exit(-42);
		}
	}

	return (NULL);
}

/**
 * Returns the amount of philosophers welcomed into the cavern.\n
 * If something went wrong, nobody will be allowed.
 * @param philo = Philosoph who will be checked
 * @param id = his/her ID card
 * @param argv
 * @return
 */
size_t	welcome_philos(t_philo *philo, size_t id, char **argv, int argc)
{
	pthread_t	health_check;

	if (!check_args(argc, argv))
		return (0);
	philo->id = id;
	philo->lifetime = ft_atoi(argv[2]);
	philo->starve = ft_atoi(argv[3]);
	gettimeofday(&philo->lastmeal, NULL);
	philo->resttime = ft_atoi(argv[4]);
	if (argc == 6)
		philo->nb_meals = ft_atoi(argv[5]);
	if (philo->lifetime <= 0 || philo->starve <= 0 || philo->resttime <= 0)
		return (0);
	pthread_mutex_init(&philo->fork, NULL);
	philo->isalive = true;
	pthread_create(&health_check, NULL, &check_philo_health, &philo->philo);
	pthread_detach(health_check);
	return ((size_t)ft_atoi(argv[1]));
}

void	*routine(void *philosoph)
{
	struct timeval	time;
	t_philo			philo;

	philo = (*(t_philo *)philosoph);
	//pthread_mutex_init(&secure, NULL);
	gettimeofday(&time, NULL);
	while (time.tv_usec - philo.birth.tv_usec >= philo.lifetime && philo.isalive) //FIXME: Infinite loop
	{
		printf("[%ldms]\troutine of philo[%d]\n", (time.tv_usec - philo.birth.tv_usec),
			   (int)philo.id);
		if (philo.lastmeal.tv_usec - time.tv_usec <= philo.starve && philo.isalive)
		{
			if (eat(&philo, philo.starve))
			{
				dream(philo, philo.resttime);
				think(philo, 8);
			}
			else
				dprintf(2, "[%s]Something wrong happened\n", __func__);
		}
		else
			printf("[%ldms]\t%d died (routine)\n", (time.tv_usec - philo.birth.tv_usec),
				   (int)philo.id);
		gettimeofday(&time, NULL);
		//printf("Is philo[%zu] alive? %s\n", philo.id, philo.isalive ? "True" : "False");
		printf("Numbers locks = %d\n", nb_locks);
	}
	//dprintf(2, "Fin de la routine de %zu\n", philo.id);
	return (NULL);
}

void	chain_philos(size_t nb_philos, t_philo *cavern, int argc, char **argv)
{
	struct timeval	temps;
	size_t			cuffs;
	bool			*everything_is_ok;

	cuffs = 0;
	gettimeofday(&temps, NULL);
	everything_is_ok = malloc(sizeof(bool));
	*everything_is_ok = true;
	while (cuffs < nb_philos)
	{
		if (!welcome_philos(&cavern[cuffs], cuffs + 1, argv, argc))
			break ;
		if (nb_philos > 1)
			cavern[cuffs].nextfork = cavern[(cuffs + 1) % nb_philos].fork;
		else
		{
			printf("[%ldms] %zu died.\n", cavern[0].starve, cavern[0].id);
			cavern[0].isalive = false;
		}
		cavern[cuffs].birth = temps;
		cuffs++;
	}
	cuffs = -1;
	while (++cuffs < nb_philos)
	{
		pthread_create(&cavern[cuffs].philo, NULL, &routine, &cavern[cuffs]);
	}
}

void	get_away_corpses(size_t nb_philos, t_philo *cavern)
{
	size_t	corpses_cleaned;

	corpses_cleaned = 0;
	while (corpses_cleaned < nb_philos)
	{
		//pthread_mutex_destroy(&cavern[corpses_cleaned].fork);
		/*if (!cavern[corpses_cleaned].isalive){
			break ;
		}*/
		printf("Trying to join philo[%zu]\n", cavern[corpses_cleaned].id);
		pthread_join(cavern[corpses_cleaned++].philo, NULL);
		printf("philo[%zu]joined.\n", cavern[corpses_cleaned - 1].id);
	}
	printf("Cavern cleaned.\n");
	free(cavern);
}

int	main(int argc, char **argv)
{
	struct timeval	temps;
	//suseconds_t		times[2];
	t_philo			*cavern;
	size_t			nb_philos;

	if (!check_args(argc, argv))
		return (-2);
	nb_philos = ft_atoi(argv[1]);
	gettimeofday(&temps, NULL);
	//times[0] = temps.tv_sec * 1000 + temps.tv_usec / 1000;
	cavern = malloc(sizeof(t_philo) * nb_philos);
	chain_philos(nb_philos, cavern, argc, argv);
	get_away_corpses(nb_philos, cavern);
	/*gettimeofday(&temps, NULL);
	times[1] = temps.tv_sec * 1000 + temps.tv_usec / 1000;
	printf("Time elapsed = %ums\n", times[1] - times[0]);*/
	return (0);
}
