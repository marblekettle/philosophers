#include <unistd.h>
#include <pthread.h>
#include <stdio.h>

void	*thred(void *a)
{
	while (1)
	{
		printf("a");
		usleep(100000);
	}
}

int	main(void)
{
	pthread_t	thr;

	printf("Go!");
	pthread_create(&thr, NULL, thred, NULL);
	usleep(1000000);
	pthread_detach(thr);
	printf("Time's up!");
	return (0);
}