/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosoph.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: bmans <bmans@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/11 11:56:02 by bmans         #+#    #+#                 */
/*   Updated: 2021/10/11 13:24:37 by bmans         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>

void	*philosopher(void *philo)
{
	t_philo	*ph;

	ph = (t_philo *)philo;
	printf("I am %i\n", ph->id);
	return (NULL);
}
