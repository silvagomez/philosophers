/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilva-g <dsilva-g@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 00:00:43 by dsilva-g          #+#    #+#             */
/*   Updated: 2023/12/20 10:08:36 by dsilva-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int mails = 0;

/*
 * s_time.tv_sec contains the number of seconds.
 * s_time.tv_usec contains the number of microseconds. 
 * The expression (s_time.tv_sec * 1000) converts seconds to milliseconds, and 
 * (s_time.tv_usec / 1000) converts microseconds to milliseconds. 
 * The two results are added together to get the total time in milliseconds, 
 * which is then returned by the function.
 */
size_t	get_current_time(void)
{
	struct timeval	s_time;
	
	gettimeofday(&s_time, NULL);
	return ((s_time.tv_sec * 1000) + (s_time.tv_usec / 1000));
}

void	ft_usleep(size_t time)
{
	size_t	time_stamp;

	time_stamp = get_current_time();
	while ((get_current_time() - time_stamp) < time)
		usleep(10);
}

size_t	complete_meals(t_philo *philo)
{
	size_t	idx;
	size_t	menu;

	idx = 0;
	if (philo->table->max_meals == 0)
		return (0);
	menu = 0;
	while (idx < philo->table->n_philos)
	{
		pthread_mutex_lock(philo[idx]->table->eat);
		//test 0 or idx or nothing
		if (philo[idx]->meal >= philo[0]->table->max_meals)
			menu++;
		idx++;
		pthread_mutex_unlock(philo[idx]->table->eat);
	}
	//test 0 or idx or nothing 
	if (menu == philo[0]->table->n_philos)
	{
		ending();
	}
}

size_t	unhappy_philo(t_philo *philo)
{

}

void	*customer_service(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	ft_usleep(1);
	while (1)
	{
		if (unhappy_philo(philo) || complete_meals(philo))
			break ;
	}
	return (ptr);
}
size_t	is_end(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->end);
	if (philo->ending_flag == 0)
	{
		pthread_mutex_unlock(&philo->table->end);
		return (0);
	}
	pthread_mutex_unlock(&philo->table->end);
	return (1);
}

void	eating(t_philo *philo)
{	
	pthread_mutex_lock(&philo->table->print);
	printf("%lums ", (get_current_time() - philo->table->time));
	printf(HGRN"%lu is eating\n"RST, philo->id);
	pthread_mutex_unlock(&philo->table->print);	
	philo->eating_flag = 1;
	pthread_mutex_lock(&philo->table->eat);
	philo->meal++;
	philo->last_meal_time = get_current_time();
	pthread_mutex_unlock(&philo->table->eat);	
	ft_usleep(philo->table->eat_time);
	philo->eating_flag = 0;
	pthread_mutex_unlock(philo->l_hand);
	pthread_mutex_unlock(philo->r_hand);
}

void	cutlery(t_philo *philo)
{
	if (!is_end(philo))
	{
		pthread_mutex_lock(philo->l_hand);
		pthread_mutex_lock(&philo->table->print);
		printf("%lums ", (get_current_time() - philo->table->time));
		printf("%lu has taken the fork %lu\n", philo->id, philo->id_lhand);
		pthread_mutex_lock(philo->r_hand);
		printf("%lums ", (get_current_time() - philo->table->time));
		printf("%lu has taken the fork %lu\n", philo->id, philo->id_rhand);
		pthread_mutex_unlock(&philo->table->print);
		eating(philo);
	}
}

void	sleeping(t_philo *philo)
{
	if (!is_end(philo))
	{
		pthread_mutex_lock(&philo->table->print);
		printf("%lums ", (get_current_time() - philo->table->time));
		printf("%lu is sleeping\n", philo->id);
		ft_usleep(philo->table->zzz_time);	
		pthread_mutex_unlock(&philo->table->print);
	}
}

void	thinking(t_philo *philo)
{
	if (!is_end(philo))
	{
		pthread_mutex_lock(&philo->table->print);
		printf("%lums ", (get_current_time() - philo->table->time));
		printf("%lu is thinking\n", philo->id);
		pthread_mutex_unlock(&philo->table->print);
	}
}

void	dead(t_philo *philo)
{
	if (is_end(philo))
	{
		pthread_mutex_lock(&philo->table->print);
		printf("%lums ", (get_current_time() - philo->table->time));
		printf("%lu died\n", philo->id);
		pthread_mutex_unlock(&philo->table->print);
	}
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
	{
		ft_usleep(1);
		printf(RED"philo id %lu\n"RST, philo->id);
	}
	//starter
	while (is_end(philo) == 0)
	{
		cutlery(philo);
		sleeping(philo);
		thinking(philo);
	}
	//return (NULL);
	return (ptr);
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
	table->time = get_current_time();
	if (arg[5])
		table->max_meals = ft_atoi(arg[5]);
	else
		table->max_meals = 0;
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
	//	(*philo)[idx].life_time = table->life_time;
		(*philo)[idx].meal = 0;
		(*philo)[idx].last_meal_time = get_current_time();
		(*philo)[idx].table = table;
		(*philo)[idx].ending_flag = 0;
		(*philo)[idx].eating_flag = 0;
		//(*philo)[idx].printing_flag = 0;
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
		printf("last_meal_time: %lu ## ", (*philo)[idx].last_meal_time);
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
	printf("table.max_meals %lu\n", table.max_meals);
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
		printf("philo->table->time %lu\n", philo[idx].table->time);
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
	printf("---THREAD WAITER----------------------------------------------\n");
	if (pthread_create(&table.waiter, NULL, customer_service, philo) != 0)
		return (error_terminate(ERR_CTH));
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
