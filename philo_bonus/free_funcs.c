/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_funcs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Farm Tonita <ftonita@student.21-school.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 11:27:45 by Farm Tonita       #+#    #+#             */
/*   Updated: 2022/06/17 13:48:37 by Farm Tonita      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	free_null(void *ptr)
{
	if (ptr)
		free(ptr);
	ptr = NULL;
}

void	free_null_array(void **array, int size)
{
	int	i;

	i = -1;
	if (array)
		while (++i < size)
			free(array[i]);
	free(array);
	array = NULL;
}

static void	free_philo(t_args *params)
{
	int	id;

	id = -1;
	while (++id < params->number_of_philosophers)
		sem_close_unlink(params->philo->death[id], params->philo->name[id]);
	if (params->philo->name)
		free_null_array((void **)params->philo->name,
			params->number_of_philosophers + 1);
	if (params->philo->death)
		free_null(params->philo->death);
	free_null(params->philo);
}

int	free_exit(t_args *params)
{
	kill_all_processes(params, params->number_of_philosophers, 0);
	sem_post(params->print);
	sem_close_unlink(params->forks, FORKS);
	sem_close_unlink(params->print, PRINT);
	sem_close_unlink(params->fed_count, FED_COUNT);
	if (params->philo)
		free_philo(params);
	if (params->pid)
		free_null(params->pid);
	if (params)
		free_null(params);
	return (0);
}

int	free_all(t_args *params, char *err)
{
	free_exit(params);
	return (printf("\tStatus: [%s]\n", err));
}
