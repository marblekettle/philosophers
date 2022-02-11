/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   aux.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: bmans <bmans@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/29 11:59:12 by bmans         #+#    #+#                 */
/*   Updated: 2022/02/11 10:34:06 by bmans         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

char	error_message(char *msg)
{
	printf("Error: %s\n", msg);
	return (0);
}

static char	is_num(const char c)
{
	return (c >= '0' && c <= '9');
}

char	is_numeric(const char *str)
{
	unsigned short	i;

	i = 0;
	while (str[i])
	{
		if (!is_num(str[i]))
			return (0);
		i++;
	}
	return (1);
}

unsigned int	atoui(const char *str)
{
	unsigned int	out;
	unsigned short	i;

	if (str[0] == '0')
		return (0);
	i = 0;
	out = 0;
	while (str[i])
	{
		if (!is_num(str[i]))
			break ;
		out *= 10;
		out += str[i] - '0';
		i++;
	}
	return (out);
}

void	help_message(void)
{
	printf("%s%s%s\n", "Format: ./philo number_of_philosophers ", \
		"time_to_die time_to_eat time_to_sleep [number_of", \
		"times_each_philosopher_must_eat]");
}
