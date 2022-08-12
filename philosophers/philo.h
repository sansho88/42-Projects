/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriffit <tgriffit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 14:17:48 by tgriffit          #+#    #+#             */
/*   Updated: 2022/08/12 12:45:35 by tgriffit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdbool.h>
# include <unistd.h>
# include <stdlib.h>

# define TIMESTAMP (temps.tv_sec * 1000 + temps.tv_usec / 1000) - (philo->birth.tv_sec * 1000 + philo->birth.tv_usec / 1000)

typedef struct s_mtx{
	pthread_mutex_t	print;
	pthread_mutex_t	is_philo_alive;
}	t_mtx;

typedef struct s_philo{
	pthread_t		philo;
	size_t			id;
	suseconds_t		lifetime;
	suseconds_t		resttime;
	suseconds_t		starve; //Speed for eat
	int				nb_meals; //TODO
	bool			isalive;
	struct timeval	birth;
	struct timeval	lastmeal;
	pthread_mutex_t	fork;
	pthread_mutex_t	*nextfork;
	size_t			nb_philos;
	bool			*letsgo;
	struct s_philo	**cavern;
	t_mtx			mtxlist;
}	t_philo;

int			ft_str_isdigit(char **str, size_t size);
int			ft_isdigit(int c);
int			ft_atoi(const char *str);
void		dream(t_philo philo, useconds_t time);
void		think(t_philo philosoph);
bool		eat(t_philo *philo, useconds_t time);
bool		isphilo_alive(t_philo *philo);
t_mtx		init_mutexs(void);
long		ft_timer(t_philo	*philo);

#endif
