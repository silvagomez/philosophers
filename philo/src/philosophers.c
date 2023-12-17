/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilva-g <dsilva-g@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 00:00:43 by dsilva-g          #+#    #+#             */
/*   Updated: 2023/12/17 18:06:45 by dsilva-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int mails = 0;

int	get_current_time(void)
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

int	ft_usleep(size_t millisecond)
{
	size_t	start;

	start = get_current_time();
	printf(RED"call to wait ft_usleep time %zu \n"RST, start);
	while ((get_current_time() - start) < millisecond)
		usleep(500);
	return (0);
}

size_t	is_end(t_philo *philo)
{
	if (philo->end_flag == 0)
		return (0);
	return (1);
}

void	*routine(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	if (philo->id % 2 == 0)
	{
		ft_usleep(1);
		printf(RED"philo id %lu\n"RST, philo->id);
	}
	//starter
	while (is_end(philo) == 0)
	{
		pthread_mutex_lock(philo->l_hand);
		printf("philo id %lu\n", philo->id);
		printf("time philo %lu has taken the fork %lu\n", philo->id, philo->id_lhand);
		pthread_mutex_lock(philo->r_hand);
		printf("time philo %lu has taken the fork %lu\n", philo->id, philo->id_rhand);
		printf(HGRN"time philo %lu is eating\n"RST, philo->id);
		philo->eat_flag = 1;
		pthread_mutex_lock(&philo->table->eat);
		philo->meal++;
		philo->last_meal = get_current_time();
		printf("philo %lu has eating %lu meals\n"RST, philo->id, philo->meal);
		pthread_mutex_unlock(&philo->table->eat);
		//ft_usleep(ph->eat_time);
		philo->eat_flag = 0;
		pthread_mutex_unlock(philo->l_hand);
		pthread_mutex_unlock(philo->r_hand);

		printf("time philo_id is sleeping\n");
		//ft_usleep(ph->zzz_time);
		
		printf("time philo_id is thinking\n");
		
		printf("time philo_id died\n");
		
		//test for data race
		pthread_mutex_lock(&philo->table->mutest);
		mails++;
		pthread_mutex_unlock(&philo->table->mutest);
		//break;
	}
		return (NULL);
	//return (ptr);
}

/*
 * Returns the last node of philo list.
 */
/*
t_philo	*philo_last(t_philo *philo)
{
	if (!philo)
		return (NULL);
	while(philo->next)
		philo = philo->next;
	return (philo);
}
*/

/*
 * Creates a new philo node.
 */
/*
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
*/

/*
 * Adds a new philo node to the list, and set the sit order.
 */
/*
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
*/

/*
 * Creates the philo list.
 */
/*
void	init_philo(t_table *table)
{
	size_t	idx;

	idx = 0;
	while (++idx <= table->n_philos)
		philo_add(table, philo_new(table, idx));
}
*/

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
	table->time = get_current_time();
	if (arg[5])
		table->max_meals = ft_atoi(arg[5]);
	else
		table->max_meals = -1;
	if (alloc_thread(table) < 0)
		return (-1);
	if (alloc_fork(table) < 0)
		return (-1);
	printf("-----TEST ADDRESS FORK----------------------------------------\n");
	size_t idx = 0;
	while (idx < table->n_philos)
	{
		printf("pointer address of fork %lu is %p\n", idx, &table->fork[idx]);
		idx++;
	}
	/*
	table->philo = NULL;
	init_philo(table);
	*/
	return (0);
}

