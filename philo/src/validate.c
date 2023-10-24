/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilva-g <dsilva-g@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 21:28:02 by dsilva-g          #+#    #+#             */
/*   Updated: 2023/10/24 23:56:12 by dsilva-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	validate_char(char *ar[])
{
	size_t	i;
	size_t	j;

	i = 1;
	while (ar[i])
	{
		j = 0;
		while (ar[i][j])
		{
			if (!ft_isdigit(ar[i][j]))
				return (error_terminate(ERR_CHR));
			j++;
		}
		i++;
	}
	return (1);
}

int	validate_arg(char *ar[])
{
	if (validate_char(ar) < 0)
		return (-1);
	if (ft_atoi(ar[1]) < 1)
		return (error_terminate(ERR_NPH));
	// error control if number of philo == 1
	if (ar[5] && ft_atoi(ar[5]) < 1)
		return (error_terminate(ERR_NML));
	return (1);
}
