/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   monitor.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: bmans <bmans@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/11 11:53:37 by bmans         #+#    #+#                 */
/*   Updated: 2022/02/07 14:13:13 by bmans         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <sys/time.h>

void	*stop_sim(t_monit *monit, UINT dead)
{
	UINT	i;

	i = 0;
	monit->any_dead = 1;
	while (i < monit->n_philo)
	{
		pthread_mutex_lock(&(monit->philo[i]->mutex));
		monit->philo[i]->state = DEAD;
		i++;
	}
	printf("%u %i died\n", monit->time, dead);
	i = 0;
	while (i < monit->n_philo)
	{
		pthread_mutex_unlock(&(monit->philo[i]->mutex));
		pthread_join(monit->philo[i]->philo_thr, NULL);
		i++;
	}
	return (NULL);
}

void	*timer(void *monit)
{
	struct timeval	start;
	struct timeval	now;
	UINT			i;
	t_monit			*mo;
	UINT			tally;

	mo = (t_monit *)monit;
	gettimeofday(&start, NULL);
	while (1)
	{	
		gettimeofday(&now, NULL);
		pthread_mutex_lock(&(mo->mutex));
		mo->time = (now.tv_sec * 1000) + (now.tv_usec / 1000) \
			- (start.tv_sec * 1000) - (start.tv_usec / 1000);
		pthread_mutex_unlock(&(mo->mutex));
		i = 0;
		tally = 0;
		while (i < mo->n_philo)
		{
			if (mo->total_eat && mo->philo[i]->eat >= mo->total_eat)
				tally++;
			if (mo->philo[i]->last_eat + mo->time_die < mo->time)
				return (stop_sim(mo, i));
			i++;
		}
		if (tally == mo->n_philo)
			return (NULL);
		usleep(500);
	}
	return (NULL);
}

void	*monitor(void *monit)
{
	t_monit		*mo;
	UINT		i;

	mo = (t_monit *)monit;
	i = 0;
	mo->start = 1;
	timer(monit);
	return (NULL);
}
