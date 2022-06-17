/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   custom.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Farm Tonita <ftonita@student.21-school.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 05:07:00 by Farm Tonita       #+#    #+#             */
/*   Updated: 2022/06/17 05:10:18 by Farm Tonita      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

char	*get_status(int status)
{
	if (status == 0)
		return ("is \x1b[36mthinking\x1b[0m");
	else if (status == 1)
		return ("has \x1b[33mtaken a fork (R)\x1b[0m");
	else if (status == 2)
		return ("has \x1b[33mtaken a fork (L)\x1b[0m");
	else if (status == 3)
		return ("is \x1b[32meating\x1b[0m");
	else if (status == 4)
		return ("is \x1b[34msleeping\x1b[0m");
	return (NULL);
}

int	right_fork_unlock(t_philo *philo)
{
	pthread_mutex_unlock(&philo->forks->m_forks[philo->right_fork]);
	return (1);
}

int	all_forks_unlock(t_philo *philo)
{
	pthread_mutex_unlock(&philo->forks->m_forks[philo->right_fork]);
	pthread_mutex_unlock(&philo->forks->m_forks[philo->left_fork]);
	return (1);
}

int	print_log(t_philo	*philo, int status)
{
	pthread_mutex_lock(&philo->params->print->m_print);
	pthread_mutex_lock(&philo->params->stop->stop);
	if (!philo->params->philo_exit)
	{
		pthread_mutex_unlock(&philo->params->stop->stop);
		printf("[%7zu] philo %d %5s\n",
			get_time() - philo->t_started, philo->id, get_status(status));
		pthread_mutex_unlock(&philo->params->print->m_print);
		return (0);
	}
	pthread_mutex_unlock(&philo->params->print->m_print);
	pthread_mutex_unlock(&philo->params->stop->stop);
	return (0);
}
