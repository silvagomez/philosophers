/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threading.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilva-g <dsilva-g@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 13:27:56 by dsilva-g          #+#    #+#             */
/*   Updated: 2023/12/25 16:39:59 by dsilva-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*customer_service(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	
	while (!is_end(philo))
	{
		ft_usleep(10);
		complete_meals(philo);
		unhappy_philox2(philo);
	}
	return (ptr);
}

/*
 * Philosophers routine
 * - eat
 * - sleep
 * - think
 */
void	*routine(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	if (philo->id % 2 == 0)
		ft_usleep(10);
	while (!is_end(philo))
	//while (1)
	{
		cutlery(philo);
		sleeping(philo);
		thinking(philo);
	}
	//return (NULL);
	return (ptr);
}

int	launching_thread(t_table *table, t_philo **philo)
{
	size_t	idx;

	if (pthread_create(&table->waiter, NULL, &customer_service, (*philo)) != 0)
		return (error_terminate(ERR_CTH));
	idx = 0;
	while (idx < table->n_philos)
	{
		printf(MAG"Philo %zu thread is been launched\n"RST, idx + 1);
		if (pthread_create(&table->th[idx], NULL, &routine, &(*philo)[idx]) != 0)
			return (error_terminate(ERR_CTH));
		idx++;
	}
	return (1);
}

int	waiting_for_thread(t_table *table)
{
	size_t	idx;
	if (pthread_join(table->waiter, NULL) != 0)
		return (error_terminate(ERR_JTH));
	printf(HCYN"Waiter thread has finished\n"RST);
	idx = 0;
	while (idx < table->n_philos)
	{
		if (pthread_join(table->th[idx], NULL) != 0)
			return (error_terminate(ERR_JTH));
		printf(HCYN"Philo %zu thread has finished\n"RST, idx + 1);
		idx++;
	}
	return (1);
}
