#include "philosophers.h"

int		ft_checker(t_philo **philo, t_args *p)
{
	int i = 0;
	while (i < p->number_of_philosophers)
	{
		if (i % 2)
		{
			printf("\tphilo: %d sleeping\n", i + 1);
		}
		else
		{
			printf("\tphilo: %d eating\n", i + 1);
		}
		i++;
	}
	return (0);
}

void	*ft_philo_action(void *philo)
{
	t_philo *p = (void *)philo;
	printf("Philosopher #%d is active\n", p->id);
	//ft_check(*p);
	return (NULL);
}

t_philo	**ft_philo_init(t_philo **philo, t_args *p)
{
	int	i;
	int	status;

	printf("ft_philo_init\n");
	i = 0;
	while (i < p->number_of_philosophers)
	{
		printf("\tphilo: %d\n", i + 1);
		if (i == 0)
			philo[i]->right_fork = philo[p->number_of_philosophers - 1];
		else
			philo[i]->right_fork = philo[i - 1];
		if (i == p->number_of_philosophers - 1)
			philo[i]->left_fork = philo[0];
		else
			philo[i]->left_fork = philo[i + 1];
		philo[i]->id = i + 1;
		philo[i]->eating = 0;
		philo[i]->sleeping = 0;
		philo[i]->thinking = 0;
		status = pthread_create(&philo[i]->thread, NULL, ft_philo_action, philo[i]);
		if (status != 0)
		{
			printf("main error: can't create thread, status = %d\n", status);
			return (NULL);
		}
		pthread_join(philo[i]->thread, NULL);
		printf("\tphilo: %d - success started\n", i + 1);
		i++;
	}
	while (!ft_checker(philo, p))
		ft_sleep(1);
	printf("ft_philo_init end\n");
	return (philo);
}

t_philo	**ft_philo_malloc(t_philo **philo, t_args *p)
{
	int	i;

	philo = (t_philo **) malloc((p->number_of_philosophers + 1)* sizeof(*philo));
	if (philo == NULL)
		exit (0);
	philo[p->number_of_philosophers] = NULL;
	i = 0;
	while (i < p->number_of_philosophers)
	{
		philo[i] = (t_philo *) malloc (sizeof(t_philo));
		if (philo[i] == NULL)
		{
			i--;
			while (i >= 0)
			{
				free(philo[i]);
				i--;
			}
			free(philo);
			exit (0);
		}
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
	return (0);
}

int		main(int argc, char **argv)
{
	(void) argc;
	(void) argv;
	int 	e;
	int		i;
	t_args	*p;
	t_philo	**philo;

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
	philo = ft_philo_malloc(philo, p);
	philo = ft_philo_init(philo, p);
	//free_all(philo, p);
	while (1)
		;
	return 0;
}