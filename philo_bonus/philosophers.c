/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Farm Tonita <ftonita@student.21-school.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 11:25:12 by Farm Tonita       #+#    #+#             */
/*   Updated: 2022/06/17 13:49:58 by Farm Tonita      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

char	*get_status(int status)
{
	if (status == 0)
		return ("is \x1b[36mthinking\x1b[0m");
	else if (status == 1)
		return ("has \x1b[33mtaken a fork (I)\x1b[0m");
	else if (status == 2)
		return ("has \x1b[33mtaken a fork (II)\x1b[0m");
	else if (status == 3)
		return ("is \x1b[32meating\x1b[0m");
	else if (status == 4)
		return ("is \x1b[34msleeping\x1b[0m");
	return (NULL);
}

void	print_log(t_philo *philo, t_args *params, int status)
{
	sem_wait(params->print);
	printf("[%7lld] philo %d %5s\n",
		get_time() - params->t_started, philo->id, get_status(status));
	sem_post(params->print);
}

int	ft_atoi(const char *str)
{
	int			i;
	long int	n;

	i = 0;
	n = 0;
	if (str[i] < '0' || str[i] > '9')
		return (-1);
	while (str[i] >= '0' && str[i] <= '9')
	{
		n = n * 10 + ((long int)str[i] - 48);
		if ((str[i + 1] < '0' || str[i + 1] > '9') && str[i + 1])
			return (-1);
		i++;
	}
	return (n);
}

int	main(int argc, char **argv)
{
	t_args	*params;

	if (argc != 5 && argc != 6)
		return (printf("ARGS count must be ONLY 4 or 5"));
	params = (t_args *)malloc(sizeof(t_args));
	if (!params)
		return (printf("Params Malloc() error"));
	if (ft_valid_args(argv, params))
		return (free_all(params, "Invalid ARGS"));
	if (ft_philo_init(params))
		return (free_all(params, "Philos init failed"));
	if (arrays_malloc(params->philo, params))
		return (free_all(params, "Philos init failed"));
	if (semaphore_init(params->philo, params))
		return (free_all(params, "sem init failed"));
	if (launch_all(params->philo, params))
		return (free_all(params, "debil slomal vse"));
	return (free_exit(params));
}
