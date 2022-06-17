/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Farm Tonita <ftonita@student.21-school.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 04:46:58 by Farm Tonita       #+#    #+#             */
/*   Updated: 2022/06/17 05:20:37 by Farm Tonita      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef pthread_mutex_t	t_mutex;

typedef union s_fork
{
	t_mutex		*m_forks;
}	t_fork;

typedef union s_print
{
	t_mutex		m_print;
}	t_print;

typedef union s_stop
{
	t_mutex	stop;
}	t_stop;

typedef union s_meals
{
	pthread_mutex_t	mut;
}	t_meals;

typedef struct s_args
{
	int				number_of_philosophers;
	size_t			time_to_die;
	int				time_to_eat;
	size_t			time_to_sleep;
	size_t			t_started;
	int				eat_count;
	int				fed_count;
	t_fork			*forks;
	t_print			*print;
	pthread_t		*thread;
	struct s_philo	*philo;
	t_stop			*stop;
	int				philo_exit;
	t_meals			*meals_mut;
}	t_args;

typedef struct s_philo
{
	int		id;
	int		left_fork;
	int		right_fork;
	int		fed_amount;
	size_t	last_eat;
	t_args	*params;
	t_fork	*forks;
	t_print	*print;
	size_t	t_started;
	size_t	l_time;
	t_mutex	m_death;
	t_meals	*meals_mut;
}	t_philo;

int		ft_valid_args(char **argv, t_args *p);
int		ft_philo_init(t_args *p);
int		global_mutex_init(t_args *p);
int		global_mutex_malloc(t_args *p);

int		ft_sleep(size_t m_secs, t_philo *philo);
int		ft_atoi(const char *str);
size_t	get_time(void);
int		free_all(t_args *params, char *err);
int		mutex_destroy(t_args *params);

void	*routine_philo(void *tmp);

int		print_log(t_philo	*philo, int status);

int		right_fork_unlock(t_philo *philo);
int		all_forks_unlock(t_philo *philo);

#endif