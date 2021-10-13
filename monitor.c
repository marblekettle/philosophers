/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   monitor.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: bmans <bmans@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/11 11:53:37 by bmans         #+#    #+#                 */
/*   Updated: 2021/10/11 13:30:40 by bmans         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>

void	*monitor(void *monit)
{
	t_monit	*mo;
	UINT	i;

	mo = (t_monit *)monit;
	i = 0;
	while (i < mo->n_philo)
	{
		pthread_join(mo->philo[i]->philo_thr, NULL);
		i++;
	}
	printf("All threads done.\n");
	return (NULL);
}
