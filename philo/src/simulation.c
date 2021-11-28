/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanh <ghanh@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 15:44:34 by ghanh             #+#    #+#             */
/*   Updated: 2021/11/28 15:48:29 by ghanh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_f(t_phil_c *data, int sign)
{
	unsigned int	time;

	time = set_time(0) - data->start_time;
	pthread_mutex_lock(&data->print);
	if (sign == 1)
		printf("%ums %d is eating\n", time, data->number);
	else if (sign == 2)
		printf("%ums %d has taken a fork\n", time, data->number);
	else if (sign == 3)
		printf("%ums %d is sleeping\n", time, data->number);
	else if (sign == 4)
		printf("%ums %d is thinking\n", time, data->number);
	else if (sign == 5)
		printf("%ums %d died\n", time, data->number);
	if (sign != 5)
		pthread_mutex_unlock(&data->print);
}

void	eat_ph(t_phil_c	*data)
{
	pthread_mutex_lock(data->l_fork);
	print_f(data, 2);
	pthread_mutex_lock(data->r_fork);
	print_f(data, 2);
	data->end_eating = set_time(0);
	data->win--;
	print_f(data, 1);
	c_usleep(data->t_t_e);
	pthread_mutex_unlock(data->r_fork);
	pthread_mutex_unlock(data->l_fork);
}

void	sleep_and_think(t_phil_c *data)
{
	print_f(data, SLEEP);
	c_usleep(data->t_t_s);
	print_f(data, THINK);
}

void	*phil_process(void *phil)
{
	t_phil_c	*data;

	data = phil;
	if (data->number % 2 == 0)
		c_usleep(data->t_t_e);
	while (1)
	{
		eat_ph(data);
		sleep_and_think(data);
	}
}

int	phil_game(t_phil *phil_info)
{
	size_t	i;

	start_threads(phil_info);
	while (1)
	{
		i = 0;
		while (i < phil_info->phil_num)
		{
			if ((long long int)(set_time(0) - phil_info->phil[i].end_eating
			) >=
				phil_info->time_to_die && phil_info->phil[i].win != 0)
			{
				print_f(&phil_info->phil[i], DIE);
				return (die(&(*phil_info)));
			}
			i++;
			if (check_eat(phil_info) && phil_info->win != -1)
				return (die(&(*phil_info)));
		}
	}
	return (0);
}
