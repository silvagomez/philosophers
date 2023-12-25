/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waiter_routine.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilva-g <dsilva-g@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 21:22:18 by dsilva-g          #+#    #+#             */
/*   Updated: 2023/12/25 18:13:58 by dsilva-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	dead(t_philo *philo)
{
	if (is_end(philo))
	{
		pthread_mutex_lock(&philo->table->print);
		printf(HRED"%lums ", (get_current_time() - philo->table->time));
		printf("%lu died\n"RST, philo->id);
		pthread_mutex_unlock(&philo->table->print);
	}
}

void	billing(t_philo *philo)
{
	size_t	idx;

	idx = 0;
	while (idx < philo->table->n_philos)
	{
		pthread_mutex_lock(&philo->table->end);
		philo[idx].ending_flag = 1;
		idx++;
		pthread_mutex_unlock(&philo->table->end);
	}
}

size_t	complete_meals(t_philo *philo)
{
	size_t	idx;
	size_t	menu;

	idx = 0;
	if (philo->table->max_meals == 0)
	{
		return (0);
	}
	menu = 0;
	while (idx < philo->table->n_philos)
	{
		pthread_mutex_lock(&philo->table->eat);
		if (philo[idx].meal >= philo[0].table->max_meals)
			menu++;
		idx++;
		pthread_mutex_unlock(&philo->table->eat);
	}
	if (menu == philo->table->n_philos)
	{
		billing(philo);
		return (1);
	}
	return (0);
}

void	unhappy_philo(t_philo *philo)
{
	size_t	idx;

	idx = 0;
	while (!is_end(philo) && idx < philo->table->n_philos)
	{
		pthread_mutex_lock(&philo->table->time_stamp);
		if ((get_current_time() - philo[idx].last_meal_time) >= \
				philo[idx].table->life_time)
		{
			billing(philo);
			dead(philo);
		}
		idx++;
		pthread_mutex_unlock(&philo->table->time_stamp);
	}
}
