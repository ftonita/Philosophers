#include "philosophers.h"

int main(void)
{
	pthread_mutex_t *a;
	// pthread_mutex_t *b; 
	// a = NULL;
	// b = NULL;
	// a = b;
	a = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(a, NULL);
	return 0;
}