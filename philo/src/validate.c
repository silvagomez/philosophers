/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilva-g <dsilva-g@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 21:28:02 by dsilva-g          #+#    #+#             */
/*   Updated: 2023/10/27 01:13:30 by dsilva-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	validate_char(char *arg[])
{
	size_t	i;
	size_t	j;

	i = 1;
	while (arg[i])
	{
		j = 0;
		while (arg[i][j])
		{
			if (!ft_isdigit(arg[i][j]))
				return (error_terminate(ERR_CHR));
			j++;
		}
		if (ft_atoi(arg[i]) < 1)
			return (error_terminate(ERR_LZR));
		i++;
	}
	return (1);
}

int	validate_arg(char *arg[])
{
	// if there is not more to validate, bring fn() above to here.
	if (validate_char(arg) < 0)
		return (-1);
	// error control if number of philo == 1
	return (1);
}
