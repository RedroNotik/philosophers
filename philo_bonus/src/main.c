/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanh <ghanh@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 17:48:14 by ghanh             #+#    #+#             */
/*   Updated: 2021/12/03 19:45:05 by ghanh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_bonus.h"

////PROCESS
void	print_f(t_phil_c *phil, char *str)
{
	uint64_t	time;

	time = set_time(0) - data->start_time;
	sem_wait(phil->info->message);
	print_f("%ums %d %s", time, phil->number, str);
	sem_post(phil->info->message);
}

void	eat_ph(t_phil_c *phil)
{
	sem_wait(phil->info->forks);
	print_f(phil, "has taken a fork\n");
	sem_wait(phil->info->forks);
	print_f(phil, "has taken a fork\n");
	phil->end_eating = set_time(0);
	print_f(phil, "is eating\n");
	phil->eat_counter++;
	////todo add check
}

void	start_phil(t_phil_c *phil)
{
	////monitor;
	if (phil->number % 2 == 0)
		c_usleep(phil->info->time_to_eat);
	while (1)
	{
		eat_ph(phil);
	}
	exit(0);
}

void	run_process(t_info *ph_info)
{
	uint64_t	time;
	int			i;

	time = set_time(0);
	i = 0;
	while (i < ph_info->phil_num)
	{
		ph_info->phil[i].end_eating = time;
		ph_info->phil[i].pid = fork();
		if (ph_info->phil[i].pid == 0)
			return (start_phil(&ph_info->phil[i])); ////PROCESS FUNCTION
		else if (ph_info->phil[i].pid < 0)
		{
			printf("Fork error\n");
			exit(0);
		}
		i++;
	}
}

int	main(int argc, char *argv[])
{
	t_info	ph_info;

	memset(&ph_info, 0, sizeof(ph_info));
	if (argc != 5 && argc != 6)
		return (printf("Incorrect number of arguments\n"));
	if (!init(&ph_info, argc, argv))
		return (printf("Incorrect arguments"));
	run_process(&ph_info);
	////todo make two monitors
	return (0);
}
