/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriffit <tgriffit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 14:17:48 by tgriffit          #+#    #+#             */
/*   Updated: 2022/04/12 15:06:58 by tgriffit         ###   ########.fr       */
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

typedef struct s_fork{
	pthread_mutex_t	isfree;
}	t_fork;

typedef struct s_philo{
	pthread_t		philo;
	size_t			id;
	suseconds_t		lifetime;
	suseconds_t		resttime;
	suseconds_t		starve; //Speed for eat
	int				nb_meals;
	bool			isalive;
	struct timeval	birth;
	struct timeval	lastmeal;
	pthread_mutex_t	fork;
	pthread_mutex_t	*nextfork;
	struct s_philo	*nextphilo;
	size_t			nb_philos;
	bool			letsgo;
}	t_philo;

int		ft_str_isdigit(char **str, size_t size);
int		ft_isdigit(int c);
int		ft_atoi(const char *str);
void	dream(t_philo philo, useconds_t time);
void	think(t_philo philosoph);
bool	eat(t_philo *philo, useconds_t time);

#endif
