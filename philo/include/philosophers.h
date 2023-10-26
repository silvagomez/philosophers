/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilva-g <dsilva-g@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 22:34:38 by dsilva-g          #+#    #+#             */
/*   Updated: 2023/10/26 15:51:47 by dsilva-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <string.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/time.h>
# include <pthread.h>

# include "error.h"

typedef struct	s_data
{
	size_t	n_philos;
	size_t	life_time;
	size_t	eat_time;
	size_t	zzz_time;
	size_t	n_meals;
	pthread_t	*philo;
	//pthread_mutex_t
}				t_data;

// fork?
typedef struct	s_philo
{
	size_t		philo_id;
	size_t		l_hand;
	size_t		r_hand;	
	t_data		*data;
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
void	philosopher(char *arg[]);

#endif
