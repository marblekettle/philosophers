/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: bmans <bmans@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/10 11:27:26 by bmans         #+#    #+#                 */
/*   Updated: 2022/02/11 10:36:19 by bmans         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <string.h>

static void	cleanup(t_monit *monit)
{
	UINT	i;

	if (monit->philo)
	{
		i = 0;
		while (i < monit->n_philo)
		{
			if (monit->philo[i])
			{
				pthread_mutex_destroy(&(monit->philo[i]->mutex));
				pthread_mutex_destroy(&(monit->philo[i]->f_mutex));
				free(monit->philo[i]);
			}
			i++;
		}
		free(monit->philo);
	}
	pthread_mutex_destroy(&(monit->mutex));
}

static void	start_threads(t_monit *monit)
{
	UINT	i;

	i = monit->n_philo;
	pthread_mutex_lock(&(monit->mutex));
	while (i > 0)
	{
		i--;
		pthread_create(&(monit->philo[i]->philo_thr), \
			NULL, philo_loop, monit->philo[i]);
	}
	monitor(monit);
}

static char	init_philo(t_philo **philo, t_monit *monit, UINT id)
{
	*philo = malloc(sizeof(t_philo));
	if (!*philo)
		return (error_message("Malloc fail"));
	memset(*philo, 0, sizeof(t_philo));
	(*philo)->monit = monit;
	(*philo)->id = id;
	if (pthread_mutex_init(&((*philo)->mutex), NULL))
		return (error_message("Mutex init fail"));
	if (pthread_mutex_init(&((*philo)->f_mutex), NULL))
		return (error_message("Mutex init fail"));
	if (id >= 1)
		monit->philo[id - 1]->next = *philo;
	return (1);
}

static char	init_monit(t_monit *monit, char **args)
{
	UINT	i;

	monit->n_philo = atoui(args[1]);
	monit->time_die = atoui(args[2]);
	monit->time_eat = atoui(args[3]);
	monit->time_sleep = atoui(args[4]);
	monit->philo = (t_philo **)malloc(sizeof(void *) * monit->n_philo);
	if (!monit->philo)
		return (error_message("Malloc fail"));
	if (pthread_mutex_init(&(monit->mutex), NULL))
		return (error_message("Mutex init fail"));
	i = 0;
	while (i < monit->n_philo)
	{
		if (!init_philo(&(monit->philo[i]), monit, i))
			return (0);
		i++;
	}
	monit->philo[monit->n_philo - 1]->next = monit->philo[0];
	start_threads(monit);
	return (0);
}

int	main(int ac, char **av)
{
	t_monit			monit;
	unsigned short	i;

	if (ac == 5 || ac == 6)
	{
		i = 1;
		while (i < ac)
		{
			if (!is_numeric(av[i]))
			{
				printf("Invalid arguments!\n");
				return (0);
			}
			i++;
		}
		memset(&monit, 0, sizeof(t_monit));
		if (ac == 6)
			monit.total_eat = atoui(av[5]);
		init_monit(&monit, av);
		cleanup(&monit);
	}
	else
		help_message();
	return (0);
}
