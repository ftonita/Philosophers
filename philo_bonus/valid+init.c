/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid+init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Farm Tonita <ftonita@student.21-school.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 06:36:15 by Farm Tonita       #+#    #+#             */
/*   Updated: 2022/06/17 13:47:09 by Farm Tonita      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

sem_t	*ft_sem_open(char *name, int oflag, mode_t mode, int value)
{
	sem_t	*sem;

	sem_unlink(name);
	sem = sem_open(name, oflag, mode, value);
	return (sem);
}

int	semaphore_init(t_philo *philo, t_args *params)
{
	int	id;

	params->forks = ft_sem_open
		(FORKS, O_CREAT, 0644, params->number_of_philosophers);
	if (params->forks == SEM_FAILED)
		return (1);
	params->print = ft_sem_open(PRINT, O_CREAT, 0644, 1);
	if (params->print == SEM_FAILED)
		return (1);
	params->fed_count
		= ft_sem_open(FED_COUNT, O_CREAT, 0644, 1);
	if (params->fed_count == SEM_FAILED)
		return (1);
	id = params->number_of_philosophers;
	while (--id >= 0)
	{
		philo->death[id] = ft_sem_open(philo->name[id], O_CREAT, 0644, 1);
		if (philo->death[id] == SEM_FAILED)
			return (1);
	}
	return (0);
}

int	arrays_malloc(t_philo *philo, t_args *params)
{
	int	id;
	int	num;

	id = 0;
	num = params->number_of_philosophers;
	params->pid = (pid_t *) malloc(sizeof(pid_t) * num);
	if (!params->pid)
		return (1);
	while (id < params->number_of_philosophers)
		params->pid[id++] = 0;
	philo->name = (char **) malloc(sizeof(char *) * num + 1);
	if (!philo->name)
		return (1);
	while (id >= 0)
		philo->name[id--] = NULL;
	while (++id < params->number_of_philosophers)
	{
		philo->name[id] = (char *)malloc(sizeof(char) * 5);
		if (!philo->name[id])
			return (1);
	}
	philo->death = (sem_t **) malloc(sizeof(sem_t *) * num);
	if (!philo->death)
		return (1);
	return (0);
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
	return (0);
}

int	ft_philo_init(t_args *params)
{
	params->philo = (t_philo *)malloc(sizeof(t_philo));
	if (!params->philo)
		return (1);
	params->philo->id = 0;
	params->philo->fed_amount = 0;
	params->philo->l_time = params->time_to_die;
	params->philo->last_eat = 0;
	params->philo->name = NULL;
	params->philo->death = NULL;
	return (0);
}
