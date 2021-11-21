#include "includes/philo.h"

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

t_phil	set_info(char *argv[], t_phil phil_info)
{
	phil_info.phil_num = ft_atoi(argv[1]);
	phil_info.time_to_die = ft_atoi(argv[2]);
	phil_info.time_to_eat = ft_atoi(argv[3]);
	phil_info.time_to_sleep = ft_atoi(argv[4]);
	phil_info.forks = malloc(sizeof(pthread_mutex_t) * phil_info.phil_num);
	//todo check malloc
	if (argv[5])
		phil_info.nb_meals_to_win = ft_atoi(argv[5]);
	else
		phil_info.nb_meals_to_win = -1;
	return (phil_info);
}

unsigned int	set_time()
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	printf("seconds : %ld\nmicro seconds : %d\n",
		current_time.tv_sec, current_time.tv_usec);
	unsigned int time = (current_time.tv_sec / 1000 + current_time.tv_usec *
			1000);
	printf("%u\n", time);
	return (0);
}

int	main(int argc, char *argv[])
{
	t_phil	phil_info;

	if (argc != 5 && argc != 6)
	{
		printf("Incorrect number of arguments\n");
		exit(EXIT_SUCCESS);
	}
	if (!check_arg(argc, argv))
	{
		printf("Incorrect arguments\n");
		exit(EXIT_SUCCESS);
	}
	phil_info = set_info(argv, phil_info);
	set_time();
	return (0);
}