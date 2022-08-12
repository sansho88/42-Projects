/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriffit <tgriffit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 12:03:55 by tgriffit          #+#    #+#             */
/*   Updated: 2022/08/12 13:25:55 by tgriffit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	struct timeval	start;
	useconds_t		timestamp;

	gettimeofday(&temps, NULL);
	//time = ((current.tv_sec * 1000 + current.tv_usec / 1000) - (data.start.tv_sec * 1000 + data.start.tv_usec / 1000));
	start = temps;
	timestamp = (temps.tv_sec * 1000 + temps.tv_usec / 1000) -
			(start.tv_sec * 1000 + start.tv_usec / 1000);
	//printf("[%s1] timestamp(%u) vs time(%u)\n", __func__,timestamp, time);
	while (timestamp < time)//(temps.tv_usec - start < time)
	{
		usleep(1);
		gettimeofday(&temps, NULL);
		timestamp =(temps.tv_sec * 1000 + temps.tv_usec / 1000 )- (start.tv_sec * 1000 + start.tv_usec / 1000);
	}
	//printf("[%s2] ft_timer(philo)(%u) vs time(%u)\n", __func__,ft_timer(philo), time);
}

void	print_act(t_philo *philo, const char *act, bool finish)
{
	struct timeval	temps;

	if (*philo->letsgo == false)
		return ;
	pthread_mutex_lock(&philo->mtxlist.print);
	gettimeofday(&temps, NULL);
	//temps.tv_usec / 1000 - philo.birth.tv_usec / 1000;
	//dprintf(2, "[BIRTH]%ld vs timestamp(%u)\n", philo.birth.tv_usec, timestamp);
	if (finish == false)
	{
		printf("[%ldms]\t%d is %sing\n", ft_timer(philo), (int)philo->id, act);
		pthread_mutex_unlock(&philo->mtxlist.print);
		//pthread_mutex_destroy(&mtx);
	}
	else
		printf("[%ldms]\t%d died T-T\n", ft_timer(philo), (int)philo->id);
}

bool	eat(t_philo *philo, useconds_t time)
{
	struct timeval	temps;

	think(*philo);
	pthread_mutex_lock(&philo->fork);
	gettimeofday(&temps, NULL);
	printf("[%ldms]\t%zu has taken his fork (%p)\n",ft_timer(philo), philo->id, &philo->fork);
	if (philo->nb_philos < 2)
	{
		philo->isalive = false;
		return (false);
	}
	pthread_mutex_lock(philo->nextfork);
	gettimeofday(&temps, NULL);
	gettimeofday(&philo->lastmeal, NULL);
	printf("[%ldms]\t%zu has taken an other fork (%p)\n", ft_timer(philo),
		philo->id, philo->nextfork);
	print_act(philo, __func__, false);
	myusleep(time);
	pthread_mutex_unlock(&philo->fork);
	pthread_mutex_unlock(philo->nextfork);
	return (true);
}

void	dream(t_philo philo, useconds_t time)
{
	print_act(&philo, "sleep", false);
	myusleep(time);
}

void	think(t_philo philosoph)
{
	print_act(&philosoph, __func__, false);
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


long ft_timer(t_philo	*philo)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000) - (philo->birth.tv_sec *
			1000 + philo->birth.tv_usec / 1000);
}

bool	isphilo_alive(t_philo *philo)
{
	bool			answer;

	pthread_mutex_lock(&philo->mtxlist.is_philo_alive);
	answer = philo->isalive;
	//if (answer == true)
	pthread_mutex_unlock(&philo->mtxlist.is_philo_alive);
	return (answer);
}

void	*check_philo_health(void *philosoph) //fixme: faire en sorte que la mort stop tout (mutex?)
{
	struct timeval	temps;
	t_philo			*philo;

	philo = (t_philo *)philosoph;
	gettimeofday(&temps, NULL);
	/*dprintf(2, "[%s]&philo[%zu].fork:%p\nphilo.nextfork:%p\n", __func__, philo->id, &philo->fork, philo->nextfork);*/
	/*dprintf(2, "[%s]&philo[%zu].birth=%ld\n", __func__ ,philo->id, philo->birth.tv_usec);
	dprintf(2, "[%s]&philo[%zu].letsgo=%d\n", __func__ ,philo->id, philo->letsgo);*/
	while (isphilo_alive(philo))
	{
		gettimeofday(&temps, NULL);
		if ((temps.tv_sec * 1000 + temps.tv_usec / 1000) - (philo->lastmeal.tv_sec * 1000 + philo->lastmeal.tv_usec / 1000) >= philo->lifetime){//(temps.tv_usec / 100 - philo->lastmeal.tv_usec / 100) >= philo->starve) {
			/*dprintf(2, "[%s: %zu]lastmeal(=%ld) >= philo->lifetime(%d)\n",
					__func__,philo->id, (temps.tv_sec * 1000 + temps.tv_usec / 1000 ) - (philo->lastmeal.tv_sec * 1000 + philo->lastmeal.tv_usec / 1000), philo->lifetime);*/
			philo->isalive = false;
			//dprintf(2, "[id: %zu]lastmeal=%d\n", philo->id, philo->lastmeal.tv_usec);
			//print_act(philo, "died", true);
			//exit(-42);
		}
		usleep(10);
	}
	print_act(philo, "died", true);
	*philo->letsgo = false;
	gettimeofday(&temps, NULL);
	//printf("[%ldms]\t%d died (philo health checker)\n", ft_timer(philo), (int) philo->id);

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
	philo->mtxlist = init_mutexs();
	gettimeofday(&philo->lastmeal, NULL); //toplace after infinite loop before start
	philo->resttime = ft_atoi(argv[4]);
	if (argc == 6)
		philo->nb_meals = ft_atoi(argv[5]);
	if (philo->lifetime <= 0 || philo->starve <= 0 || philo->resttime <= 0)
		return (0);
	philo->isalive = true;
	pthread_create(&health_check, NULL, &check_philo_health, &philo->philo);
	pthread_detach(health_check);
	return ((size_t)ft_atoi(argv[1]));
}

