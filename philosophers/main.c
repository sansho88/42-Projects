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
	//printf("[%s2] timestamp(%u) vs time(%u)\n", __func__,timestamp, time);
}

void	print_act(t_philo *philo, const char *act, bool finish)
{
	useconds_t		timestamp;
	struct timeval	temps;
	pthread_mutex_t	mtx;

	if (philo->letsgo == false)
		return ;
	pthread_mutex_init(&mtx, NULL);
	pthread_mutex_lock(&mtx);
	gettimeofday(&temps, NULL);
	timestamp = TIMESTAMP;//temps.tv_usec / 1000 - philo.birth.tv_usec / 1000;
	//dprintf(2, "[BIRTH]%ld vs timestamp(%u)\n", philo.birth.tv_usec, timestamp);
	if (finish == false)
	{
		printf("[%dms]\t%d is %sing\n", timestamp, (int)philo->id, act);
		pthread_mutex_unlock(&mtx);
		pthread_mutex_destroy(&mtx);
	}
	else
		printf("[%dms]\t%d died T-T\n",timestamp, (int)philo->id);
}

bool	eat(t_philo *philo, useconds_t time)
{
	struct timeval	temps;

	think(*philo);
	pthread_mutex_lock(&philo->fork);
	gettimeofday(&temps, NULL);
	printf("[%ldms]\t%zu has taken his fork (%p)\n",TIMESTAMP, philo->id, &philo->fork);
	if (philo->nb_philos < 2)
	{
		philo->isalive = false;
		return (false);
	}
	pthread_mutex_lock(philo->nextfork);
	gettimeofday(&temps, NULL);
	printf("[%ldms]\t%zu has taken an other fork (%p)\n",
		   TIMESTAMP, philo->id, philo->nextfork);
	print_act(philo, __func__, false);
	myusleep(time);
	/*if ((temps.tv_usec - philo->lastmeal.tv_usec) >= philo->lifetime)
	{
		nb_locks -= 2;
		philo->isalive = false;
		printf("[%ldms]\t%d died (time vs starve = %ld vs %ld)\n", TIMESTAMP,
			   (int)philo->id, (temps.tv_usec - philo->lastmeal.tv_usec), philo->starve);
		return (false);
	}*/
	gettimeofday(&philo->lastmeal, NULL);
	/*if (isphilo_alive(philo))
	{*/
		pthread_mutex_unlock(&philo->fork);
		pthread_mutex_unlock(philo->nextfork);
		return (true);
	//}
	return (false);
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

void turnoff_philos(size_t nb_philos, t_philo **cavern)
{
	size_t	i;

	i = 0;
	while (i < nb_philos)
	{
		cavern[0][i].letsgo = false;
		i++;
	}
}

bool	isphilo_alive(t_philo *philo)
{
	pthread_mutex_t	checker;
	bool			answer;

	pthread_mutex_init(&checker, NULL);
	pthread_mutex_lock(&checker);
	answer = philo->isalive;
	pthread_mutex_unlock(&checker);
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
	while (isphilo_alive(philo)) {
		gettimeofday(&temps, NULL);
		if ((temps.tv_sec * 1000 + temps.tv_usec / 1000 ) - (philo->lastmeal.tv_sec * 1000 + philo->lastmeal.tv_usec / 1000) >= philo->lifetime){//(temps.tv_usec / 100 - philo->lastmeal.tv_usec / 100) >= philo->starve) {
			dprintf(2, "[%s]lastmeal(=%ld) >= philo->starve(%ld)\n",
					__func__,  (temps.tv_sec * 1000 + temps.tv_usec / 1000 ) - (philo->lastmeal.tv_sec * 1000 + philo->lastmeal.tv_usec / 1000), philo->lifetime);
			philo->isalive = false;
			//dprintf(2, "lastmeal=%ld\n", philo->lastmeal.tv_usec);
			print_act(philo, "died", true);
			//exit(-42);
		}
		usleep(10);
	}
	gettimeofday(&temps, NULL);
	printf("[%ldms]\t%d died (philo health checker)\n", TIMESTAMP, (int) philo->id);
	if (philo->letsgo)
		turnoff_philos(philo->nb_philos, philo->cavern);

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
	while (philo->letsgo == false)
		usleep(1);
	//pthread_mutex_init(&secure, NULL);
	//dprintf(2, "[%s] %zu start: %d\n", __func__ , philo->id, philo->isalive);
	gettimeofday(&temps, NULL);
	//philo->birth = temps;
	//printf("[%ldms]\troutine of philo[%d]\n", TIMESTAMP, (int)philo->id);
	while (isphilo_alive(philo))
	{
		if (philo->lastmeal.tv_usec - temps.tv_usec <= philo->lifetime)
		{
			if (eat(philo, philo->starve) && isphilo_alive(philo))
				dream(*philo, philo->resttime);
			/*else
				dprintf(2, "[%s]Something wrong happened\n", __func__);*/
		}
		else
			philo->isalive = false;
			//printf("[%ldms]\t%d died (routine)\n", (temps.tv_usec - philo->birth.tv_usec), (int)philo->id);
		//gettimeofday(&temps, NULL);
		//printf("Is philo[%zu] alive? %s\n", philo->id, philo->isalive ? "True" : "False");
	}
	//dprintf(2, "Fin de la routine de %zu\n", philo.id);
	return (NULL);
}

void	letsgo_philos(size_t nb_philos, t_philo **philos)
{
	size_t			i;
	struct timeval	start;

	i = 0;
	gettimeofday(&start, NULL);
	//dprintf(2, "[%s]\n", __func__ );
	while (i < nb_philos)
	{
		philos[0][i].letsgo = true;
		philos[0][i].birth = start;
		philos[0][i].lastmeal = start;
		//dprintf(2, "[%s]philos[0][%zu]\n", __func__, i);
		//dprintf(2, "[%s]&philo[%zu].birth=%ld\n", __func__ ,philos[0][i].id, philos[0][i].birth.tv_usec);
		i++;
	}
}

void	chain_philos(size_t nb_philos, t_philo *cavern, int argc, char **argv)
{
	size_t			cuffs;
	//struct timeval	time;
	bool			*everything_is_ok;

	cuffs = 0;
	everything_is_ok = malloc(sizeof(bool));
	*everything_is_ok = true;
	while (cuffs < nb_philos)
	{
		if (!welcome_philos(&cavern[cuffs], cuffs + 1, argv, argc))
			break ;
		pthread_mutex_init(&cavern[cuffs].fork, NULL);
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
	letsgo_philos(nb_philos, &cavern);
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
		if (pthread_join(cavern[corpses_cleaned++].philo, NULL) == 0)
			exit(84);
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
