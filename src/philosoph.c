/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosoph.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: bmans <bmans@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/11 11:56:02 by bmans         #+#    #+#                 */
/*   Updated: 2022/02/07 14:31:05 by bmans         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>
#include <unistd.h>

static char	check_stop(t_philo *ph)
{
	return (ph->state == DEAD || ph->monit->any_dead);
}

static char	grab_forks(t_philo *philo)
{
	UINT	next;

	next = (philo->id + 1) % philo->monit->n_philo;
	while (philo->fork || philo->monit->philo[next]->fork)
	{
		if (check_stop(philo))
			return (1);
		usleep(10);
	}
	pthread_mutex_lock(&(philo->mutex));
	pthread_mutex_lock(&(philo->monit->philo[next]->mutex));
	philo->fork = 1;
	printf("%u %i takes fork %i\n", philo->monit->time, philo->id, philo->id);
	philo->monit->philo[next]->fork = 1;
	printf("%u %i takes fork %i\n", philo->monit->time, philo->id, next);
	return (0);
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
	while (!(ph->monit->start))
		usleep(100);
	usleep(100 * (ph->id % 2));
	while (!check_stop(ph))
	{
		usleep(500);
		if (grab_forks(philo))
			break ;
		ph->state = EAT;
		ph->last_eat = ph->monit->time;
		printf("%u %i is eating\n", ph->monit->time, ph->id);
		usleep(ph->monit->time_eat * 1000);
		release_forks(philo);
		(ph->eat)++;
		if ((ph->monit->total_eat > 0 && ph->eat == ph->monit->total_eat) || check_stop(ph))
			break ;
		printf("%u %i is sleeping\n", ph->monit->time, ph->id);
		ph->state = SLEEP;
		usleep(ph->monit->time_sleep * 1000);
		if (check_stop(ph))
			break ;
		printf("%u %i is thinking\n", ph->monit->time, ph->id);
		ph->state = THINK;
	}
	return (NULL);
}
