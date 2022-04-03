#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef	struct s_args
{
	int	number_of_philosophers;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	eat_count;
}	t_args;

typedef struct s_philo
{
	int				eating;
	int				sleeping;
	int				thinking;
	pthread_t		thread;
	struct s_philo *left_fork;
	struct s_philo *right_fork;
	int				id;
}	t_philo;

int		ft_valid_args(char **argv, t_args *p);
void	ft_sleep(unsigned int	second);
int		ft_atoi(const char *str);

#endif