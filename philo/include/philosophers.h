/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilva-g <dsilva-g@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 22:34:38 by dsilva-g          #+#    #+#             */
/*   Updated: 2023/12/25 16:46:27 by dsilva-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/time.h>
# include <pthread.h>

# include "error.h"

/*
typedef struct s_philo
{
	size_t			id;
	size_t			l_hand;
	size_t			r_hand;
	pthread_mutex_t	l_hand;
	pthread_mutex_t	r_hand;
	int				meals;
	struct s_philo	*next;
	struct s_philo	*prev;
	struct s_philo	*beside;
	t_table			*table;
}				t_philo;
*/

typedef struct s_table
{
	size_t			n_philos;
	size_t			life_time;
	size_t			eat_time;
	size_t			zzz_time;
	size_t			time;
	size_t			max_meals;
	pthread_t		*th;
	pthread_t		waiter;
	pthread_mutex_t	*fork;
	pthread_mutex_t	eat;
	pthread_mutex_t	print;
	pthread_mutex_t	end;
	pthread_mutex_t	time_stamp;
}				t_table;

typedef struct s_philo
{
	size_t			id;
	size_t			meal;
	size_t			last_meal_time;
	size_t			id_lhand;
	size_t			id_rhand;
	pthread_mutex_t	*l_hand;
	pthread_mutex_t	*r_hand;
	//size_t			eating_flag;
	size_t			ending_flag;
	t_table			*table;
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
int	set_table(t_table *table, char *arg[]);
int	set_philo(t_table *table, t_philo **philo);
int	alloc_fork(t_table *table);
int	alloc_thread(t_table *table);

//mutexing
void	init_mutex(t_table *table);
void	destroy_mutex(t_table *table);

//threading
int	launching_thread(t_table *table, t_philo **philo);
int	waiting_for_thread(t_table *table);
void	*routine(void *ptr);
void	*customer_service(void *ptr);

// utils_2
size_t	get_current_time(void);
void	ft_usleep(size_t time);
size_t	is_end(t_philo *philo);

// philosopher_routine
void	cutlery(t_philo *philo);
void	eating(t_philo *philo);
void	sleeping(t_philo *philo);
void	thinking(t_philo *philo);

// waiter_routine
void	unhappy_philox2(t_philo *philo);
size_t	complete_meals(t_philo *philo);
void	billing(t_philo *philo);
void	dead(t_philo *philo);
size_t	is_end(t_philo *philo);
#endif
