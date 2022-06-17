/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Farm Tonita <ftonita@student.21-school.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 07:50:57 by Farm Tonita       #+#    #+#             */
/*   Updated: 2022/06/17 13:48:59 by Farm Tonita      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	philo_died(t_philo *philo, t_args *params)
{
	long long	time;

	sem_wait(philo->death[philo->id - 1]);
	time = get_time();
	if (philo->l_time < time - params->t_started)
	{
		sem_post(philo->death[philo->id - 1]);
		sem_wait(params->print);
		printf("[%7lld] philosopher %d \x1b[35mdied\n\x1b[0m\n",
			time - params->t_started, philo->id);
		exit (1);
	}
	sem_post(philo->death[philo->id - 1]);
}

void	*death_check(void *ptr)
{
	t_args	*params;
	t_philo	*philo;
	int		id;

	params = (t_args *)ptr;
	philo = params->philo;
	id = 0;
	while (id <= params->number_of_philosophers)
	{
		if (id == params->number_of_philosophers)
			id = 0;
		philo_died(philo, params);
		usleep(50);
		id++;
	}
	return (NULL);
}

void	*check_meals(void *ptr)
{
	t_args	*params;
	int		i;

	params = (t_args *)ptr;
	i = 0;
	sem_wait(params->fed_count);
	while (i++ < params->number_of_philosophers)
		sem_wait(params->fed_count);
	sem_wait(params->print);
	exit (1);
	return (NULL);
}
