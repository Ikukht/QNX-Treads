#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <pthread.h>
#include <semaphore.h>
#include <fcntl.h>


void handler();
void* childThread(void *arg);

sig_atomic_t signalReceived=0;
sem_t* sem;

int main(void) {

	int nThreads;

	struct sigaction sa;
	sa.sa_handler=handler;
	sa.sa_flags=0;
	sigemptyset(&sa.sa_mask);

	pthread_attr_t attr;

	if (sigaction(SIGUSR1, &sa, NULL) == -1) {
		perror("sigaction");
		exit(1);
	}

	printf("Enter number of threads:\n");
	scanf("%d", &nThreads);

	sem = sem_open("/Lab4_Sem", O_CREAT, S_IWOTH, 0);

	for (int i = 0; i < nThreads; i++){
		pthread_attr_init(&attr);
		if ( pthread_create(NULL, &attr, &childThread, NULL) != EOK){
			perror("Error creating thread");
		}
		pthread_attr_destroy(&attr);
	}

	while(signalReceived==0){}
	sem_close(sem);

	return EXIT_SUCCESS;
}

void handler(){
	signalReceived=1;
}

void* childThread(void *arg){
	printf("Thread created: %d\n", pthread_self());
	while(1){
		sem_wait(sem);
		printf("Thread unblocked: %d\n", pthread_self());
		sleep(5);
	}
	return(NULL);
}
