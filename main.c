#include "includes/philo.h"

void c_usleep(uint64_t time)
{
	u_int64_t get_time;

	get_time = set_time(0);
	while (set_time(0) - get_time < time)
		usleep(100);
}

void	print_f(t_phil_c *data, int sign)
{
	unsigned int time;

	time = set_time(0) - data->start_time;
	pthread_mutex_lock(&data->print);
	if (sign == 1)
		printf("%ums %d is eating\n", time,
			   data->number);
	else if (sign == 2)
		printf("%ums %d has taken a fork\n",time, data->number);
	else if (sign == 3)
		printf("%ums %d is sleeping\n", time,data->number);
	else if (sign == 4)
		printf("%ums %d is thinking\n", time,data->number);
	else if (sign == 5)
		printf("%ums %d died\n",time, data->number);
	pthread_mutex_unlock(&data->print);
}

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

//t_phil	set_info(char *argv[])
//{
//	size_t	i;
//	t_phil *phil_info;
//
//	i = 0;
//	phil_info.phil_num = ft_atoi(argv[1]);
//	phil_info.time_to_die = ft_atoi(argv[2]);
//	phil_info.time_to_eat = ft_atoi(argv[3]);
//	phil_info.time_to_sleep = ft_atoi(argv[4]);
//	phil_info.forks = malloc(sizeof(pthread_mutex_t) * phil_info.phil_num);
//	phil_info.phil = malloc(sizeof(t_phil_c) * phil_info.phil_num);
//	pthread_mutex_init(&phil_info.print, NULL);
//	//todo check malloc and dont forget to free
//	while (i < phil_info.phil_num)
//	{
//		phil_info.phil[i].number = i + 1;
//		phil_info.phil[i].l_fork = &phil_info.forks[i];
//		phil_info.phil[i].r_fork = &phil_info.forks[(i + 1) % phil_info
//													.phil_num];
//		phil_info.phil[i].t_t_d = phil_info.time_to_die;
//		phil_info.phil[i].t_t_e = phil_info.time_to_eat;
//		phil_info.phil[i].t_t_s = phil_info.time_to_sleep;
//		phil_info.phil[i].eat_counter = 0;
//		pthread_mutex_init(&phil_info.forks[i], NULL);
//		phil_info.phil[i].print = phil_info.print;
//		if (argv[5])
//			phil_info.phil[i].win = ft_atoi(argv[5]);
//		else
//			phil_info.phil[i].win = -1;
//		i++;
//	}
//	return (phil_info);
//}

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
	pthread_mutex_init(&phil_info->print, NULL);
	//todo check malloc and dont forget to free
	while (i < phil_info->phil_num)
	{
		phil_info->phil[i].number = i + 1;
		phil_info->phil[i].l_fork = &phil_info->forks[i];
		phil_info->phil[i].r_fork = &phil_info->forks[(i + 1) % phil_info
																	   ->phil_num];
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
		i++;
	}
}

uint64_t	set_time(int i)
{
	struct timeval	current_time;
	uint64_t time;

	gettimeofday(&current_time, NULL);
	time = (current_time.tv_sec * 1000 + current_time.tv_usec / 1000) + i;
//	printf("%llu OLSAOLSAO\n", time);
	return (time);
}

void	eat_ph(t_phil_c	*data)
{
	pthread_mutex_lock(data->l_fork);
	print_f(data, 2);
	pthread_mutex_lock(data->r_fork);
	print_f(data, 2);
	data->end_eating  = set_time(data->t_t_e);
	print_f(data, 1);
	c_usleep(data->t_t_e);
	data->eat_counter++;
}

void	sleep_and_think(t_phil_c *data)
{
	pthread_mutex_unlock(data->r_fork);
	pthread_mutex_unlock(data->l_fork);
	print_f(data, SLEEP);
	c_usleep(data->t_t_s);
	print_f(data, THINK);
}

void	*phil_process(void *phil)
{
	t_phil_c	*data;

	data = phil;
	if (data->number % 2 == 0)
		usleep(1000);
	while (1)
	{
		eat_ph(data);
		sleep_and_think(data);
	}

}

int start_threads(t_phil *phil_info)
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

int	phil_game(t_phil *phil_info)
{
	size_t i;

	start_threads(phil_info);
	while (1)
	{
		i = 0;
		while (i < phil_info->phil_num)
		{
			if ((long long int)(set_time(0) - phil_info->phil[i].end_eating
			) >=
			phil_info->time_to_die && phil_info->phil[i].eat_counter != 0)
			{
				print_f(&phil_info->phil[i], DIE);
				exit(0); //todo make some frees
			}
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
//	phil_info = set_info(argv, phil_info);
	set_info(argv, &phil_info);
	phil_game(&phil_info);
//	free(phil_info.forks);
	return (0);
}