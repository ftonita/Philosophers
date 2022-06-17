/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Farm Tonita <ftonita@student.21-school.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 11:25:19 by Farm Tonita       #+#    #+#             */
/*   Updated: 2022/06/17 13:54:30 by Farm Tonita      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <semaphore.h>
# include <signal.h>
# include <sys/wait.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define FORKS "/forks"
# define PRINT "/print"
# define FED_COUNT "/fed_count"

typedef struct s_philo
{
	int			id;
	int			fed_amount;
	long long	l_time;
	long long	last_eat;
	char		**name;
	sem_t		**death;
}	t_philo;

typedef struct s_args
{
	int			number_of_philosophers;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			eat_count;
	long long	t_started;
	sem_t		*forks;
	sem_t		*print;
	sem_t		*fed_count;
	pid_t		*pid;
	t_philo		*philo;
}	t_args;

int			free_all(t_args *params, char *err);
void		free_null(void *ptr);
void		free_null_array(void **array, int size);
int			free_exit(t_args *params);

int			ft_valid_args(char **argv, t_args *p);
int			arrays_malloc(t_philo *philo, t_args *params);
int			ft_philo_init(t_args *params);
int			semaphore_init(t_philo *philo, t_args *params);

int			launch_all(t_philo *philo, t_args *params);
void		routine_philo(t_philo *philo, t_args *params);

void		*check_meals(void *ptr);
void		*death_check(void *ptr);
void		philo_died(t_philo *philo, t_args *params);

void		init_sem_name(int id, char *name);
sem_t		*ft_sem_open(char *name, int oflag, mode_t mode, int value);
void		sem_close_unlink(sem_t *sem, char *name);
void		wait_exit_status(t_args *params, int id);
int			kill_all_processes(t_args *params, int id, int value);

long long	get_time(void);
void		ft_sleep(long long m_secs);
void		print_log(t_philo *philo, t_args *params, int status);
int			ft_atoi(const char *str);
#endif