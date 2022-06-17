/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Farm Tonita <ftonita@student.21-school.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 05:04:52 by Farm Tonita       #+#    #+#             */
/*   Updated: 2022/06/17 05:25:08 by Farm Tonita      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	global_mutex_malloc(t_args *p)
{
	t_fork	*fork;
	t_print	*mut;
	t_stop	*stp;
	t_meals	*meals_mut;

	mut = (t_print *) malloc(sizeof(t_print));
	stp = (t_stop *) malloc(sizeof(t_stop));
	meals_mut = (t_meals *)malloc(sizeof(t_meals));
	if (!meals_mut || !mut || !stp)
		return (free_all(p, "print/stop/meals mutex malloc error!"));
	p->print = mut;
	p->stop = stp;
	p->meals_mut = meals_mut;
	fork = (t_fork *) malloc(sizeof(t_fork));
	if (!fork)
		return (free_all(p, "Forks[] malloc error!"));
	fork->m_forks = (t_mutex *) malloc
		(sizeof(t_mutex) * p->number_of_philosophers);
	if (!fork->m_forks)
		return (free_all(p, "Forks malloc error!"));
	p->forks = fork;
	return (global_mutex_init(p));
}

int	ft_valid_args(char **argv, t_args *p)
{
	int	i;

	i = 0;
	while (argv[++i])
	{
		if ((ft_atoi(argv[i]) <= 0 && i < 5)
			|| (ft_atoi(argv[i]) < 0 && i == 5))
			return (1);
		if (i == 5 && ft_atoi(argv[i]) == 0)
			i++;
	}
	p->number_of_philosophers = ft_atoi(argv[1]);
	p->time_to_die = ft_atoi(argv[2]);
	p->time_to_eat = ft_atoi(argv[3]);
	p->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		p->eat_count = ft_atoi(argv[5]);
	else
		p->eat_count = 0;
	p->fed_count = 0;
	p->philo_exit = 0;
	return (0);
}

int	ft_philo_init(t_args *p)
{
	int	i;

	p->philo = (t_philo *) malloc
		((p->number_of_philosophers) * sizeof(t_philo));
	if (p->philo == NULL)
		return (printf("\tStatus: [Philo[] malloc error!]\n"));
	i = 0;
	p->t_started = get_time();
	while (i < p->number_of_philosophers)
	{
		p->philo[i].t_started = p->t_started;
		p->philo[i].params = p;
		p->philo[i].id = i + 1;
		p->philo[i].right_fork = i;
		p->philo[i].left_fork = i + 1;
		if (i == p->number_of_philosophers - 1)
			p->philo[i].left_fork = 0;
		p->philo[i].last_eat = 0;
		p->philo[i].l_time = p->time_to_die;
		p->philo[i].fed_amount = 0;
		p->philo[i].print = p->print;
		p->philo[i].meals_mut = p->meals_mut;
		i++;
	}
	return (global_mutex_malloc(p));
}

int	global_mutex_init(t_args *p)
{
	int	i;

	if (pthread_mutex_init(&p->print->m_print, NULL))
		return (free_all(p, "Print mutex init error!"));
	if (pthread_mutex_init(&p->stop->stop, NULL))
		return (free_all(p, "Stop mutex init error!"));
	p->thread = (pthread_t *) malloc(sizeof(pthread_t)
			* p->number_of_philosophers);
	if (!p->thread)
		return (free_all(p, "Thread[] malloc error!"));
	if (pthread_mutex_init(&p->meals_mut->mut, NULL))
		return (free_all(p, "Meals mutex init error!"));
	i = -1;
	while (++i < p->number_of_philosophers)
	{
		p->philo[i].forks = p->forks;
		p->philo[i].meals_mut = p->meals_mut;
		if (pthread_mutex_init(&p->forks->m_forks[p
					->philo[i].right_fork], NULL))
			return (free_all(p, "Forks mutexes' init error!"));
		if (pthread_mutex_init(&p->philo[i].m_death, NULL))
			return (free_all(p, "Death mutexes' init error!"));
	}
	return (0);
}
