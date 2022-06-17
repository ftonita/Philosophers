/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_philo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Farm Tonita <ftonita@student.21-school.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 07:55:12 by Farm Tonita       #+#    #+#             */
/*   Updated: 2022/06/17 13:57:36 by Farm Tonita      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	philo_is_living(t_philo *philo, t_args *params)
{
	print_log(philo, params, 3);
	ft_sleep(params->time_to_eat);
	sem_post(params->forks);
	sem_post(params->forks);
	philo->fed_amount++;
	if (params->eat_count && params->eat_count == philo->fed_amount)
		sem_post(params->fed_count);
	print_log(philo, params, 4);
	ft_sleep(params->time_to_sleep);
	print_log(philo, params, 0);
}

static void	philo_take_forks(t_philo *philo, t_args *params)
{
	long long	time_stamp;

	time_stamp = get_time() - params->t_started;
	if (philo->l_time < time_stamp - params->t_started)
		exit (1);
	sem_wait(params->forks);
	print_log(philo, params, 1);
	sem_wait(params->forks);
	print_log(philo, params, 2);
	time_stamp = get_time() - params->t_started;
	if (philo->l_time < time_stamp - params->t_started)
	{
		sem_post(params->forks);
		sem_post(params->forks);
		exit (1);
	}
	philo->last_eat = time_stamp;
	sem_wait(philo->death[philo->id - 1]);
	philo->l_time = philo->last_eat + params->time_to_die;
	sem_post(philo->death[philo->id - 1]);
	philo_is_living(philo, params);
}

void	routine_philo(t_philo *philo, t_args *params)
{
	if (philo->id % 2 == 0)
	{
		print_log(philo, params, 0);
		usleep((params->time_to_eat - 1) * 990);
	}
	while (1)
		philo_take_forks(philo, params);
}
