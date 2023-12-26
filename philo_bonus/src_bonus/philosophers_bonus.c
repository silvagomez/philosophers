/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilva-g <dsilva-g@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 00:00:43 by dsilva-g          #+#    #+#             */
/*   Updated: 2023/12/26 02:11:25 by dsilva-g         ###   ########.fr       */
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

size_t	complete_meals(t_philo *philo)
{
	if (philo->max_meals == 0)
	{
		return (0);
	}
	sem_wait(philo->eat);
	if (philo->meal == philo->max_meals)
	{
		//sem_pos(philo->eat);
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
		dead(philo);
		//sem_post(philo->time_stamp);
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
		ft_usleep(10);
		if (unhappy_philo(philo))
			exit(1);
		if (complete_meals(philo))
			exit(0);
	}
	return (ptr);
}

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
