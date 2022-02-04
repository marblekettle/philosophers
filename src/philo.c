/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: bmans <bmans@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/04 11:08:21 by bmans         #+#    #+#                 */
/*   Updated: 2022/02/04 14:23:49 by bmans         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <string.h>

void	cleanup(t_monit *monit)
{
	UINT	i;

	i = 0;
	while (i < monit->n_philo)
	{
		if (monit->philo && monit->philo[i])
		{
//			pthread_mutex_destroy(&monit->philo[i]->mutex);
			free(monit->philo[i]);
		}
		if (monit->reaper && monit->reaper[i])
		{
//			pthread_mutex_destroy(&monit->reaper[i]->mutex);
			free(monit->reaper[i]);
		}
		i++;
	}
	if (monit->philo)
		free(monit->philo);
	if (monit->reaper)
		free(monit->reaper);
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
	i = 0;
	while (i < monit->n_philo)
	{
		monit->philo[i] = malloc(sizeof(t_philo));
		if (!monit->philo[i])
			return ;
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
		cleanup(&monit);
	}
	else
		help_message();
	return (0);
}
