/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Farm Tonita <ftonita@student.21-school.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 04:46:55 by Farm Tonita       #+#    #+#             */
/*   Updated: 2022/06/17 05:20:22 by Farm Tonita      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	philo_died(t_philo *philo, t_args *params, int id)
{
	size_t	time;

	pthread_mutex_lock(&params->stop->stop);
	time = get_time();
	if (philo[id].l_time < time - philo[id].t_started)
	{
		pthread_mutex_unlock(&philo[id].m_death);
		if (params->philo_exit)
			return (1);
		params->philo_exit = 1;
		pthread_mutex_lock(&params->print->m_print);
		printf("[%7zu] philo %d \x1b[35mdied\n\x1b[0m\n",
			time - params->t_started, philo[id].id);
		pthread_mutex_unlock(&params->stop->stop);
		return (1);
	}
	pthread_mutex_unlock(&params->stop->stop);
	return (0);
}

int	check_philos_had_eaten(t_philo *philo, t_args *params)
{
	(void) philo;
	pthread_mutex_lock(&philo->meals_mut->mut);
	if (params->fed_count == params->number_of_philosophers)
	{
		pthread_mutex_lock(&params->stop->stop);
		params->philo_exit = 1;
		pthread_mutex_unlock(&params->stop->stop);
		pthread_mutex_unlock(&philo->meals_mut->mut);
		return (1);
	}
	pthread_mutex_unlock(&philo->meals_mut->mut);
	return (0);
}

void	*ft_observer(void *ptr)
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
		{
			id = 0;
			if (check_philos_had_eaten(philo, params))
				return (NULL);
		}
		pthread_mutex_lock(&philo[id].m_death);
		if (philo_died(philo, params, id))
			return (NULL);
		pthread_mutex_unlock(&philo[id].m_death);
		usleep(50);
		id++;
	}
	return (NULL);
}

int	launch_all(t_args *params, int i)
{
	pthread_t	observer;
	int			id;

	while (i < params->number_of_philosophers)
	{
		if (pthread_create(&params->thread[i], 0,
				&routine_philo, &params->philo[i]))
			return (free_all(params, "pthread_create error!"));
		usleep(50);
		i += 1;
	}
	if (pthread_create(&observer, NULL, &ft_observer, params))
		return (7);
	if (pthread_join(observer, NULL))
		return (8);
	if (params->number_of_philosophers == 1)
		pthread_mutex_unlock(&params->philo->forks
			->m_forks[params->philo->right_fork]);
	pthread_mutex_unlock(&params->print->m_print);
	pthread_mutex_unlock(&params->stop->stop);
	id = 0;
	while (id < params->number_of_philosophers)
		if (pthread_join(params->thread[id++], NULL))
			return (8);
	return (0);
}

int	main(int argc, char **argv)
{
	t_args	*params;

	if (argc < 5 || argc > 6)
		return (printf("\tHint: ARGS count must be 4 or 5 only!\n"));
	params = (t_args *) malloc(sizeof(t_args));
	if (ft_valid_args(argv, params))
		return (free_all(params, "Invalid args!"));
	if (ft_philo_init(params))
		return (free_all(params, "Philos Init error!"));
	if (launch_all(params, 0))
		return (free_all(params, "миша все хуйня давай по новой"));
	if (mutex_destroy(params))
		return (free_all(params, "Mutex destroy error!"));
	free_all(params, "im blue dabudeedabudaaaaaa");
	return (0);
}
