/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: bmans <bmans@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/27 12:13:28 by bmans         #+#    #+#                 */
/*   Updated: 2021/09/27 15:52:41 by bmans         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

typedef struct		s_beacon
{
	unsigned char	state;
	void			*monitor;
}					t_beacon;

typedef	struct		s_monitor
{
	t_beacon		**beacon;
	unsigned int	n_beacons;
	unsigned char	busy;
	pthread_t		**beacon_thr;
	pthread_t		monitor_thr;
	pthread_mutex_t	mutex;
}					t_monitor;

int	waitup(void)
{
	struct timeval	tp;
	int				left;

	gettimeofday(&tp, NULL);
	left = 10000 - (tp.tv_usec % 10000);
	tp.tv_usec += left;
	while (left)
	{
		left--;
		usleep(1);
	}
	return (tp.tv_usec / 1000);
}

void	*beacon(void *beacon)
{
	while (1)
	{
		if (((t_beacon *)beacon)->state == 0)
		{
			pthread_mutex_lock(&(((t_monitor *)(((t_beacon *)beacon)->monitor))->mutex));
			((t_monitor *)(((t_beacon *)beacon)->monitor))->busy = 1;
			((t_beacon *)beacon)->state = 1;
			usleep(50000);
			pthread_mutex_unlock(&(((t_monitor *)(((t_beacon *)beacon)->monitor))->mutex));
			((t_beacon *)beacon)->state = 0;
			((t_monitor *)(((t_beacon *)beacon)->monitor))->busy = 0;
		}
		usleep(30000);
	}
}

void	*monitor(void *monitor)
{
	unsigned int	i;

	while (1)
	{
		i = 0;
		while (i < ((t_monitor *)monitor)->n_beacons)
		{
			if (((t_monitor *)monitor)->beacon[i]->state)
				printf("Beacon %i is busy.\n", i);
			else
				printf("Beacon %i is free.\n", i);
			i++;
		}
		printf("\n");
		waitup();
	}
	return (NULL);
}

void	init_monitor(t_monitor *moni, unsigned int n)
{
	unsigned int	i;

	moni->busy = 0;
	moni->n_beacons = n;
	moni->beacon = malloc(sizeof(t_beacon *) * n);
	moni->beacon_thr = malloc(sizeof(pthread_t *) * n);
	i = 0;
	while (i < n)
	{
		moni->beacon[i] = malloc(sizeof(t_beacon));
		moni->beacon_thr[i] = malloc(sizeof(pthread_t));
		moni->beacon[i]->monitor = moni;
		moni->beacon[i]->state = 0;
		i++;
	}

}

int	main(void)
{
	t_monitor		moni;
	unsigned int	i;
	init_monitor(&moni, 3);
	i = 0;
	pthread_mutex_init(&(moni.mutex), NULL);
	pthread_create(&(moni.monitor_thr), NULL, monitor, &moni);
	while (i < moni.n_beacons)
	{
		pthread_create(moni.beacon_thr[i], NULL, beacon, moni.beacon[i]);
		usleep(100);
		i++;
	}
	pthread_join(moni.monitor_thr, NULL);
	return (0);
}