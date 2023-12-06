/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilva-g <dsilva-g@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 22:30:36 by dsilva-g          #+#    #+#             */
/*   Updated: 2023/12/06 17:59:28 by dsilva-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int ac, char *ar[])
{
	if (ac < 5 || ac > 6)
		return (error_terminate(ERR_ARG));
	if (validate_arg(ar) < 0)
		return (-1);
	if (philosopher(ar) < 0)
		return (-1);
	return (0);
}
