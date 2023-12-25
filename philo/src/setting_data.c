/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setting_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilva-g <dsilva-g@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 21:27:26 by dsilva-g          #+#    #+#             */
/*   Updated: 2023/12/25 13:38:31 by dsilva-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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
	while (idx < table->n_philos)
	{
		(*philo)[idx].id = idx + 1;
		(*philo)[idx].meal = 0;
		(*philo)[idx].last_meal_time = get_current_time();
		(*philo)[idx].table = table;
		(*philo)[idx].ending_flag = 0;
		//(*philo)[idx].eating_flag = 0;
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


