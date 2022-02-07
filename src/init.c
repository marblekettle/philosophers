/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: bmans <bmans@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/07 11:44:08 by bmans         #+#    #+#                 */
/*   Updated: 2022/02/07 13:07:13 by bmans         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "string.h"

static void	link_philos(t_monit *monit)
{
	UINT	i;
	UINT	inext;

	i = 0;
	while (i < monit->n_philo)
	{
		inext = (i + 1) % monit->n_philo;
		monit->philo[i]->next_fork = &(monit->philo[inext]->fork);
		monit->philo[i]->next_mutex = &(monit->philo[inext]->mutex);
		i++;
	}
}

static char	init_philo(t_monit *monit, UINT i, \
	t_philo **philo, t_reaper **reaper)
{
	*philo = malloc(sizeof(t_philo));
	if (!(*philo))
		return (0);
	*reaper = malloc(sizeof(t_reaper));
	if (!(*reaper))
		return (0);
	memset(*philo, 0, sizeof(t_philo));
	memset(*reaper, 0, sizeof(t_reaper));
	(*philo)->monit = monit;
	(*reaper)->monit = monit;
	(*philo)->id = i;
	pthread_mutex_init(&((*philo)->mutex), NULL);
	pthread_mutex_init(&((*reaper)->mutex), NULL);
	(*philo)->reaper = *reaper;
	(*reaper)->philo = *philo;
	return (1);
}

void	init_monit(t_monit *monit, char **av)
{
	UINT	i;

	monit->n_philo = atoui(av[1]);
	monit->time_die = atoui(av[2]);
	monit->time_eat = atoui(av[3]);
	monit->time_sleep = atoui(av[4]);
	monit->philo = (t_philo **)malloc(sizeof(void *) * monit->n_philo);
	if (!monit->philo)
		return ;
	monit->reaper = (t_reaper **)malloc(sizeof(void *) * monit->n_philo);
	if (!monit->reaper)
		return ;
	memset(monit->philo, 0, sizeof(void *) * monit->n_philo);
	memset(monit->reaper, 0, sizeof(void *) * monit->n_philo);
	i = 0;
	while (i < monit->n_philo)
	{
		if (!init_philo(monit, i, &(monit->philo[i]), &(monit->reaper[i])))
			return ;
		i++;
	}
	link_philos(monit);
	//start_threads(monit);
}
