#include "../includes/philo.h"



int	check_arg(int argc, char *argv[])
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

int	start_threads(t_phil *phil_info)
{
	size_t	i;
	uint64_t time;

	i = 0;
	time = set_time(0);
	while (i < phil_info->phil_num)
	{
		phil_info->phil[i].start_time = time;
		pthread_create(&phil_info->phil[i].tr_phil, NULL, phil_process,
					   &phil_info->phil[i]);
		i++;
	}
	return (0);
}

int	check_eat(t_phil *phil_info)
{
	size_t	i;
	int		count;

	count = 0;
	i = 0;
	while (i < phil_info->phil_num)
	{
		if (phil_info->phil[i].win <= 0)
			count++;
		else
			return (0);
		i++;
	}
	return (1);
}

int	die(t_phil *phil_info)
{
	size_t	i;

	i = 0;
	while (i < phil_info->phil_num)
	{
		pthread_detach(phil_info->phil[i].tr_phil);
		pthread_mutex_destroy(&phil_info->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&phil_info->print);
	return (0);
}



int	main(int argc, char *argv[])
{
	t_phil	phil_info;

	if (argc != 5 && argc != 6)
	{
		printf("Incorrect number of arguments\n");
		return (0);
	}
	if (!check_arg(argc, argv))
	{
		printf("Incorrect arguments\n");
		return (0);
	}
	set_info(argv, &phil_info);
	phil_game(&phil_info);
	free(phil_info.forks);
	free(phil_info.phil);
	return (0);
}
