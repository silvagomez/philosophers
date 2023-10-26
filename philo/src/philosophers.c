/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilva-g <dsilva-g@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 00:00:43 by dsilva-g          #+#    #+#             */
/*   Updated: 2023/10/26 15:54:22 by dsilva-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int mails = 0;

void	*routine(void)
{
	mails++;
	return ;
}

void	philosopher(char *arg[])
{
	t_data	data;

	// data init
	data.n_philos = ft_atoi(arg[1]);
	data.life_time = ft_atoi(arg[2]);
	data.eat_time = ft_atoi(arg[3]);
	data.zzz_time = ft_atoi(arg[4]);
	if (arg[5])
		data.n_meals = ft_atoi(arg[5]);
	else
		data.n_meals = 0;
	// create thread 
	size_t idx;
	idx = 1;
	while (idx <= data.n_philos)
	{
		if (pthread_create(data.philo + idx, NULL, &routine, NULL) != 0)
			return (error_terminate(ERR_CTH));
		idx++;
		printf("Philo %zu thread has started\n", idx);
	}
	// create join 
	idx = 1;
	while (idx <= data.n_philos)
	{
		if (pthread_join(data.philo[idx], NULL) != 0)
			return (error_terminate(ERR_JTH));
		printf("Philo %zu thread has finished\n", idx);
	}
	printf("Total mails %d\n", mails);
}
