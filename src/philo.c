/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: bmans <bmans@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/10 11:27:45 by bmans         #+#    #+#                 */
/*   Updated: 2022/02/10 17:03:27 by bmans         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static char	check_dead(t_philo *philo)
{
	char	any_dead;

	pthread_mutex_lock(&(philo->monit->mutex));
	any_dead = philo->monit->any_dead;
	pthread_mutex_unlock(&(philo->monit->mutex));
	return (any_dead);
}

void	time_message(t_philo *philo, char *msg)
{
	pthread_mutex_lock(&(philo->monit->mutex));
	printf("%u %u %s\n", philo->monit->time, philo->id, msg);
	pthread_mutex_unlock(&(philo->monit->mutex));
}

static char	eat(t_philo *philo)
{
/*	while (1)
	{
		if (!philo->fork && !philo->next->fork)
			break;
		if (check_dead(philo))
			return (1);
	} */
	pthread_mutex_lock(&(philo->f_mutex));
	philo->fork = 1;
	time_message(philo, "takes a fork");
	pthread_mutex_lock(&(philo->next->f_mutex));
	philo->next->fork = 1;
	time_message(philo, "takes a fork");
	pthread_mutex_lock(&(philo->monit->mutex));
	philo->last_eat = philo->monit->time;
	pthread_mutex_unlock(&(philo->monit->mutex));
	philo->eat++;
	if (philo->eat > philo->monit->total_eat)
		philo->eat_fin = 1;
	time_message(philo, "is eating");
	usleep(1000 * philo->monit->time_eat);
	philo->fork = 0;
	philo->next->fork = 0;
	pthread_mutex_unlock(&(philo->f_mutex));
	pthread_mutex_unlock(&(philo->next->f_mutex));
	return (check_dead(philo));
}

void	*philo_loop(void *philo)
{
	t_philo	*ph;

	ph = (t_philo *)philo;
	pthread_mutex_lock(&(ph->monit->mutex));
	pthread_mutex_unlock(&(ph->monit->mutex));
	printf("%u ready\n", ph->id);
	if (ph->id % 2)
		usleep(5000);
	while (!check_dead(ph))
	{
		if (eat(ph))
			break ;
		time_message(ph, "is sleeping");
		usleep(1000 * ph->monit->time_sleep);
		time_message(ph, "is thinking");
	}
	return (NULL);
}
