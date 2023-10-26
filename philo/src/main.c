/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilva-g <dsilva-g@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 22:30:36 by dsilva-g          #+#    #+#             */
/*   Updated: 2023/10/25 00:00:20 by dsilva-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int ac, char *ar[])
{
	if (ac < 5 || ac > 6)
		return (error_terminate(ERR_ARG));
	if (validate_arg(ar) < 0)
		return (-1);
	philosopher(ar);
	return (0);
}
