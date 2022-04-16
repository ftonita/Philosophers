#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef pthread_mutex_t t_mutex;

typedef	struct s_args
{
	int	number_of_philosophers;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	t_started;
	int	eat_count;
	int	fed_amount;
	int	last_msg;
	t_mutex	m_stop;
	t_mutex	m_print;
	t_mutex	*m_forks;
}	t_args;

typedef struct s_philo
{
	int		id;
	int		left_fork;
	int		right_fork;
	int		last_eat;
	int		t_wdead;
	int		eat_amount;
	t_mutex m_eat;
	t_args	*params;
}	t_philo;

int		ft_valid_args(char **argv, t_args *p);
void	ft_sleep(unsigned int	second);
int		ft_atoi(const char *str);

#endif