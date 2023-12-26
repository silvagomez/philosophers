/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_bonus.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilva-g <dsilva-g@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 22:34:38 by dsilva-g          #+#    #+#             */
/*   Updated: 2023/12/26 01:18:55 by dsilva-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_BONUS_H
# define PHILOSOPHERS_BONUS_H

# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/time.h>
# include <pthread.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <semaphore.h>
# include <signal.h>
# include <sys/wait.h>

# include "error_bonus.h"

typedef struct s_philo
{
	size_t		id;
	size_t		n_philos;
	size_t		life_time;
	size_t		eat_time;
	size_t		zzz_time;
	size_t		time;
	size_t		max_meals;
	size_t		meal;
	size_t		last_meal_time;
	size_t		id_lhand;
	size_t		id_rhand;
	int			*pid;
	sem_t		*fork;
	sem_t		*print;
	sem_t		*eat;
	sem_t		*end;			
	sem_t		*time_stamp;
	pthread_t	waiter;
}				t_philo;

// error
int		error_terminate(char *s);

// validate
int		validate_arg(char *ar[]);

// utils_1
void	ft_putendl_fd(char *s, int fd);
int		ft_isdigit(int c);
int		ft_atoi(const char *str);

// philosophers
int		philosopher(char *arg[]);

// setting_data
void	set_philo(t_philo *philo, char *arg[]);
int		alloc_pid(t_philo *philo);


//threading

// utils_2
size_t	get_current_time(void);
void	ft_usleep(size_t time);
size_t	is_end(t_philo *philo);

// philosopher_routine
void	eating(t_philo *philo);
void	sleeping(t_philo *philo);
void	thinking(t_philo *philo);

// waiter_routine
size_t	unhappy_philo(t_philo *philo);
size_t	complete_meals(t_philo *philo);
void	dead(t_philo *philo);
#endif
