/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanh <ghanh@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 13:01:32 by ghanh             #+#    #+#             */
/*   Updated: 2021/11/21 13:57:51 by ghanh            ###   ########.fr       */
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

typedef struct s_cur_phil
{
	int	eat_counter;

} 			t_cut_phil;

typedef struct s_phil
{
	unsigned int	phil_num;
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	unsigned int	time_to_think;
	unsigned int	cur_time;
	int				nb_meals_to_win;

	pthread_mutex_t	*forks;
	pthread_mutex_t	print;
}				t_phil;
#endif