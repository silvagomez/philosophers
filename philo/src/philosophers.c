/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilva-g <dsilva-g@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 00:00:43 by dsilva-g          #+#    #+#             */
/*   Updated: 2023/12/16 13:03:13 by dsilva-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int mails = 0;

int	get_time(void)
{
	struct timeval	s_time;
	
	gettimeofday(&s_time, NULL);
	return ((s_time.tv_sec * 1000) + (s_time.tv_usec / 1000));
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
	if (philo->id % 2 != 0)
		usleep(10);
	printf("pointer %lu\n", philo->id);
	printf("time philo_id has taken a fork\n");
	printf("time philo_id is eating\n");
	printf("time philo_id is sleeping\n");
	printf("time philo_id is thinking\n");
	printf("time philo_id died\n");
	mails++;
	return (NULL);
}

/*
 * Returns the last node of philo list.
 */
t_philo	*philo_last(t_philo *philo)
{
	if (!philo)
		return (NULL);
	while(philo->next)
		philo = philo->next;
	return (philo);
}

/*
 * Creates a new philo node.
 */
t_philo	*philo_new(t_table *table, size_t id)
{
	t_philo	*node;

	node = (t_philo *)malloc(sizeof(t_philo));
	if (!node)
		return (NULL);
	node->id = id;
	node->meals = table->meals;
	node->prev = philo_last(table->philo);
	node->next = NULL;
	node->beside = NULL;
	node->table = table;
	return (node);
}


/*
 * Adds a new philo node to the list, and set the sit order.
 */
void	philo_add(t_table *table, t_philo *new)
{
	if (!new)
		return ;
	if (table->philo != NULL)
	{
		philo_last(table->philo)->next = new;
		philo_last(table->philo)->beside = new;
		if (philo_last(table->philo)->id == table->n_philos)
			philo_last(table->philo)->beside = table->philo;
	}
	else
		table->philo = new;
}

/*
 * Creates the philo list.
 */
void	init_philo(t_table *table)
{
	size_t	idx;

	idx = 0;
	while (++idx <= table->n_philos)
		philo_add(table, philo_new(table, idx));
}

/*
 * Allocates the matrix of mutex per philo fork.
 */
int	alloc_fork(t_table *table)
{
	table->fork = (pthread_mutex_t *)malloc(table->n_philos * \
			sizeof(pthread_mutex_t));
	if (!table->fork)
		return (error_terminate(ERR_MMT));
	return (0);
}


/*
 * Allocates the matrix of threads per philo.
 */
int	alloc_thread(t_table *table)
{
	table->th = (pthread_t *)malloc(table->n_philos * sizeof(pthread_t));
	if (!table->th)
		return (error_terminate(ERR_MTH));
	return (0);
}

/*
 * This functions initializes varriables of the table.
 */
int	set_table(t_table *table, char *arg[])
{
	table->n_philos = ft_atoi(arg[1]);
	table->life_time = ft_atoi(arg[2]);
	table->eat_time = ft_atoi(arg[3]);
	table->zzz_time = ft_atoi(arg[4]);
	table->time = get_time();
	if (arg[5])
		table->meals = ft_atoi(arg[5]);
	else
		table->meals = -1;
	if (alloc_thread(table) < 0)
		return (-1);
	if (alloc_fork(table) < 0)
		return (-1);
	/*
	table->philo = NULL;
	init_philo(table);
	*/
	return (0);
}

int	set_philo(t_table *table, t_philo **philo)
{
	size_t	idx;

	*philo = (t_philo *)malloc(table->n_philos * sizeof(pthread_t));
	if (!philo)
		return (error_terminate("Error malloc philo matrix"));
	idx = 0;
	while (idx < table->n_philos)
	{
		(*philo)->id = idx + 1;
		(*philo)->meals = table->meals;
		(*philo)->table = table;
		idx++;
	}
	return (0);
}

int	philosopher(char *arg[])
{
	t_table	table;

	if (set_table(&table, arg) < 0)
		return (-1);
	printf("table.n_philos %lu\n", table.n_philos);
	printf("table.life_time %lu\n", table.life_time);
	printf("table.eat_time %lu\n", table.eat_time);
	printf("table.zzz_time %lu\n", table.zzz_time);
	printf("table.meals %i\n", table.meals);
	printf("table.time %lu\n", table.time);
	printf("table.philo %p\n", table.philo);

	t_philo	*philo;
	if (set_philo(&table, &philo) < 0)
		return (-1);

	size_t	idx;
	/*
	idx = 0;
	while(idx < table.n_philos)
	{
		printf("philo id %lu meals %i\n", philo[idx].id, philo[idx].meals);
		idx++;
	}
*/
	idx = 0;
	// thread routine
	while (idx < table.n_philos)
		pthread_mutex_init(&table.fork[idx++], NULL);
	idx = 0;
	while (idx < table.n_philos)
	{
		if (pthread_create(&table.th[idx], NULL, routine, philo) != 0)
			return (error_terminate(ERR_CTH));
		printf(HGRN"Philo %zu thread has started\n"RST, idx + 1);
		idx++;
	}
	
	// Need a pthread_t for guardian
	
	// create join 
	idx = 0;
	while (idx < table.n_philos)
	{
		if (pthread_join(table.th[idx], NULL) != 0)
			return (error_terminate(ERR_JTH));
		printf(HCYN"Philo %zu thread has finished\n"RST, idx + 1);
		idx++;
	}
	// destroy fork mutex
	idx = 0;
	while (idx <= table.n_philos)
		pthread_mutex_destroy(&table.fork[idx++]);
	printf("Total mails %d\n", mails);
	

	/* 
	 * A pthread_join will used for the guardian
	 */
	return (0);
}
