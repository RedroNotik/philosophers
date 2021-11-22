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

t_phil	set_info(char *argv[])
{
	size_t	i;
	t_phil phil_info;

	i = 0;
	phil_info.phil_num = ft_atoi(argv[1]);
	phil_info.time_to_die = ft_atoi(argv[2]);
	phil_info.time_to_eat = ft_atoi(argv[3]);
	phil_info.time_to_sleep = ft_atoi(argv[4]);
	phil_info.forks = malloc(sizeof(pthread_mutex_t) * phil_info.phil_num);
	phil_info.phil = malloc(sizeof(t_phil_c) * phil_info.phil_num);
	//todo check malloc and dont forget to free
	while (i < phil_info.phil_num)
	{
		phil_info.phil[i].number = i;
		phil_info.phil[i].l_fork = 0;
		phil_info.phil[i].r_fork = (i + 1) % phil_info.phil_num;
		phil_info.phil[i].t_t_d = phil_info.time_to_die;
		phil_info.phil[i].t_t_e = phil_info.time_to_eat;
		phil_info.phil[i].t_t_s = phil_info.time_to_sleep;
		pthread_mutex_init(&phil_info.forks[i], NULL);
		if (argv[5])
			phil_info.phil[i].win = ft_atoi(argv[5]);
		else
			phil_info.phil[i].win = -1;
		i++;
	}
	return (phil_info);
}

uint64_t	set_time(int i)
{
	struct timeval	current_time;
	uint64_t time;

	gettimeofday(&current_time, NULL);
	time = (current_time.tv_sec / 1000 + current_time.tv_usec * 1000) + i;
//	printf("%u\n", time);
	return (time);
}

void *phil_process(void *phil)
{
	t_phil_c	*data;

	data = phil;
	while (1)
	{
		data->start_eating  = set_time(data->t_t_e);
//		printf("%d\n", data->number);
		usleep(data->t_t_e);
	}

}

int start_threads(t_phil phil_info)
{
	size_t	i;

	i = 0;
	while (i < phil_info.phil_num)
	{
		pthread_create(&phil_info.phil[i].tr_phil, NULL, phil_process,
					   &phil_info.phil[i]);
		i++;
	}
	return (0);
}

int	phil_game(t_phil phil_info)
{
	size_t i;

	start_threads(phil_info);
	while (1)
	{
		i = 0;
		while (i < phil_info.phil_num)
		{
//			if ((set_time(0) - phil_info.phil[i].start_eating) >= phil_info
//			.time_to_die)
//			{
//				printf("Someone died\n");
//				printf("%lld and %lld and %u and %u\n", set_time(0) - phil_info
//				.phil[i]
//						.start_eating, set_time(0), phil_info.phil[i]
//							   .start_eating,phil_info
//						.time_to_die);
//				exit(0); //todo make some frees
//			}
//			printf("%lld and %lld and %u\n", set_time(0) - phil_info.phil[i]
//			.start_eating, set_time(0), phil_info.phil[i]
//					.start_eating);
			printf("%u\n", phil_info.phil[i].start_eating);
			printf("%lld )))))))))))\n", set_time(0));
			printf("%lld wowowow\n", set_time(0) - phil_info.phil[i]
			.start_eating);
			usleep(5000);
			i++;
		}
	}
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
	phil_info = set_info(argv);
	phil_game(phil_info);
//	set_time();
	usleep(50000);
	free(phil_info.forks);
	return (0);
}