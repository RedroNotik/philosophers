/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanh <ghanh@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 18:54:05 by ghanh             #+#    #+#             */
/*   Updated: 2021/12/03 18:54:05 by ghanh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_bonus.h"

static int	check_arg(int argc, char *argv[])
{
	int	i;
	int	j;

	i = 1;
	while (i < argc)
	{
		j = 0;
		if (argv[i][0] != '-')
		{
			while (argv[i][j])
			{
				if (!ft_isdigit(argv[i][j]))
					return (0);
				j++;
			}
		}
		else
			return (0);
		i++;
	}
	return (1);
}

static void	parsing_info(t_info *ph_info, int argc, char *argv[])
{
	ph_info->phil_num = ft_atoi(argv[1]);
	ph_info->time_to_die = ft_atoi(argv[2]);
	ph_info->time_to_eat = ft_atoi(argv[3]);
	ph_info->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		ph_info->win = ft_atoi(argv[5]);
}

int	init_ph(t_info *ph_info)
{
	int	i;

	sem_unlink("death");
	sem_unlink("forks");
	sem_unlink("message");
	sem_unlink("finish");
	ph_info->death = sem_open("death", O_CREAT | O_EXCL, 0644, 1);
	ph_info->forks = sem_open("forks", O_CREAT | O_EXCL, 0644,
			  ph_info->phil_num);
	ph_info->message = sem_open("message", O_CREAT | O_EXCL, 0644, 1);
	ph_info->finish = sem_open("finish", O_CREAT | O_EXCL, 0644, 1);
	ph_info->phil = malloc(sizeof(t_phil_c) * ph_info->phil_num);
	if (!ph_info->phil)
		return (printf("Malloc failed\n"));
	i = 0;
	while (i < ph_info->phil_num)
	{
		ph_info->phil[i].number = i;
		ph_info->phil[i].eat_counter = 0;
		ph_info->phil[i].info = ph_info;
		i++;
	}
	return (0);
}

int	init(t_info *ph_info, int argc, char *argv[])
{
	if (!check_arg(argc, argv))
		return (0);
	parsing_info(ph_info, argc, argv);
	if (!init_ph(ph_info))
		return (0);
	return (1);
}
