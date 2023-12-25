/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutexing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilva-g <dsilva-g@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 13:28:01 by dsilva-g          #+#    #+#             */
/*   Updated: 2023/12/25 17:25:16 by dsilva-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/*
void	mutexes(void)
{
	printf("---INIT MUTEX-------------------------------------------------\n");
	printf("the mutexes are initialized\n");
}
*/

void	init_mutex(t_table *table)
{
	size_t	idx;

	idx = 0;
	while (idx < table->n_philos)
		pthread_mutex_init(&table->fork[idx++], NULL);
	pthread_mutex_init(&table->eat, NULL);
	pthread_mutex_init(&table->print, NULL);
	pthread_mutex_init(&table->end, NULL);
	pthread_mutex_init(&table->time_stamp, NULL);
}

void	destroy_mutex(t_table *table)
{
	size_t	idx;

	idx = 0;
	while (idx < table->n_philos)
		pthread_mutex_destroy(&table->fork[idx++]);
	pthread_mutex_destroy(&table->eat);
	pthread_mutex_destroy(&table->print);
	pthread_mutex_destroy(&table->end);
	pthread_mutex_destroy(&table->time_stamp);
}
