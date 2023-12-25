/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_routine.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilva-g <dsilva-g@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 21:22:09 by dsilva-g          #+#    #+#             */
/*   Updated: 2023/12/25 18:13:42 by dsilva-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->print);
	printf("%lums ", (get_current_time() - philo->table->time));
	printf(HGRN"%lu is eating\n"RST, philo->id);
	pthread_mutex_unlock(&philo->table->print);
	pthread_mutex_lock(&philo->table->eat);
	philo->meal++;
	pthread_mutex_unlock(&philo->table->eat);
	pthread_mutex_lock(&philo->table->time_stamp);
	philo->last_meal_time = get_current_time();
	pthread_mutex_unlock(&philo->table->time_stamp);
	ft_usleep(philo->table->eat_time);
}

void	cutlery(t_philo *philo)
{
	pthread_mutex_lock(philo->l_hand);
	if (!is_end(philo))
	{
		pthread_mutex_lock(&philo->table->print);
		printf("%lums ", (get_current_time() - philo->table->time));
		printf("%lu has taken the fork %lu\n", philo->id, philo->id_lhand);
		pthread_mutex_unlock(&philo->table->print);
	}
	pthread_mutex_lock(philo->r_hand);
	if (!is_end(philo))
	{
		pthread_mutex_lock(&philo->table->print);
		printf("%lums ", (get_current_time() - philo->table->time));
		printf("%lu has taken the fork %lu\n", philo->id, philo->id_rhand);
		pthread_mutex_unlock(&philo->table->print);
	}
	if (!is_end(philo))
	{
		eating(philo);
		pthread_mutex_unlock(philo->l_hand);
		pthread_mutex_unlock(philo->r_hand);
	}
}

void	sleeping(t_philo *philo)
{
	if (!is_end(philo))
	{
		pthread_mutex_lock(&philo->table->print);
		printf("%lums ", (get_current_time() - philo->table->time));
		printf("%lu is sleeping\n", philo->id);
		pthread_mutex_unlock(&philo->table->print);
		ft_usleep(philo->table->zzz_time);
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
