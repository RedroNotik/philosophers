//
// Created by Gaynell Hanh on 12/8/21.
//

#include "philo_bonus.h"

void	*eat_monitor(void *inf)
{
	t_info	*info;
	size_t	i;

	i = 0;
	info = inf;
	while (i < info->phil_num)
	{
		sem_wait(info->num_to_win);
		i++;
	}
	sem_post(info->finish);
	return (NULL);
}

void	*f_monitor(void *inf)
{
	t_info	*info;
	size_t	i;

	info = inf;
	sem_wait(info->finish);
	i = 0;
	while (i < info->phil_num)
	{
		kill(info->phil[i].pid, SIGTERM);
		i++;
	}
	return (NULL);
}

void	*monitor(void *phil)
{
	t_phil_c	*r_phil;
	uint64_t	time;

	r_phil = phil;
	while (1)
	{
		sem_wait(r_phil->info->action);
		time = set_time(0);
		if (time - r_phil->end_eating >= r_phil->info->time_to_die)
		{
			print_f(phil, "\x1b[31mdied\x1b[0m\n" );
			sem_post(r_phil->info->finish);
			return (NULL);
		}
		sem_post(r_phil->info->action);
	}
}
