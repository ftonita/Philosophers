#include "philosophers.h"
void	*ft_philo_action(void *philo)
{
	t_philo *p = (void *)philo;
	printf("Philosopher #%d is active\n", p->id);
	return (NULL);
}

int		ft_launch_all(t_philo *philo, t_args *p)
{
	int	i;

	i = 0;
	while (i < p->number_of_philosophers)
	{
		pthread_create();
		
		write(1, "Launch\n", 7);
	}
	return (1);
}

t_philo	*ft_philo_init(t_philo *philo, t_args *p)
{
	int	i;

	philo = (t_philo *) malloc((p->number_of_philosophers)* sizeof(t_philo));
	if (philo == NULL)
		exit (0);
	i = 0;
	while (i < p->number_of_philosophers)
	{
		philo[i].id = i;
		philo[i].left_fork = i;
		philo[i].right_fork = (i + 1) % p->number_of_philosophers;
		philo[i].t_wdead = 0;
		philo[i].last_eat = 0;
		philo[i].params = p;
		philo[i].eat_amount = 0;
		pthread_mutex_init(&p->m_forks[i], 0);
		pthread_mutex_init(&philo[i].m_eat, 0);
		i++;
	}
	return (philo);
}

void	free_all(t_philo **philo, t_args *p)
{
	int	i;

	i = 0;
	while (i < p->number_of_philosophers)
	{
		free(philo[i]);
		i++;
	}
	free(philo);
	free (p);
}

int		ft_valid_args(char **argv, t_args *p)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		if ((ft_atoi(argv[i]) <= 0 && i < 5) || (ft_atoi(argv[i]) < 0 && i == 5))
		{
			return (1);
		}
		if (i == 5 && ft_atoi(argv[i]) == 0)
		{
			i++;
		}
		i++;
	}
	p->number_of_philosophers = ft_atoi(argv[1]);
	p->time_to_die = ft_atoi(argv[2]);
	p->time_to_eat = ft_atoi(argv[3]);
	p->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		p->eat_count = ft_atoi(argv[5]);
	else
		p->eat_count = -42;
	p->m_forks = (t_mutex *) malloc(sizeof(t_mutex) * p->number_of_philosophers);
	if (p->m_forks == NULL)
	{
		free(&p);
		return (1);
	}
	pthread_mutex_init(&p->m_print, 0);
	pthread_mutex_init(&p->m_stop, 0);
	pthread_mutex_lock(&p->m_stop);
	return (0);
}

int		main(int argc, char **argv)
{
	(void) argc;
	(void) argv;
	int 	e;
	int		i;
	t_args	*p;
	t_philo	*philo;

	if (argc < 5 || argc > 6)
		return (0);
	p = (t_args *) malloc(sizeof(t_args));
	if (p == NULL)
		return (0);
	e = ft_valid_args(argv, p);
	if (e != 0)
	{
		printf("args error\n");
		free(p);
	}
	else
	{
		printf("Number: \t %d\nTime to die: \t %d\nTime to eat: \t %d\nTime to sleep: \t %d\nEat count: \t %d\n", p->number_of_philosophers, p->time_to_die, p->time_to_eat, p->time_to_sleep, p->eat_count);
	}
	philo = ft_philo_init(philo, p);
	//free_all(philo, p);
	while (1)
		;
	return 0;
}