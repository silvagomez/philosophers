/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilva-g <dsilva-g@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 00:00:43 by dsilva-g          #+#    #+#             */
/*   Updated: 2023/12/25 18:44:08 by dsilva-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/*
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
		printf("philo pointer %p and pointer table %p\n", &(*philo)[idx], \
				(*philo)[idx].table);
		printf("philo->table->time %lu\n", (*philo)[idx].table->time);
		idx++;
	}
}
*/

int	philosopher(char *arg[])
{
	t_table	table;
	t_philo	*philo;

	if (set_table(&table, arg) < 0)
		return (-1);
	if (alloc_philo(&table, &philo) < 0)
		return (-1);
	set_philo(&table, &philo);
	init_mutex(&table);
	if (launching_thread(&table, &philo) < 0)
		return (-1);
	if (waiting_for_thread(&table) < 0)
		return (-1);
	destroy_mutex(&table);
	free(table.th);
	free(table.fork);
	return (0);
}
