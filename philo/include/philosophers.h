/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilva-g <dsilva-g@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 22:34:38 by dsilva-g          #+#    #+#             */
/*   Updated: 2023/12/07 12:46:52 by dsilva-g         ###   ########.fr       */
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

typedef struct s_table	t_table;

typedef struct s_philo
{
	size_t			id;
	size_t			l_hand;
	size_t			r_hand;
	int				meals;
	struct s_philo	*next;
	struct s_philo	*prev;
	struct s_philo	*beside;
	t_table			*table;
}				t_philo;

typedef struct s_table
{
	size_t			n_philos;
	size_t			die_time;
	size_t			eat_time;
	size_t			zzz_time;
	int				meals;
	long			time;
	pthread_t		*th;
	pthread_t		waiter;
	pthread_mutex_t	*fork;
	t_philo			*philo;
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
int		philosopher(char *arg[]);

//COLOR
#define BLK		"\033[30m"
#define RED		"\033[31m"
#define GRN		"\033[32m"
#define YEL		"\033[33m"
#define BLU		"\033[34m"
#define MAG		"\033[35m"
#define CYN		"\033[36m"
#define WHT		"\033[37m"
#define RST		"\033[0m"

//HIGH COLOR
#define HBLK	"\033[90m"
#define HRED	"\033[91m"
#define HGRN	"\033[92m"
#define HYEL	"\033[93m"
#define HBLU	"\033[94m"
#define HMAG	"\033[95m"
#define HCYN	"\033[96m"
#define HWHT	"\033[97m"

#endif
