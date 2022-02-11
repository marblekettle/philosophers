/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: bmans <bmans@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/10 11:27:45 by bmans         #+#    #+#                 */
/*   Updated: 2022/02/11 11:44:35 by bmans         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static char	check_stop(t_philo *philo)
{
	char	stop;

	pthread_mutex_lock(&(philo->monit->mutex));
	stop = philo->monit->stop;
	pthread_mutex_unlock(&(philo->monit->mutex));
	return (stop);
}

void	time_message(t_philo *philo, char *msg, char priority)
{
	pthread_mutex_lock(&(philo->monit->mutex));
	if (priority || !philo->monit->stop)
		printf("%u %u %s\n", philo->monit->time, philo->id, msg);
	pthread_mutex_unlock(&(philo->monit->mutex));
}

static char	eat(t_philo *philo)
{
	pthread_mutex_lock(&(philo->f_mutex));
	philo->fork = 1;
	time_message(philo, "takes a fork", 0);
	pthread_mutex_lock(&(philo->next->f_mutex));
	philo->next->fork = 1;
	time_message(philo, "takes a fork", 0);
	pthread_mutex_lock(&(philo->monit->mutex));
	pthread_mutex_lock(&(philo->mutex));
	philo->last_eat = philo->monit->time;
	philo->eat++;
	if (philo->eat == philo->monit->total_eat)
		philo->eat_fin = 1;
	pthread_mutex_unlock(&(philo->mutex));
	pthread_mutex_unlock(&(philo->monit->mutex));
	if (philo->eat > philo->monit->total_eat)
		philo->eat_fin = 1;
	time_message(philo, "is eating", 0);
	usleep(1000 * philo->monit->time_eat);
	philo->fork = 0;
	philo->next->fork = 0;
	pthread_mutex_unlock(&(philo->f_mutex));
	pthread_mutex_unlock(&(philo->next->f_mutex));
	return (check_stop(philo));
}

void	*philo_loop(void *philo)
{
	t_philo	*ph;

	ph = (t_philo *)philo;
	pthread_mutex_lock(&(ph->monit->mutex));
	pthread_mutex_unlock(&(ph->monit->mutex));
	if (ph->id % 2)
		usleep(5000);
	while (!check_stop(ph))
	{
		if (eat(ph))
			break ;
		time_message(ph, "is sleeping", 0);
		usleep(1000 * ph->monit->time_sleep);
		time_message(ph, "is thinking", 0);
	}
	return (NULL);
}
