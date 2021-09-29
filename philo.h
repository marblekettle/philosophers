/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: bmans <bmans@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/29 10:44:22 by bmans         #+#    #+#                 */
/*   Updated: 2021/09/29 12:17:02 by bmans         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>

typedef enum e_state
{
	SLEEP,
	THINK,
	EAT,
	DEAD
}	t_state;

typedef struct s_philo
{
	pthread_t		philo_thr;
	t_state			state;
	unsigned char	fork;
	pthread_mutex_t	mutex;
	struct s_monit	*monit;
	UINT			eat;
}					t_philo;

typedef struct s_monit
{
	pthread_t	monit_thr;
	t_philo		**philo;
	UINT		n_philo;
	UINT		time;
	UINT		time_die;
	UINT		time_eat;
	UINT		time_sleep;
	UINT		total_eat;
}				t_monit;

void	*philosopher(void *philo);
void	*monitor(void *monit);

char	is_numeric(const char *str);
UINT	ft_atoui(const char *str);

#endif
