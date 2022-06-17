/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_philo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Farm Tonita <ftonita@student.21-school.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 04:46:46 by Farm Tonita       #+#    #+#             */
/*   Updated: 2022/06/17 05:10:12 by Farm Tonita      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	philo_is_living(t_philo *philo, t_args *params)
{
	if (print_log(philo, 3))
		return (all_forks_unlock(philo));
	if (ft_sleep(params->time_to_eat, philo))
		return (all_forks_unlock(philo));
	pthread_mutex_unlock(&philo->forks->m_forks[philo->right_fork]);
	pthread_mutex_unlock(&philo->forks->m_forks[philo->left_fork]);
	philo->fed_amount++;
	if (params->eat_count && params->eat_count == philo->fed_amount)
	{
		pthread_mutex_lock(&philo->meals_mut->mut);
		params->fed_count++;
		pthread_mutex_unlock(&philo->meals_mut->mut);
	}
	if (print_log(philo, 4))
		return (1);
	if (ft_sleep(params->time_to_sleep, philo))
		return (1);
	return (0);
}

int	philo_dead_check(t_philo *philo, t_args *params, size_t time)
{
	pthread_mutex_lock(&philo->m_death);
	if (philo->l_time < time)
	{
		pthread_mutex_unlock(&philo->m_death);
		pthread_mutex_lock(&params->stop->stop);
		params->philo_exit = 1;
		pthread_mutex_unlock(&params->stop->stop);
		return (1);
	}
	pthread_mutex_unlock(&philo->m_death);
	pthread_mutex_lock(&params->stop->stop);
	if (params->philo_exit == 1)
	{
		pthread_mutex_unlock(&params->stop->stop);
		return (1);
	}
	pthread_mutex_unlock(&params->stop->stop);
	philo->last_eat = time;
	pthread_mutex_lock(&philo->m_death);
	philo->l_time = philo->last_eat + params->time_to_die;
	pthread_mutex_unlock(&philo->m_death);
	return (0);
}

int	take_forks(t_philo *philo, t_args *params)
{
	size_t	time;

	pthread_mutex_lock(&params->stop->stop);
	if (params->philo_exit)
	{
		pthread_mutex_unlock(&params->stop->stop);
		return (1);
	}
	pthread_mutex_unlock(&params->stop->stop);
	pthread_mutex_lock(&philo->forks->m_forks[philo->right_fork]);
	if (print_log(philo, 1))
		return (right_fork_unlock(philo));
	pthread_mutex_lock(&philo->forks->m_forks[philo->left_fork]);
	if (print_log(philo, 2))
		return (all_forks_unlock(philo));
	time = get_time() - philo->t_started;
	if (philo_dead_check(philo, params, time))
		return (all_forks_unlock(philo));
	return (philo_is_living(philo, params));
}

void	*routine_philo(void *tmp)
{
	t_philo	*philo;
	t_args	*params;

	philo = (t_philo *)tmp;
	params = philo->params;
	if (philo->id % 2 == 0)
	{
		print_log(philo, 0);
		usleep((params->time_to_eat - 1) * 990);
	}
	while (1)
	{
		pthread_mutex_lock(&params->stop->stop);
		if (params->philo_exit)
		{
			pthread_mutex_unlock(&params->stop->stop);
			return (NULL);
		}
		pthread_mutex_unlock(&params->stop->stop);
		if (take_forks(philo, params))
			return (NULL);
		if (print_log(philo, 0))
			return (NULL);
	}
	return (NULL);
}
