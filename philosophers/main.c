/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriffit <tgriffit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 12:03:55 by tgriffit          #+#    #+#             */
/*   Updated: 2022/08/16 18:34:25 by tgriffit         ###   ########.fr       */
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
		usleep(10);
		gettimeofday(&temps, NULL);
		timestamp =(temps.tv_sec * 1000 + temps.tv_usec / 1000 )- (start.tv_sec * 1000 + start.tv_usec / 1000);
	}
	//printf("[%s2] ft_timer(philo)(%u) vs time(%u)\n", __func__,ft_timer(philo), time);
}

void	print_act(t_philo *philo, const char *act, bool finish)
{
	struct timeval	temps;

	if (!look_at_shadows(*philo->torch->letsgo, &philo->torch->check_letsgo))
	{
		//printf("[%s]id: %zu| peut pas manger ta race yo, fdpoulpe\n", __func__, philo->id);
		return ;
	}
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
	pthread_mutex_lock(&philo->check_lastmeal);
	gettimeofday(&philo->lastmeal, NULL);
	pthread_mutex_unlock(&philo->check_lastmeal);
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


bool	look_at_shadows(bool value, pthread_mutex_t *mutex)
{
	bool	answer;

	pthread_mutex_lock(mutex);
	answer = value;
	pthread_mutex_unlock(mutex);
	return (answer);
}

bool	isgotrue(t_philo philo)
{
	bool			answer;

	pthread_mutex_lock(&philo.mtxlist.is_go_true);
	answer = *philo.letsgo;
	pthread_mutex_unlock(&philo.mtxlist.is_go_true);
	return (answer);
}

void	*check_philo_health(void *void_torch) //fixme: faire en sorte que la mort stop tout (mutex?)
{
	struct timeval	temps;
	t_torch			torch;
	t_philo			*philo;
	size_t			i;

	torch = *(t_torch *) void_torch;
	philo = *torch.cavern;
	gettimeofday(&temps, NULL);
	/*dprintf(2, "[%s]&philo[%zu].fork:%p\nphilo.nextfork:%p\n", __func__, philo->id, &philo->fork, philo->nextfork);*/
	/*dprintf(2, "[%s]&philo[%zu].birth=%ld\n", __func__ ,philo->id, philo->birth.tv_usec);
	dprintf(2, "[%s]&philo[%zu].letsgo=%d\n", __func__ ,philo->id, philo->letsgo);*/
	//printf( "[%s]LETSGO:%s...%p\n",__func__, *letsgo ? "True" : "False", letsgo);
	printf( "NTP\n");
	while (look_at_shadows(torch.letsgo, &torch.check_letsgo) == false) //FIXME
	{
		dprintf(1, "[%s:%zu]philo->letsgo=%d\n", __func__, philo->id, *philo->letsgo);
		usleep(10000);
	}
	//dprintf(1, "NTPOUET\n");
	while (isgotrue(philo[0]))
	{
		i = 0;
		*philo = philo[i];
		//printf( "NTP\n");
		while (i < philo[0].nb_philos)
		{
			//printf( "[%s]ISALIVE(%zu):%s...%p\n",__func__,philo[i].id ,philo->isalive ? "True" : "False", letsgo);
			gettimeofday(&temps, NULL);
			pthread_mutex_lock(&philo[i].check_lastmeal);
			if ((temps.tv_sec * 1000 + temps.tv_usec / 1000) - (philo[i].lastmeal.tv_sec * 1000 + philo[i].lastmeal.tv_usec / 1000) >= philo[i].lifetime){//(temps.tv_usec / 100 - philo->lastmeal.tv_usec / 100) >= philo->starve) {
				/*dprintf(2, "[%s: %zu]lastmeal(=%ld) >= philo->lifetime(%d)\n",
						__func__,philo->id, (temps.tv_sec * 1000 + temps.tv_usec / 1000 ) - (philo->lastmeal.tv_sec * 1000 + philo->lastmeal.tv_usec / 1000), philo->lifetime);*/
				dprintf(2, "[id: %zu]lastmeal=%d\n", philo->id, philo[i].lastmeal.tv_usec);
				philo[i].isalive = false;
				pthread_mutex_lock(&torch.check_letsgo);
				*torch.letsgo = false;
				pthread_mutex_unlock(&torch.check_letsgo);
				//printf( "NTP\n");
				//exit(-42);
				printf("[%ldms]\t%d died (philo health checker)\n", ft_timer(philo), (int) philo->id);
				return (NULL);
			}
			pthread_mutex_unlock(&philo[i].check_lastmeal);
			//usleep(10);
			i++;
		}
		//printf( "[%s]ISALIVE(%zu):%s...%p\n",__func__,philo[i].id ,philo->isalive ? "True" : "False", letsgo);
		//printf( "[%s]LETSGO:%s...%p\n",__func__, *letsgo ? "True" : "False", letsgo);
	}
	//printf( "[%s]LETSGO:%s...%p\n",__func__, *letsgo ? "True" : "False", letsgo);
	//print_act(philo, "died", true);
	//*philo->letsgo = false;
	gettimeofday(&temps, NULL);
	printf("[%ldms]\t%d died (philo health checker)\n", ft_timer(philo), (int) philo->id);

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
size_t	welcome_philos(t_philo *philo, size_t id, t_torch torch)
{
	//pthread_t	health_check;

	if (!check_args(torch.argc, torch.argv))
		return (0);
	philo->id = id;
	philo->lifetime = ft_atoi(torch.argv[2]);
	philo->starve = ft_atoi(torch.argv[3]);
	philo->mtxlist = init_mutexs();
	gettimeofday(&philo->lastmeal, NULL); //toplace after infinite loop before start
	philo->resttime = ft_atoi(torch.argv[4]);
	if (torch.argc == 6)
		philo->nb_meals = ft_atoi(torch.argv[5]);
	if (philo->lifetime <= 0 || philo->starve <= 0 || philo->resttime <= 0)
		return (0);
	philo->isalive = true;
	/*pthread_create(&health_check, NULL, &check_philo_health, &philo->philo);
	pthread_detach(health_check);*/
	return ((size_t)ft_atoi(torch.argv[1]));
}

void	*routine(void *philosoph)
{
	//struct timeval	temps;
	t_philo			*philo;
	t_torch			*torch;

	philo = (t_philo *)philosoph;
	philo->letsgo = philo->torch->letsgo;
	torch = philo->torch;
//	printf("[%s:%zu]philo->letsgo=%d\n", __func__, philo->id, *philo->letsgo);
while (!look_at_shadows(*torch->letsgo, &torch->check_letsgo))
		usleep(10);
	//dprintf(1, "[%s:%zu]philo->letsgo=%d\n", __func__, philo->id, *philo->letsgo);
	//gettimeofday(&temps, NULL);
	while (look_at_shadows(*torch->letsgo, &torch->check_letsgo))
	{
		if (eat(philo, philo->starve))//if (eat(philo, philo->starve))
			dream(*philo, philo->resttime);
	}
	return (NULL);
}

void letsgo_philos(size_t nb_philos, t_philo **philos)
{
	size_t			i;
	struct timeval	start;

	i = 0;
	//dprintf(2, "[%s]\n", __func__ );
	gettimeofday(&start, NULL);
	while (i < nb_philos)
	{
		//philos[0][i].letsgo = true;
		//dprintf(2, "[%s]philos[0][%zu].letsgo=%d\n", __func__,i, *philos[0][i].letsgo);
//		gettimeofday(&start, NULL);
		philos[0][i].birth = start;
		philos[0][i].lastmeal = start;
//		myusleep(i % 1 == 0);
		i++;
	}
	//gettimeofday(&start, NULL);
	pthread_mutex_lock(&philos[0]->mtxlist.is_go_true);
	*philos[0]->letsgo = true;
	pthread_mutex_unlock(&philos[0]->mtxlist.is_go_true);
	usleep(10);
	//make
	//printf( "[%s]LETSGO:%s...%p\n",__func__, *philos[0]->letsgo ? "True" : "False", philos[0]->letsgo);
}

t_mtx	init_mutexs(void)
{
	t_mtx	mtx_initiated;

	pthread_mutex_init(&mtx_initiated.print, NULL);
	pthread_mutex_init(&mtx_initiated.is_philo_alive, NULL);
	pthread_mutex_init(&mtx_initiated.is_go_true, NULL);
	return (mtx_initiated);
}

t_torch init_torch(t_philo **cavern, bool *letsgo, int argc, char **argv)
{
	t_torch			torch;
	size_t			i;

	torch.cavern = cavern;
	torch.letsgo = letsgo;
	torch.argc = argc;
	torch.argv = argv;
	pthread_mutex_init(&torch.check_letsgo, NULL);
	i = 0;
	while (i < cavern[0]->nb_philos)
	{
		cavern[i]->torch = &torch;
		i++;
	}
	return (torch);
}

void	chain_philos(size_t nb_philos, t_philo *cavern, t_torch torch)
{
	size_t			cuffs;

	cuffs = 0;
	while (cuffs < nb_philos)
	{
		if (!welcome_philos(&cavern[cuffs], cuffs + 1, torch))
			break ;
		pthread_mutex_init(&cavern[cuffs].fork, NULL);
		pthread_mutex_init(&cavern[cuffs].check_lastmeal, NULL);
		cavern[cuffs].nb_philos = nb_philos;
		cavern[cuffs].torch = &torch;
		if (cuffs > 0 && nb_philos > 1)
			cavern[cuffs - 1].nextfork = &cavern[cuffs].fork;
		else
			cavern[0].nextfork = &cavern[0].fork;
		cavern[cuffs].nextfork = &cavern[(cuffs + 1) % nb_philos].fork;
		cuffs++;
		/*gettimeofday(&time, NULL);
		cavern[cuffs].birth = time;*/
	}
	cuffs = -1;
	while (++cuffs < nb_philos)
	{
	//	printf("[%s]%zu\n",__func__, cuffs);
		pthread_create(&cavern[cuffs].philo, NULL, &routine, &cavern[cuffs]);
	}
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
		//printf("Trying to join philo[%zu]\n", cavern[corpses_cleaned].id);
		pthread_join(cavern[corpses_cleaned++].philo, NULL);
		//pthread_detach(cavern[corpses_cleaned++].philo);
		//printf("philo[%zu]joined.\n", cavern[corpses_cleaned - 1].id);
	}
	printf("Cavern cleaned.\n");
	free(cavern);
}

void	init_letsgo(t_philo *cavern, size_t nb_philo, bool *letsgo)
{
	size_t	i;

	i = 0;
	while (i < nb_philo)
	{
		cavern[i].letsgo = letsgo;
		i++;
	}
}

int	main(int argc, char **argv) //FIXME: 5 800 200 200
{
	//struct timeval	temps;
	t_torch			torch;
	bool			letsgo;
	t_philo			*cavern;
	pthread_t		checker;
	size_t			nb_philos;

	if (!check_args(argc, argv))
		return (-2);
	nb_philos = ft_atoi(argv[1]);
	//gettimeofday(&temps, NULL);
	//times[0] = temps.tv_sec * 1000 + temps.tv_usec / 1000;
	cavern = malloc(sizeof(t_philo) * nb_philos);
	init_letsgo(cavern, nb_philos, &letsgo);
	torch = init_torch(&cavern, &letsgo, argc, argv);
	pthread_create(&checker, NULL, check_philo_health, &torch);
	chain_philos(nb_philos, cavern, torch);
	//pthread_detach(checker);
	get_away_corpses(nb_philos, cavern);
	/*gettimeofday(&temps, NULL);
	times[1] = temps.tv_sec * 1000 + temps.tv_usec / 1000;
	printf("Time elapsed = %ums\n", times[1] - times[0]);*/
	return (0);
}
