/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilva-g <dsilva-g@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 00:00:43 by dsilva-g          #+#    #+#             */
/*   Updated: 2023/12/25 16:57:56 by dsilva-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	data_table(t_table *table)
{
	printf("---TABLE DATA-------------------------------------------------\n");
	printf("table.n_philos %lu\n", table->n_philos);
	printf("table.life_time %lu\n", table->life_time);
	printf("table.eat_time %lu\n", table->eat_time);
	printf("table.zzz_time %lu\n", table->zzz_time);
	printf("table.max_meals %lu\n", table->max_meals);
	printf("table.time %lu\n", table->time);
	printf("table %p\n", &(*table));
}

void	data_philo(t_table *table, t_philo **philo)
{
	size_t idx;

	printf("---PHILOS-----------------------------------------------------\n");
	idx = 0;
 	while(idx < table->n_philos)
	{
		printf("philo id %lu meals %lu\n", (*philo)[idx].id, (*philo)[idx].meal);
		printf("philo pointer %p and pointer table %p\n", &(*philo)[idx], (*philo)[idx].table);
		printf("philo->table->time %lu\n", (*philo)[idx].table->time);
		idx++;
	}
}

int	philosopher(char *arg[])
{
	t_table	table;
	t_philo	*philo;

	if (set_table(&table, arg) < 0)
		return (-1);
	data_table(&table);
	if (set_philo(&table, &philo) < 0)
		return (-1);
	data_philo(&table, &philo);
	
	printf("---INIT MUTEX-------------------------------------------------\n");

	init_mutex(&table);
	/*
	idx = 0;
	while (idx < table.n_philos)
		pthread_mutex_init(&table.fork[idx++], NULL);
	pthread_mutex_init(&table.eat, NULL);
	pthread_mutex_init(&table.print, NULL);
	pthread_mutex_init(&table.end, NULL);
	pthread_mutex_init(&table.time_stamp, NULL);
	printf("the mutexes are initialized\n");
	*/

	// Need a pthread_t for guardian that is the waiter
	printf("---THREAD WAITER----------------------------------------------\n");
	printf(MAG"WAITER thread is been launched\n"RST);
	if (launching_thread(&table, &philo) < 0)
		return (-1);
	//if (pthread_create(&table.waiter, NULL, &customer_service, philo) != 0)
	//	return (error_terminate(ERR_CTH));
	
	printf("---THREADS PHILOS---------------------------------------------\n");
/*
	idx = 0;
	while (idx < table.n_philos)
	{
		printf(MAG"Philo %zu thread is been launched\n"RST, idx + 1);
		if (pthread_create(&table.th[idx], NULL, &routine, &philo[idx]) != 0)
			return (error_terminate(ERR_CTH));
		idx++;
	}
*/	
	// create join
	if (waiting_for_thread(&table) < 0)
		return (-1);
	/*
	if (pthread_join(table.waiter, NULL) != 0)
		return (error_terminate(ERR_JTH));
	printf(HCYN"Waiter thread has finished\n"RST);
	idx = 0;
	while (idx < table.n_philos)
	{
		if (pthread_join(table.th[idx], NULL) != 0)
			return (error_terminate(ERR_JTH));
		printf(HCYN"Philo %zu thread has finished\n"RST, idx + 1);
		idx++;
	}
*/

	// destroy fork mutex
	destroy_mutex(&table);
		/*
	idx = 0;
	while (idx < table.n_philos)
		pthread_mutex_destroy(&table.fork[idx++]);
	pthread_mutex_destroy(&table.eat);
	pthread_mutex_destroy(&table.print);
	pthread_mutex_destroy(&table.end);
	pthread_mutex_destroy(&table.time_stamp);
	*/
	return (0);
}
