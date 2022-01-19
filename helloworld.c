#include <stdio.h>
#include <stdlib.h>
#include <pthread.h> /* For working with POSIX threads */
#include <unistd.h> /* For pause() and sleep() */

static void *
thread_fn_callback(void *arg) {
	char *input = (char *)arg;
	
	int a = 0;
	while(a < 10) {
		printf("input string = %s\n", input);
		sleep(1);
		if(a ==5)	pthread_exit(0);
		a++;
	}
}

void
thread1_create() {
	
	/* declare the thread handle */
	pthread_t pthread1;

	/* input to the thread, allocated in persistent(heap) memory 
	 * input to the thread must be allocated in head, or it should be static */
	static char *thread_input1 = "I am thread no 1";

	/* pthread_create returns 0 on success, otherwise a negative value
	 *  to indicate error/failure */
	int rc = pthread_create(&pthread1, 
					NULL,
					thread_fn_callback,
					(void *)thread_input1);
	if(rc != 0) {
		printf("Error occurred, thread could not be created, errno = %d\n", rc);
		exit(0);
	}
}

int main(int argc, char **argv) {
	
	thread1_create();
	printf("main function paused\n");
	//pause();
	
	/* pthread_exit() allows the main thread to return without 
	   killing the child threads */
	pthread_exit(0);
	return 0;
}
