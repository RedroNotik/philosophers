/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanh <ghanh@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 13:01:32 by ghanh             #+#    #+#             */
/*   Updated: 2021/11/22 19:34:36 by ghanh            ###   ########.fr       */
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

typedef struct s_phil_c
{
	pthread_t		tr_phil;
	int 			number;
	int				eat_counter;
	unsigned int	start_eating;
	int				l_fork;
	int 			r_fork;
	unsigned int 	t_t_d;
	unsigned int	t_t_e;
	unsigned int	t_t_s;
	int 			win;

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
#endif