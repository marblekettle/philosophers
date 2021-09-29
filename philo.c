/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: bmans <bmans@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/29 11:49:54 by bmans         #+#    #+#                 */
/*   Updated: 2021/09/29 12:18:32 by bmans         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>

int	main(int ac, char **av)
{
	t_monitor	monit;

	if (ac == 5 || ac == 6)
	{
		
	}
	else
		write(2, "Argument error!\n", 16);
	return (0);
}
