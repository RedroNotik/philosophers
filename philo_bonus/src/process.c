/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanh <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 15:59:00 by ghanh             #+#    #+#             */
/*   Updated: 2021/12/08 15:59:02 by ghanh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	eat_ph(t_phil_c *phil)
{
	sem_wait(phil->info->forks);
	print_f(phil, "\x1b[35mhas taken a fork\x1b[0m\n");
	sem_wait(phil->info->forks);
	print_f(phil, "\x1b[35mhas taken a fork\x1b[0m\n");
	phil->end_eating = set_time(0);
	print_f(phil, "\x1b[32mis eating\x1b[0m\n");
	phil->eat_counter++;
	if (phil->eat_counter == phil->info->win)
		sem_post(phil->info->num_to_win);
	c_usleep(phil->info->time_to_eat);
	sem_post(phil->info->forks);
	sem_post(phil->info->forks);
}

void	sleep_and_think(t_phil_c *phil)
{
	print_f(phil, "\x1b[36mis sleeping\x1b[0m\n");
	c_usleep(phil->info->time_to_sleep);
	print_f(phil, "\x1b[33mis thinking\x1b[0m\n");
}

void	start_phil(t_phil_c *phil)
{
	pthread_t	thread;

	pthread_create(&thread, NULL, monitor, phil);
	if (phil->number % 2 == 0)
		c_usleep(phil->info->time_to_eat);
	while (1)
	{
		eat_ph(phil);
		sleep_and_think(phil);
	}
	exit(0);
}

void	run_process(t_info *ph_info)
{
	size_t			i;

	ph_info->start_time = set_time(0);
	i = 0;
	while (i < ph_info->phil_num)
	{
		ph_info->phil[i].end_eating = ph_info->start_time;
		ph_info->phil[i].pid = fork();
		if (ph_info->phil[i].pid == 0)
			return (start_phil(&ph_info->phil[i]));
		else if (ph_info->phil[i].pid < 0)
		{
			printf("Fork error\n");
			exit(0);
		}
		i++;
	}
}
