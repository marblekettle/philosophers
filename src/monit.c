/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   monit.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: bmans <bmans@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/10 15:28:21 by bmans         #+#    #+#                 */
/*   Updated: 2022/02/11 11:38:45 by bmans         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <sys/time.h>

static char	loop_check(t_monit *monit, UINT *has_died)
{
	UINT	i;
	char	all_eat;

	i = 0;
	all_eat = 1;
	while (i < monit->n_philo)
	{
		pthread_mutex_lock(&(monit->philo[i]->mutex));
		if (monit->time - monit->philo[i]->last_eat > monit->time_die)
		{
			*has_died = i;
			return (2);
		}
		if (!monit->philo[i]->eat_fin)
			all_eat = 0;
		pthread_mutex_unlock(&(monit->philo[i]->mutex));
		i++;
	}
	if (monit->total_eat && all_eat)
		return (1);
	return (0);
}

static void	timer(t_monit *monit, struct timeval *start)
{
	struct timeval	now;
	UINT			has_died;
	char			state;

	pthread_mutex_lock(&(monit->mutex));
	state = loop_check(monit, &has_died);
	if (state)
	{
		monit->stop = 1;
		pthread_mutex_unlock(&(monit->mutex));
		if (state == 2)
			time_message(monit->philo[has_died], "died", 1);
		else
			printf("All finished\n");
		return ;
	}
	gettimeofday(&now, NULL);
	monit->time = (now.tv_sec * 1000) + (now.tv_usec / 1000) \
		- (start->tv_sec * 1000) - (start->tv_usec / 1000);
	pthread_mutex_unlock(&(monit->mutex));
}

void	monitor(t_monit *monit)
{
	struct timeval	start;
	UINT			i;

	gettimeofday(&start, NULL);
	pthread_mutex_unlock(&(monit->mutex));
	while (!monit->stop)
	{
		timer(monit, &start);
		usleep(2000);
	}
	i = 0;
	while (i < monit->n_philo)
	{
		pthread_join(monit->philo[i]->philo_thr, NULL);
		i++;
	}
	return ;
}
