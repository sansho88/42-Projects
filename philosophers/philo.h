/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriffit <tgriffit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 11:40:08 by tgriffit          #+#    #+#             */
/*   Updated: 2022/08/22 17:16:49 by tgriffit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <string.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdbool.h>
# include <unistd.h>
# include <stdlib.h>

# define MALLOC_ERR 42

typedef struct s_world{
	size_t			nb_philos;
	pthread_mutex_t	check_go;
	pthread_mutex_t	god_voice;
	bool			go;
	struct timeval	start;
	int				argc;
	char			**argv;
	suseconds_t		lifetime;
	suseconds_t		time4eat;
	suseconds_t		sleeptime;
	struct s_philo	*cavern;
}	t_world;

typedef struct s_philo{
	t_world			*world;
	pthread_t		philo;
	unsigned int	id;
	unsigned int	nb_meals;
	struct timeval	lastmeal;
	pthread_mutex_t	fork;
	pthread_mutex_t	*nextfork;
	suseconds_t		lifetime;
	suseconds_t		time4eat;
	suseconds_t		sleeptime;
}	t_philo;

int			ft_str_isdigit(char **str, size_t size);
int			ft_isdigit(int c);
int			ft_atoi(const char *str);
void		print_act(char *msg, t_philo philo, t_world *world);
void		myusleep(useconds_t time);
#endif
