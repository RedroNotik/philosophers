/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanh <ghanh@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 13:01:32 by ghanh             #+#    #+#             */
/*   Updated: 2021/11/23 18:41:41 by ghanh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <string.h> //memset
# include <stdio.h> //printf
# include <stdlib.h> //malloc, free
# include <unistd.h> //write, usleep
# include <sys/time.h> //gettimeofday
# include <pthread.h> //pthread_create, pthread_detach, pthread_join,
//pthread_mutex_init,pthread_mutex_destroy, pthread_mutex_lock,pthread_mutex_unlock
# include "libft.h"
# define EAT 1
# define T_FORK 2
# define SLEEP 3
# define THINK 4
# define DIE	5


typedef struct s_phil_c
{
	pthread_t		tr_phil;
	int 			number;
	int				eat_counter;
	uint64_t 		end_eating;
	pthread_mutex_t *l_fork;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	print;
	unsigned int 	t_t_d;
	unsigned int	t_t_e;
	unsigned int	t_t_s;
	int 			win;
	uint64_t 		start_time;

} 			t_phil_c;

typedef struct s_phil
{
	size_t			phil_num;
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	unsigned int	cur_time;
	int				nb_meals_to_win;
	t_phil_c		*phil;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print;
}				t_phil;

uint64_t	set_time(int i);
#endif