/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanh <ghanh@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 17:48:14 by ghanh             #+#    #+#             */
/*   Updated: 2021/12/04 18:10:39 by ghanh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_bonus.h"

static void	free_philos(t_info *ph_info)
{
	int		i;
	int		status;

	i = 0;
	while (i < ph_info->phil_num)
	{
		waitpid(ph_info->phil[i].pid, &status, 0);
		i++;
	}
	free(ph_info->phil);
	sem_close(ph_info->finish);
	sem_close(ph_info->action);
	sem_close(ph_info->forks);
}

void	*f_monitor(void *inf)
{
	t_info	*info;
	int		i;

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
			print_f(phil, "died\n");
			sem_post(r_phil->info->finish);
			return (NULL);
		}
		sem_post(r_phil->info->action);
	}
}

////PROCESS
void	print_f(t_phil_c *phil, char *str)
{
	unsigned int	time;

	time = set_time(0) - phil->info->start_time;
	sem_wait(phil->info->message);
	printf("%ums %d %s", time, phil->number, str);
	sem_post(phil->info->message);
}

void	eat_ph(t_phil_c *phil)
{
//	sem_wait(phil->info->action);
	sem_wait(phil->info->forks);
	print_f(phil, "has taken a fork\n");
	sem_wait(phil->info->forks);
	print_f(phil, "has taken a fork\n");
	phil->end_eating = set_time(0);
	print_f(phil, "is eating\n");
	phil->eat_counter++;
	c_usleep(phil->info->time_to_eat);
	sem_post(phil->info->forks);
	sem_post(phil->info->forks);
//	sem_post(phil->info->action);
	////todo add check
}

void	sleep_and_think(t_phil_c *phil)
{
	print_f(phil, "is sleeping\n");
	c_usleep(phil->info->time_to_sleep);
	print_f(phil, "is thinking\n");
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
	int			i;

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

int	main(int argc, char *argv[])
{
	t_info		ph_info;
	pthread_t	thread;

	memset(&ph_info, 0, sizeof(ph_info));
	if (argc != 5 && argc != 6)
		return (printf("Incorrect number of arguments\n"));
	if (!init(&ph_info, argc, argv))
		return (printf("Incorrect arguments"));
	run_process(&ph_info);
	pthread_create(&thread, NULL, f_monitor, &ph_info);
	free_philos(&ph_info);
	////todo make two monitors
	return (0);
}
