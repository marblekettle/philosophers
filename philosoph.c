/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosoph.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: bmans <bmans@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/11 11:56:02 by bmans         #+#    #+#                 */
/*   Updated: 2021/11/25 14:41:52 by bmans         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>
#include <unistd.h>

static void	grab_forks(t_philo *philo)
{
	UINT	next;

	next = (philo->id + 1) % philo->monit->n_philo;
	if (philo->id % 2)
	{
		pthread_mutex_lock(&(philo->monit->philo[next]->mutex));
		philo->monit->philo[next]->fork = 1;
		printf("%u %i takes fork %i\n", philo->monit->time, philo->id, next);
	}
	pthread_mutex_lock(&(philo->mutex));
	philo->fork = 1;
	printf("%u %i takes fork %i\n", philo->monit->time, philo->id, philo->id);
	if (!(philo->id % 2))
	{
		pthread_mutex_lock(&(philo->monit->philo[next]->mutex));
		philo->monit->philo[next]->fork = 1;
		printf("%u %i takes fork %i\n", philo->monit->time,  philo->id, next);
	}
}

static void	release_forks(t_philo *philo)
{
	UINT	next;

	next = (philo->id + 1) % philo->monit->n_philo;
	philo->fork = 0;
	philo->monit->philo[next]->fork = 0;
	pthread_mutex_unlock(&(philo->mutex));
	pthread_mutex_unlock(&(philo->monit->philo[next]->mutex));
}

void	*philosopher(void *philo)
{
	t_philo	*ph;

	ph = (t_philo *)philo;
	while (1)
	{
		grab_forks(philo);
		ph->state = EAT;
		usleep(ph->monit->time_eat * 1000);
		release_forks(philo);
		(ph->eat)++;
		if (ph->monit->total_eat > 0 && ph->eat == ph->monit->total_eat)
			break ;
		ph->state = SLEEP;
		usleep(ph->monit->time_sleep * 1000);
		ph->state = THINK;
	}
	printf("I am %i\n", ph->id);
	return (NULL);
}
