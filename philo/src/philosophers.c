/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilva-g <dsilva-g@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 00:00:43 by dsilva-g          #+#    #+#             */
/*   Updated: 2023/11/01 21:40:57 by dsilva-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int mails = 0;

size_t	get_time(void)
{
	struct timeval	s_time;
	gettimeofday(&s_time, NULL);
	return ((s_time.tv_sec * 1000) + (s_time.tv_usec / 1000));
}

/*
 * Philosophers routine
 *	- eat
 *	- sleep
 *	- think
 */
void	*routine(void *d)
{
	// test 

	(void)d;
	printf("time philo_id has taken a fork\n");
	printf("time philo_id is eating\n");
	printf("time philo_id is sleeping\n");
	printf("time philo_id is thinking\n");
	printf("time philo_id died\n");
	mails++;
	return (NULL);
}

int	philosopher(char *arg[])
{
	t_data	data;

	// data init
	data.n_philos = ft_atoi(arg[1]);
	data.life_time = ft_atoi(arg[2]);
	data.eat_time = ft_atoi(arg[3]);
	data.zzz_time = ft_atoi(arg[4]);
	data.time = get_time();
	if (arg[5])
		data.n_meals = ft_atoi(arg[5]);
	else
		data.n_meals = 0;
	// create thread 
	size_t idx;
	idx = 1;
	data.philo = (pthread_t *)malloc(data.n_philos * sizeof(pthread_t));
	while (idx <= data.n_philos)
	{
		if (pthread_create(&data.philo[idx], NULL, routine, NULL) != 0)
			return (error_terminate(ERR_CTH));
		printf("Philo %zu thread has started\n", idx);
		idx++;
	}
	// Need a pthread_t for guardian
	// create join 
	idx = 1;
	while (idx <= data.n_philos)
	{
		if (pthread_join(data.philo[idx], NULL) != 0)
			return (error_terminate(ERR_JTH));
		printf("Philo %zu thread has finished\n", idx);
		idx++;
	}
	printf("Total mails %d\n", mails);
	/* 
	 * A pthread_join will used for the guardian
	 */
	return (0);
}
