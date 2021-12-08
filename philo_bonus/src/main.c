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

#include "../includes/philo_bonus.h"

static void	free_philos(t_info *ph_info)
{
	size_t		i;
	int			status;

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

void	print_f(t_phil_c *phil, char *str)
{
	unsigned int	time;

	time = set_time(0) - phil->info->start_time;
	sem_wait(phil->info->message);
	printf("%ums %d %s", time, phil->number, str);
	sem_post(phil->info->message);
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
	if (argc == 6)
		pthread_create(&thread, NULL, eat_monitor, &ph_info);
	pthread_create(&thread, NULL, f_monitor, &ph_info);
	free_philos(&ph_info);
	return (0);
}
