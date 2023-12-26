/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilva-g <dsilva-g@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 23:18:45 by dsilva-g          #+#    #+#             */
/*   Updated: 2023/12/26 13:21:16 by dsilva-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# define ERR_ARG "ERROR: invalid number of arguments."
# define ERR_CHR "ERROR: args should be digits."
# define ERR_LZR "ERROR: needs values higher than 0."
# define ERR_CTH "ERROR: failed to create thread."
# define ERR_JTH "ERROR: calling wait thread."
# define ERR_MTH "ERROR: malloc thread."
# define ERR_MMT "ERROR: malloc mutex."
# define ERR_MPH "ERROR: malloc philo sructure"

//COLOR
# define BLK	"\033[30m"
# define RED	"\033[31m"
# define GRN	"\033[32m"
# define YEL	"\033[33m"
# define BLU	"\033[34m"
# define MAG	"\033[35m"
# define CYN	"\033[36m"
# define WHT	"\033[37m"
# define RST	"\033[0m"

//HIGH COLOR
# define HBLK	"\033[90m"
# define HRED	"\033[91m"
# define HGRN	"\033[92m"
# define HYEL	"\033[93m"
# define HBLU	"\033[94m"
# define HMAG	"\033[95m"
# define HCYN	"\033[96m"
# define HWHT	"\033[97m"

#endif
