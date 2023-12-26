/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilva-g <dsilva-g@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 21:13:24 by dsilva-g          #+#    #+#             */
/*   Updated: 2023/12/25 21:46:44 by dsilva-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

/*
 * s_time.tv_sec contains the number of seconds.
 * s_time.tv_usec contains the number of microseconds. 
 * The expression (s_time.tv_sec * 1000) converts seconds to milliseconds, and 
 * (s_time.tv_usec / 1000) converts microseconds to milliseconds. 
 * The two results are added together to get the total time in milliseconds, 
 * which is then returned by the function.
 */
size_t	get_current_time(void)
{
	struct timeval	s_time;

	gettimeofday(&s_time, NULL);
	return ((s_time.tv_sec * 1000) + (s_time.tv_usec / 1000));
}

void	ft_usleep(size_t time)
{
	size_t	time_stamp;

	time_stamp = get_current_time();
	while ((get_current_time() - time_stamp) < time)
		usleep(500);
}
