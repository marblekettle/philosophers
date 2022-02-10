/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   monit.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: bmans <bmans@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/10 15:28:21 by bmans         #+#    #+#                 */
/*   Updated: 2022/02/10 16:42:06 by bmans         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <sys/time.h>

void	monitor(t_monit *monit)
{
	struct timeval	start;
	struct timeval	now;
	UINT			i;

	gettimeofday(&start, NULL);
	pthread_mutex_unlock(&(monit->mutex));
	while (!monit->any_dead)
	{
		i = 0;
		pthread_mutex_lock(&(monit->mutex));
		while (i < monit->n_philo)
		{
			pthread_mutex_lock(&(monit->philo[i]->mutex));
			if (monit->time - monit->philo[i]->last_eat > monit->time_die)
			{
				monit->any_dead = 1;
				break ;
			}
			pthread_mutex_unlock(&(monit->philo[i]->mutex));
			i++;
		}
		gettimeofday(&now, NULL);
		monit->time = (now.tv_sec * 1000) + (now.tv_usec / 1000) \
			- (start.tv_sec * 1000) - (start.tv_usec / 1000);
		pthread_mutex_unlock(&(monit->mutex));
		usleep(2000);
	}
	time_message(monit->philo[i], "died");
	i = 0;
	while (i < monit->n_philo)
	{
		pthread_join(monit->philo[i]->philo_thr, NULL);
		i++;
	}
	return ;
}
