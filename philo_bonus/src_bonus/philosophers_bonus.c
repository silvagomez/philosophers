/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilva-g <dsilva-g@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 00:00:43 by dsilva-g          #+#    #+#             */
/*   Updated: 2023/12/26 12:18:17 by dsilva-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

int	launching(t_philo *philo)
{
	if (pthread_create(&philo->waiter, NULL, &customer_service, philo) != 0)
		return (error_terminate(ERR_CTH));
	if (philo->id % 2 == 0)
		ft_usleep(50);
	while (1)
	{
		eating(philo);
		sleeping(philo);
		thinking(philo);
	}
	printf(RST"Waiter end1\n");
	if (pthread_join(philo->waiter, NULL) != 0)
		return (error_terminate(ERR_JTH));
	printf(RST"Waiter end2\n");
}

void	terminate_philosopher(t_philo *philo)
{
	size_t	idx;
	int		status;

	idx = 0;
	while (idx < philo->n_philos)
	{
		waitpid(-1, &status, 0);
		if (status != 0)
		{
			idx = 0;
			while (idx < philo->n_philos)
					kill(philo->pid[idx++], SIGKILL);
			break;
		}
		idx++;
	}
}

int	philosopher(char *arg[])
{
	t_philo	philo;
	size_t	idx;

	set_philo(&philo, arg);
	if (alloc_pid(&philo) < 0)
		return (-1);
	open_semaphore(&philo);
	idx = 0;
	while (idx < philo.n_philos)
	{
		philo.pid[idx] = fork();
		if (philo.pid[idx] < 0)
			return (free(philo.pid), error_terminate("Error forking"));
		if (philo.pid[idx] == 0)
		{
			philo.id = idx + 1;
			//philo.last_meal_time = get_current_time();
			launching(&philo);
		}
		idx++;
	}
	terminate_philosopher(&philo);
	close_semaphore(&philo);
	free(philo.pid);
	return (0);
}
