/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_info.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanh <ghanh@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 15:46:46 by ghanh             #+#    #+#             */
/*   Updated: 2021/11/28 15:52:54 by ghanh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_phil(t_phil *phil_info, size_t i, char *argv[])
{
	phil_info->phil[i].number = i + 1;
	phil_info->phil[i].l_fork = &phil_info->forks[i];
	phil_info->phil[i].r_fork = &phil_info->forks[(i + 1) % phil_info
												  ->phil_num];
	phil_info->phil[i].end_eating = set_time(0);
	phil_info->phil[i].t_t_d = phil_info->time_to_die;
	phil_info->phil[i].t_t_e = phil_info->time_to_eat;
	phil_info->phil[i].t_t_s = phil_info->time_to_sleep;
	phil_info->phil[i].eat_counter = 0;
	pthread_mutex_init(&phil_info->forks[i], NULL);
	phil_info->phil[i].print = phil_info->print;
	if (argv[5])
		phil_info->phil[i].win = ft_atoi(argv[5]);
	else
		phil_info->phil[i].win = -1;
}

void	set_info(char *argv[], t_phil *phil_info)
{
	size_t	i;

	i = 0;
	phil_info->phil_num = ft_atoi(argv[1]);
	phil_info->time_to_die = ft_atoi(argv[2]);
	phil_info->time_to_eat = ft_atoi(argv[3]);
	phil_info->time_to_sleep = ft_atoi(argv[4]);
	phil_info->forks = malloc(sizeof(pthread_mutex_t) * phil_info->phil_num);
	phil_info->phil = malloc(sizeof(t_phil_c) * phil_info->phil_num);
	if (argv[5])
		phil_info->win = ft_atoi(argv[5]);
	else
		phil_info->win = -1;
	pthread_mutex_init(&phil_info->print, NULL);
	while (i < phil_info->phil_num)
	{
		set_phil(phil_info, i, argv);
//		phil_info->phil[i].number = i + 1;
//		phil_info->phil[i].l_fork = &phil_info->forks[i];
//		phil_info->phil[i].r_fork = &phil_info->forks[(i + 1) % phil_info
//				->phil_num];
//		phil_info->phil[i].end_eating = set_time(0);
//		phil_info->phil[i].t_t_d = phil_info->time_to_die;
//		phil_info->phil[i].t_t_e = phil_info->time_to_eat;
//		phil_info->phil[i].t_t_s = phil_info->time_to_sleep;
//		phil_info->phil[i].eat_counter = 0;
//		pthread_mutex_init(&phil_info->forks[i], NULL);
//		phil_info->phil[i].print = phil_info->print;
//		if (argv[5])
//			phil_info->phil[i].win = ft_atoi(argv[5]);
//		else
//			phil_info->phil[i].win = -1;
		i++;
	}
}
