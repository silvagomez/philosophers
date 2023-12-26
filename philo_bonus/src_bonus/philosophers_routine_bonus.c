/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_routine.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilva-g <dsilva-g@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 21:22:09 by dsilva-g          #+#    #+#             */
/*   Updated: 2023/12/26 12:18:15 by dsilva-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	eating(t_philo *philo)
{
	sem_wait(philo->fork);
	sem_wait(philo->print);
	printf(RST"%lums ", (get_current_time() - philo->time));
	printf("%lu has taken the fork\n", philo->id);
	sem_post(philo->print);
	sem_wait(philo->fork);
	sem_wait(philo->print);
	printf(RST"%lums ", (get_current_time() - philo->time));
	printf("%lu has taken the fork\n", philo->id);
	printf("%lums ", (get_current_time() - philo->time));
	printf(HGRN"%lu is eating\n"RST, philo->id);
	sem_post(philo->print);
	sem_wait(philo->eat);
	philo->meal++;
	sem_post(philo->eat);
	sem_wait(philo->time_stamp);
	philo->last_meal_time = get_current_time();
	sem_post(philo->time_stamp);
	ft_usleep(philo->eat_time);
	sem_post(philo->fork);
	sem_post(philo->fork);
}

void	sleeping(t_philo *philo)
{
	sem_wait(philo->print);
	printf(RST"%lums ", (get_current_time() - philo->time));
	printf("%lu is sleeping\n", philo->id);
	sem_post(philo->print);
	ft_usleep(philo->zzz_time);
}

void	thinking(t_philo *philo)
{
	sem_wait(philo->print);
	printf(RST"%lums ", (get_current_time() - philo->time));
	printf("%lu is thinking\n", philo->id);
	sem_post(philo->print);
}
