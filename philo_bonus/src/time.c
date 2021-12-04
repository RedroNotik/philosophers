/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanh <ghanh@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 15:38:19 by ghanh             #+#    #+#             */
/*   Updated: 2021/11/28 15:42:00 by ghanh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_bonus.h"

void	c_usleep(uint64_t time)
{
	u_int64_t	get_time;

	get_time = set_time(0);
	while (set_time(0) - get_time < time)
		usleep(100);
}

uint64_t	set_time(int i)
{
	struct timeval	current_time;
	uint64_t		time;

	gettimeofday(&current_time, NULL);
	time = (current_time.tv_sec * 1000 + current_time.tv_usec / 1000) + i;
	return (time);
}
