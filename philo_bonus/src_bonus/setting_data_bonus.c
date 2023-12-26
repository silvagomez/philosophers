/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setting_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilva-g <dsilva-g@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 21:27:26 by dsilva-g          #+#    #+#             */
/*   Updated: 2023/12/26 11:48:30 by dsilva-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

int	alloc_pid(t_philo *philo)
{
	philo->pid = (int *)malloc(philo->n_philos * sizeof(int));
	if (!philo->pid)
		return (error_terminate("Error malloc pid array"));
	return (0);
}

/*
void	data_philo(t_philo *philo)
{
	printf("---DATA PHILO-------------------------------------------------\n");
	printf("philo.n_philos %lu\n", philo->n_philos);
	printf("philo.life_time %lu\n", philo->life_time);
	printf("philo.eat_time %lu\n", philo->eat_time);
	printf("philo.zzz_time %lu\n", philo->zzz_time);
	printf("philo.max_meals %lu\n", philo->max_meals);
	printf("philo.time %lu\n", philo->time);
}
*/

void	set_philo(t_philo *philo, char *arg[])
{
	philo->n_philos = ft_atoi(arg[1]);
	philo->life_time = ft_atoi(arg[2]);
	philo->eat_time = ft_atoi(arg[3]);
	philo->zzz_time = ft_atoi(arg[4]);
	philo->time = get_current_time();
	if (arg[5])
		philo->max_meals = ft_atoi(arg[5]);
	else
		philo->max_meals = 0;
	philo->meal = 0;
	philo->last_meal_time = get_current_time();
}

void	open_semaphore(t_philo *philo)
{
	sem_unlink("fork");
	sem_unlink("print");
	sem_unlink("eat");
	sem_unlink("time_stamp");
	sem_unlink("end");
	philo->fork = sem_open("fork", O_CREAT, 0644, philo->n_philos);
	philo->print = sem_open("print", O_CREAT, 0644, 1);
	philo->eat = sem_open("eat", O_CREAT, 0644, 1);
	philo->time_stamp = sem_open("time_stamp", O_CREAT, 0644, 1);
	philo->end = sem_open("end", O_CREAT, 0644, 1);
}

void	close_semaphore(t_philo *philo)
{
	sem_close(philo->fork);
	sem_close(philo->print);
	sem_close(philo->eat);
	sem_close(philo->time_stamp);
	sem_close(philo->end);
	sem_unlink("fork");
	sem_unlink("print");
	sem_unlink("eat");
	sem_unlink("time_stamp");
	sem_unlink("end");
}
