/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: bmans <bmans@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/29 11:49:54 by bmans         #+#    #+#                 */
/*   Updated: 2021/09/29 14:13:04 by bmans         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

void	cleanup_monit(t_monit *monit)
{
	UINT	i;

	if (monit->philo)
	{
		i = 0;
		while (i < monit->n_philo)
		{
			if (monit->philo[i])
				free(monit->philo[i]);
			i++;
		}
		free(monit->philo);
	}
}

void	init_monit(t_monit *monit, char **args)
{
	UINT	i;

	monit->n_philo = atoui(args[1]);
	monit->time_die = atoui(args[2]);
	monit->time_eat = atoui(args[3]);
	monit->time_sleep = atoui(args[4]);
	monit->philo = (t_philo **)malloc(sizeof(void *) * monit->n_philo);
	if (!monit->philo)
		return ;
	i = 0;
	while (i < monit->n_philo)
	{
		monit->philo[i] = malloc(sizeof(t_philo));
		if (!monit->philo[i])
			return ;
		memset(monit->philo[i], 0, sizeof(t_philo));
		monit->philo[i]->monit = monit;
		pthread_mutex_init(&(monit->philo[i]->mutex), NULL);
		i++;
	}
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
				write(2, "Invalid arguments!\n", 19);
				return (0);
			}
			i++;
		}
		memset(&monit, 0, sizeof(t_monit));
		if (ac == 6)
			monit.total_eat = atoui(av[5]);
		init_monit(&monit, av);
		cleanup_monit(&monit);
	}
	else
		printf("%s %s %s\n", "Format: ./philo number_of_philosophers", \
			"time_to_die time_to_eat time_to_sleep [number of", \
			"times_each_philosopher_must_eat]");
	return (0);
}
