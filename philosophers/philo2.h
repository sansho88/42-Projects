/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriffit <tgriffit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 14:17:48 by tgriffit          #+#    #+#             */
/*   Updated: 2022/08/16 17:46:46 by tgriffit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO2_H
# define PHILO2_H

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
	pthread_mutex_t	is_go_true;
}	t_mtx;

typedef struct s_torch{
	bool			*letsgo;
	pthread_mutex_t	check_letsgo;
	struct s_philo	**cavern;
	int				argc;
	char			**argv;
} t_torch;

typedef struct s_philo{
	pthread_t		philo;
	size_t			id;
	suseconds_t		lifetime;
	suseconds_t		resttime;
	suseconds_t		starve; //Speed for eat
	int				nb_meals; //TODO
	bool			isalive;
	t_torch			*torch;
	struct timeval	birth;
	struct timeval	lastmeal;
	pthread_mutex_t	check_lastmeal;
	pthread_mutex_t	fork;
	pthread_mutex_t	*nextfork;
	size_t			nb_philos;
	bool			*letsgo;
	t_mtx			mtxlist;
}	t_philo;

int			ft_str_isdigit(char **str, size_t size);
int			ft_isdigit(int c);
int			ft_atoi(const char *str);
void		dream(t_philo philo, useconds_t time);
void		think(t_philo philosoph);
bool		eat(t_philo *philo, useconds_t time);
bool		isphilo_alive(t_philo philo);
t_mtx		init_mutexs(void);
long		ft_timer(t_philo	*philo);
bool		isgotrue(t_philo philo);
bool		look_at_shadows(bool value, pthread_mutex_t *mtx);

#endif
