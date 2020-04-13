#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <pthread.h>
#include <semaphore.h>
#include <fcntl.h>

sem_t * sem;

int main(void) {

	while(1){
		int nThreads;
		printf("PID: %d I'm a waker.\n", getpid());
		printf("How many threads do you want to wake up (enter 0 to exit)?:\n");
		scanf("%d",&nThreads);
		if (nThreads==0){
			return EXIT_SUCCESS;
		}

		sem = sem_open("/Lab4_Sem", 0);
		for(int i = 0; i < nThreads; i++ ){
			sem_post(sem);
		}
	}

	return EXIT_SUCCESS;
}

