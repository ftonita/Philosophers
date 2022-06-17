/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Farm Tonita <ftonita@student.21-school.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 04:46:38 by Farm Tonita       #+#    #+#             */
/*   Updated: 2022/06/17 05:22:34 by Farm Tonita      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

size_t	get_time(void)
{
	static struct timeval	time;

	gettimeofday(&time, 0);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

int	ft_sleep(size_t m_secs, t_philo *philo)
{
	size_t	stop;

	stop = get_time() + m_secs;
	while (get_time() < stop)
	{
		pthread_mutex_lock(&philo->params->stop->stop);
		if (philo->params->philo_exit)
		{
			pthread_mutex_unlock(&philo->params->stop->stop);
			return (1);
		}
		pthread_mutex_unlock(&philo->params->stop->stop);
		usleep(500);
	}
	return (0);
}

int	mutex_destroy(t_args *params)
{
	int	id;

	id = 0;
	while (id < params->number_of_philosophers)
		if (pthread_mutex_destroy(&params->forks->m_forks[id++]))
			return (printf("1"));
	id = 0;
	while (id < params->number_of_philosophers)
		if (pthread_mutex_destroy(&params->philo[id++].m_death))
			return (printf("2"));
	if (pthread_mutex_destroy(&params->print->m_print))
		return (printf("3"));
	if (pthread_mutex_destroy(&params->stop->stop))
		return (printf("4"));
	if (pthread_mutex_destroy(&params->meals_mut->mut))
		return (printf("5"));
	return (0);
}

int	free_all(t_args *params, char *err)
{
	if (params->forks)
	{
		if (params->forks->m_forks)
			free(params->forks->m_forks);
		free(params->forks);
	}
	if (params->thread)
		free(params->thread);
	if (params->print)
		free(params->print);
	if (params->philo)
		free(params->philo);
	if (params->stop)
		free(params->stop);
	if (params->meals_mut)
		free(params->meals_mut);
	if (params)
		free(params);
	return (printf("\tStatus: [%s]\n", err));
}

int	ft_atoi(const char *str)
{
	int			i;
	long int	n;

	i = 0;
	n = 0;
	if (str[i] < '0' || str[i] > '9')
		return (-1);
	while (str[i] >= '0' && str[i] <= '9')
	{
		n = n * 10 + ((long int)str[i] - 48);
		if ((str[i + 1] < '0' || str[i + 1] > '9') && str[i + 1])
			return (-1);
		i++;
	}
	return (n);
}
