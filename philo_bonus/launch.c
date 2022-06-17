/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Farm Tonita <ftonita@student.21-school.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 07:49:30 by Farm Tonita       #+#    #+#             */
/*   Updated: 2022/06/17 13:49:53 by Farm Tonita      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	thread_create_detach(pthread_t *th, void *func, t_args *params)
{
	if (pthread_create(th, NULL, func, params))
		return (7);
	if (pthread_detach(*th))
		return (7);
	return (0);
}

static int	create_process(t_philo *philo, t_args *params, int id)
{
	pthread_t	stop_t;
	pthread_t	meals_t;

	if (params->eat_count && id == 0)
		if (thread_create_detach(&meals_t, &check_meals, params))
			return (7);
	if (thread_create_detach(&stop_t, &death_check, params))
		return (7);
	routine_philo(philo, params);
	return (0);
}

void	init_sem_name(int id, char *name)
{
	int		i;

	i = 4;
	name[i] = 'S';
	while (--i > 0)
	{
		name[i] = id % 10 + 48;
		id = id / 10;
	}
	name[i] = '/';
}

int	launch_all(t_philo *philo, t_args *params)
{
	int			id;

	params->t_started = get_time();
	philo->last_eat = params->t_started;
	id = -1;
	while (++id < params->number_of_philosophers)
	{
		philo->id = id + 1;
		params->pid[id] = fork();
		if (params->pid[id] == -1)
			return (kill_all_processes(params, id, 6));
		if (params->pid[id] == 0)
			if (create_process(philo, params, id))
				return (kill_all_processes(params, ++id, 7));
		usleep(50);
	}
	wait_exit_status(params, id);
	return (0);
}
