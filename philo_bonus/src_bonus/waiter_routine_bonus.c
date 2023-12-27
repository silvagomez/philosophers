/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waiter_routine_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilva-g <dsilva-g@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 21:22:18 by dsilva-g          #+#    #+#             */
/*   Updated: 2023/12/27 20:35:01 by dsilva-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

size_t	complete_meals(t_philo *philo)
{
	if (philo->max_meals == 0)
		return (0);
	sem_wait(philo->eat);
	if (philo->meal == philo->max_meals)
	{
		sem_post(philo->fork);
		sem_post(philo->fork);
		return (1);
	}
	sem_post(philo->eat);
	return (0);
}

void	dead(t_philo *philo)
{
	sem_wait(philo->print);
	printf(HRED"%lums ", (get_current_time() - philo->time));
	printf("%lu died\n"RST, philo->id);
	sem_post(philo->print);
}

size_t	unhappy_philo(t_philo *philo)
{
	sem_wait(philo->time_stamp);
	if ((get_current_time() - philo->last_meal_time) >= philo->life_time)
	{
		//sem_wait(philo->end);
		dead(philo);
		return (1);
	}
	sem_post(philo->time_stamp);
	return (0);
}

/*
 * Waiter routine
 * - monitor philos meals
 * - monitor unhappy dead
 */
void	*customer_service(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	while (1)
	{
		ft_usleep(1);
		if (unhappy_philo(philo))
			exit(1);
		if (complete_meals(philo))
		{
			sem_post(philo->eat);
			exit(0);
		}
	}
	return (ptr);
}
