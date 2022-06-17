/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Farm Tonita <ftonita@student.21-school.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 06:41:23 by Farm Tonita       #+#    #+#             */
/*   Updated: 2022/06/17 13:47:23 by Farm Tonita      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long long	get_time(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

void	ft_sleep(long long m_secs)
{
	long long	stop;

	stop = get_time() + m_secs;
	while (get_time() < stop)
		usleep(250);
}

void	wait_exit_status(t_args *params, int id)
{
	int	status;

	while (waitpid(-1, &status, 0) > 0)
		if (WEXITSTATUS(status) == 1)
			kill_all_processes(params, id, 0);
}

int	kill_all_processes(t_args *params, int id, int value)
{
	while (--id >= 0)
	{
		if (params->pid[id])
		{
			kill(params->pid[id], SIGKILL);
			params->pid[id] = 0;
		}
	}
	return (value);
}

void	sem_close_unlink(sem_t *sem, char *name)
{
	if (sem)
	{
		sem_unlink(name);
		sem_close(sem);
		sem = NULL;
	}
}
