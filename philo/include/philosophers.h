/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilva-g <dsilva-g@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 22:34:38 by dsilva-g          #+#    #+#             */
/*   Updated: 2023/12/15 10:20:29 by dsilva-g         ###   ########.fr       */
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

typedef struct	s_table t_table;

typedef struct	s_philo
{
	size_t			id;
	size_t			l_hand;
	size_t			r_hand;
	int				meals;
	struct s_philo	*next;
	struct s_philo	*prev;
	struct s_philo	*beside;
	t_table		*table;
}				t_philo;

typedef struct	s_table
{
	size_t			n_philos;
	size_t			life_time;
	size_t			eat_time;
	size_t			zzz_time;
	int				meals;
	long			time;
	pthread_t		*th;
	pthread_mutex_t	*fork;
	t_philo			*philo;
	//pthread_mutex_t
}				t_table;

// error
int		error_terminate(char *s);

// validate
int		validate_arg(char *ar[]);

// utils_1
void	ft_putendl_fd(char *s, int fd);
int		ft_isdigit(int c);
int		ft_atoi(const char *str);

// philosophers
int	philosopher(char *arg[]);

#endif
