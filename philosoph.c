/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosoph.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: bmans <bmans@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/11 11:56:02 by bmans         #+#    #+#                 */
/*   Updated: 2021/10/13 10:12:37 by bmans         ########   odam.nl         */
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
		printf("%i takes fork %i\n", philo->id, next);
	}
	pthread_mutex_lock(&(philo->mutex));
	philo->fork = 1;
	printf("%i takes fork %i\n", philo->id, philo->id);
	if (!(philo->id % 2))
	{
		pthread_mutex_lock(&(philo->monit->philo[next]->mutex));
		philo->monit->philo[next]->fork = 1;
		printf("%i takes fork %i\n", philo->id, next);
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
	grab_forks(philo);
	usleep(500000);
	release_forks(philo);
	printf("I am %i\n", ph->id);
	return (NULL);
}
