/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanh <ghanh@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 17:41:18 by ghanh             #+#    #+#             */
/*   Updated: 2021/12/04 17:33:21 by ghanh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h> //printf
# include <sys/time.h> //gettimeofday
# include <unistd.h> //write, usleep, fork
# include <semaphore.h> // sem_open, sem_close, sem_post, sem_wait, sem_unlink
# include <sys/wait.h>
# include <stdlib.h> //exit

# include <pthread.h> //pthread_create, pthread_detach, pthread_join
# include <string.h> // memset
# include <sys/types.h>
# include <signal.h> //kill

typedef struct s_phil_c
{
	int				number;
	int				eat_counter;
	uint64_t		end_eating;
	struct s_info	*info;
	pid_t			pid;
}			t_phil_c;

typedef struct s_info
{
	size_t			phil_num;
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	uint64_t		start_time;
	int				win;
	sem_t			*action;
	sem_t			*forks;
	sem_t			*message;
	sem_t			*finish;
	t_phil_c		*phil;
}				t_info;

////utils.c
int	ft_atoi(const char *str);
int	ft_isdigit(int c);
////time.c
void	c_usleep(uint64_t time);
uint64_t	set_time(int i);
////init.c
int	init(t_info *ph_info, int argc, char *argv[]);

void	print_f(t_phil_c *phil, char *str);
#endif