void	*routine(void *philosoph)
{
	struct timeval	temps;
	t_philo			*philo;

	philo = (t_philo *)philosoph;
	//dprintf(2, "[%s:%zu]philo->letsgo=%d\n", __func__, philo->id, *philo->letsgo);
	while (*philo->letsgo == false)
		usleep(1);
	//dprintf(2, "[%s]philo->letsgo=%d\n", __func__, *philo->letsgo);
	gettimeofday(&temps, NULL);
	while (*philo->letsgo == true)
	{
		eat(philo, philo->starve);//if (eat(philo, philo->starve))
		dream(*philo, philo->resttime);
	}
	return (NULL);
}

void letsgo_philos(size_t nb_philos, t_philo **philos, bool *letsgo)
{
	size_t			i;
	struct timeval	start;

	i = 0;
	gettimeofday(&start, NULL);
	//dprintf(2, "[%s]\n", __func__ );
	while (i < nb_philos)
	{
		//philos[0][i].letsgo = true;
		//dprintf(2, "[%s]philos[0][%zu].letsgo=%d\n", __func__,i, *philos[0][i].letsgo);
		philos[0][i].birth = start;
		philos[0][i].lastmeal = start;
		myusleep(i % 1 == 0);
		i++;
	}
	gettimeofday(&start, NULL);
	*letsgo = true;
}

t_mtx	init_mutexs(void)
{
	t_mtx	mtx_initiated;

	pthread_mutex_init(&mtx_initiated.print, NULL);
	pthread_mutex_init(&mtx_initiated.is_philo_alive, NULL);
	return (mtx_initiated);
}

void	chain_philos(size_t nb_philos, t_philo *cavern, int argc, char **argv)
{
	size_t			cuffs;
	bool			letsgo;

	cuffs = 0;
	letsgo = false;
	while (cuffs < nb_philos)
	{
		if (!welcome_philos(&cavern[cuffs], cuffs + 1, argv, argc))
			break ;
		pthread_mutex_init(&cavern[cuffs].fork, NULL);
		cavern[cuffs].letsgo = &letsgo;
		cavern[cuffs].nb_philos = nb_philos;
		if (cuffs > 0 && nb_philos > 1)
			cavern[cuffs - 1].nextfork = &cavern[cuffs].fork;
		else
			cavern[0].nextfork = &cavern[0].fork;
		cavern[cuffs].nextfork = &cavern[(cuffs + 1) % nb_philos].fork;
		cavern[cuffs].cavern = &cavern;
		cuffs++;
		/*gettimeofday(&time, NULL);
		cavern[cuffs].birth = time;*/
	}
	cuffs = -1;
	while (++cuffs < nb_philos)
		pthread_create(&cavern[cuffs].philo, NULL, &routine, &cavern[cuffs]);
	letsgo_philos(nb_philos, &cavern, &letsgo);
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
		//printf("Trying to join philo[%zu]\n", cavern[corpses_cleaned].id);
		pthread_join(cavern[corpses_cleaned++].philo, NULL);
		//pthread_detach(cavern[corpses_cleaned++].philo);
		printf("philo[%zu]joined.\n", cavern[corpses_cleaned - 1].id);
	}
	printf("Cavern cleaned.\n");
	free(cavern);
}

int	main(int argc, char **argv) //FIXME: 5 800 200 200
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
