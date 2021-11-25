/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   monitor.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: bmans <bmans@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/11 11:53:37 by bmans         #+#    #+#                 */
/*   Updated: 2021/11/25 14:43:20 by bmans         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <sys/time.h>

void	*timer(void *t)
{
	struct timeval	start;
	struct timeval	now;

	gettimeofday(&start, NULL);
	while (1)
	{
		gettimeofday(&now, NULL);
		*((UINT *)t) = (now.tv_sec * 1000) + (now.tv_usec / 1000) \
			- (start.tv_sec * 1000) - (start.tv_usec / 1000);
	}
	return (NULL);
}

void	*monitor(void *monit)
{
	pthread_t	time;
	t_monit		*mo;
	UINT		i;

	mo = (t_monit *)monit;
	i = 0;
	pthread_create(&time, NULL, timer, &(mo->time));
	while (i < mo->n_philo)
	{
		pthread_join(mo->philo[i]->philo_thr, NULL);
		i++;
	}
	printf("All threads done.\n");
	return (NULL);
}
