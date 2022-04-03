#include "philosophers.h"

void	ft_sleep(unsigned int ms)
{
	while (ms)
	{
		usleep(1000);
		ms--;
	}
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