/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanh <ghanh@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 13:01:32 by ghanh             #+#    #+#             */
/*   Updated: 2021/11/28 15:49:18 by ghanh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <string.h> //memset
# include <stdio.h> //printf
# include <stdlib.h> //malloc, free
# include <unistd.h> //write, usleep
# include <sys/time.h> //gettimeofday
# include <pthread.h> //pthread_create, pthread_detach, pthread_join
# define EAT 1
# define T_FORK 2
# define SLEEP 3
# define THINK 4
# define DIE	5

typedef struct s_phil_c
{
	pthread_t		tr_phil;
	int				number;
	int				eat_counter;
	uint64_t		end_eating;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	print;
	unsigned int	t_t_d;
	unsigned int	t_t_e;
	unsigned int	t_t_s;
	int				win;
	uint64_t		start_time;

}			t_phil_c;

typedef struct s_phil
{
	size_t			phil_num;
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	unsigned int	cur_time;
	int				win;
	t_phil_c		*phil;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print;
}				t_phil;

////set_info.c
void		set_info(char *argv[], t_phil *phil_info);

////main.c
int			die(t_phil *phil_info);
int			check_eat(t_phil *phil_info);
int			start_threads(t_phil *phil_info);
int			check_arg(int argc, char *argv[]);
////simulation.c
void		print_f(t_phil_c *data, int sign);
void		eat_ph(t_phil_c	*data);
void		sleep_and_think(t_phil_c *data);
void		*phil_process(void *phil);
int			phil_game(t_phil *phil_info);
////time.c
void		c_usleep(uint64_t time);
uint64_t	set_time(int i);
////utils.c
int			ft_atoi(const char *str);
int			ft_isdigit(int c);
#endif