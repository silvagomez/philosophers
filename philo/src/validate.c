/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilva-g <dsilva-g@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 21:28:02 by dsilva-g          #+#    #+#             */
/*   Updated: 2023/12/25 11:26:32 by dsilva-g         ###   ########.fr       */
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
	if (validate_char(arg) < 0)
		return (-1);
	if (ft_atoi(arg[1]) == 1)
	{
		printf("0ms 1 has taken the fork 1\n");
		printf(HRED"%lu 1 died\n"RST, (size_t)ft_atoi(arg[2]));
		return (-1);
	}
	return (1);
}