int	set_philo(t_table *table, t_philo **philo)
{
	size_t	idx;

	*philo = (t_philo *)malloc(table->n_philos * sizeof(t_philo));
	if (!(*philo))
		return (error_terminate("Error malloc philo matrix"));
	idx = 0;
	printf("---INIT PHILO-------------------------------------------------\n");
	while (idx < table->n_philos)
	{
		printf("philo id %lu + 1 = %lu\n", idx, idx+1);
		(*philo)[idx].id = idx + 1;
		(*philo)[idx].life_time = table->life_time;
		(*philo)[idx].meal = 0;
		(*philo)[idx].last_meal = get_current_time();
		(*philo)[idx].table = table;
		(*philo)[idx].end_flag = 0;
		(*philo)[idx].eat_flag = 0;
		(*philo)[idx].print_flag = 0;
		(*philo)[idx].id_lhand = (*philo)[idx].id;
		printf("pointer address of left fork %lu is %p\n", idx + 1, &table->fork[idx]);
		(*philo)[idx].l_hand = &table->fork[idx];
		if ((*philo)[idx].id != (*philo)[idx].table->n_philos)
		{
			(*philo)[idx].id_rhand = (*philo)[idx].id + 1;
			(*philo)[idx].r_hand = &table->fork[idx + 1];
		}
		else
		{
			(*philo)[idx].id_rhand = 1;
			(*philo)[idx].r_hand = &table->fork[0];
		}
		printf(BLU"%p philo data: id=%lu ## meals=%lu ## pointer table=%p ## "RST, &(*philo)[idx], (*philo)[idx].id, (*philo)[idx].meal, (*philo)[idx].table);
		printf("last_meal: %lu ## life_time philo: %lu ## ", (*philo)[idx].last_meal, (*philo)[idx].life_time);
		printf(HBLU"left fork id=%lu ## left fork mutex pointer %p ## ", (*philo)[idx].id_lhand, (*philo)[idx].l_hand);
		printf("right fork id=%lu ## right fork mutex pointer %p ##\n"RST, (*philo)[idx].id_rhand, (*philo)[idx].r_hand);
		idx++;
	}
	return (0);
}

int	philosopher(char *arg[])
{
	t_table	table;
	t_philo	*philo;

	if (set_table(&table, arg) < 0)
		return (-1);
	printf("---TABLE DATA-------------------------------------------------\n");
	printf("table.n_philos %lu\n", table.n_philos);
	printf("table.life_time %lu\n", table.life_time);
	printf("table.eat_time %lu\n", table.eat_time);
	printf("table.zzz_time %lu\n", table.zzz_time);
	printf("table.max_meals %i\n", table.max_meals);
	printf("table.time %lu\n", table.time);
	printf("table.philo %p\n", table.philo);
	printf("table %p\n", &table);

	if (set_philo(&table, &philo) < 0)
		return (-1);

	printf("---PHILOS-----------------------------------------------------\n");
	size_t	idx;
	idx = 0;
	while(idx < table.n_philos)
	{
		printf("philo id %lu meals %lu\n", philo[idx].id, philo[idx].meal);
		printf("philo pointer  %p and pointer table %p\n", &philo[idx], philo[idx].table);
		idx++;
	}

	printf("---INIT MUTEX-------------------------------------------------\n");
	idx = 0;
	// thread routine
	while (idx < table.n_philos)
		pthread_mutex_init(&table.fork[idx++], NULL);
	pthread_mutex_init(&table.eat, NULL);
	pthread_mutex_init(&table.print, NULL);
	pthread_mutex_init(&table.end, NULL);
	pthread_mutex_init(&table.mutest, NULL);
	printf("the mutexes are initialized\n");
	
	// Need a pthread_t for guardian that is the waiter
	printf("---THREADS PHILOS---------------------------------------------\n");
	idx = 0;
	while (idx < table.n_philos)
	{
		printf(MAG"Philo %zu thread is been launched\n"RST, idx + 1);
		if (pthread_create(&table.th[idx], NULL, routine, &philo[idx]) != 0)
			return (error_terminate(ERR_CTH));
		idx++;
	}
	
	
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
	while (idx < table.n_philos)
		pthread_mutex_destroy(&table.fork[idx++]);
	pthread_mutex_destroy(&table.eat);
	pthread_mutex_destroy(&table.print);
	pthread_mutex_destroy(&table.end);
	pthread_mutex_destroy(&table.mutest);
	printf("Total mails %d\n", mails);
	

	/* 
	 * A pthread_join will used for the guardian
	 */
	return (0);
}
