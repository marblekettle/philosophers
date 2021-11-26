/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   monitor.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: bmans <bmans@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/11 11:53:37 by bmans         #+#    #+#                 */
/*   Updated: 2021/11/26 11:20:02 by bmans         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <sys/time.h>

void	*stop_sim(t_monit *monit, UINT dead)
{
	UINT	i;

	i = 0;
	while (i < monit->n_philo)
	{
		pthread_detach(monit->philo[i]->philo_thr);
		i++;
	}
	printf("%u %i died\n", monit->time, dead);
	return (NULL);
}

void	*timer(void *monit)
{
	struct timeval	start;
	struct timeval	now;
	UINT			i;
	t_monit			*mo;

	mo = (t_monit *)monit;
	gettimeofday(&start, NULL);
	while (1)
	{	
		gettimeofday(&now, NULL);
		mo->time = (now.tv_sec * 1000) + (now.tv_usec / 1000) \
			- (start.tv_sec * 1000) - (start.tv_usec / 1000);
		i = 0;
		while (i < mo->n_philo)
		{
			if (mo->philo[i]->last_eat + mo->time_die < mo->time)
				return (stop_sim(mo, i));
			i++;
		}
	}
	return (NULL);
}

void	*monitor(void *monit)
{
	t_monit		*mo;
	UINT		i;

	mo = (t_monit *)monit;
	i = 0;
	timer(monit);
	while (i < mo->n_philo)
	{
		pthread_join(mo->philo[i]->philo_thr, NULL);
		i++;
	}
	printf("All threads done.\n");
	return (NULL);
}
