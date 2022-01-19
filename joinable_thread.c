#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <errno.h>

pthread_t pthread2;
pthread_t pthread3;

void* 
thread_fn_callback(void *arg) {
	
	int th_id = *(int *)arg;
	free(arg);
	
	/* sleep for sometime*/
	int rc = 0;
	while(rc != th_id) {
		printf("Thread %d is doing some work\n", th_id);
		sleep(1);
		rc++;
	}
	
	/* compute square and return result */
	int *result = calloc(1, sizeof(int));
	*result = th_id * th_id;

	return (void *)result;
}

void 
thread_create(pthread_t *pthread_handle, int th_id){
	
	pthread_attr_t attr;

	int *_th_id = calloc(1, sizeof(th_id));
	*_th_id = th_id;

	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, 
					PTHREAD_CREATE_JOINABLE
					/* PTHREAD_CREATE_DETACHED */);
	
	pthread_create(pthread_handle,
					&attr,
					thread_fn_callback,
					(void *)_th_id);
}

int
main(int argc, char **argv) {
	
	void *thread_result2;
	void *thread_result3;

	thread_create(&pthread2, 10);
	thread_create(&pthread3, 2);

	printf("main fn blocked at pthread_join for thread with"
					"th_id = 2\n");
	pthread_join(pthread2, &thread_result2);
	
	if(thread_result2 != NULL){
		printf("Result returned from thread 2 = %d\n",
					*(int *)thread_result2);
		free(thread_result2);
		thread_result2 = NULL;
	}

	printf("main fn blocked at pthread_join for thread with"
					"th_id = 10\n");
	pthread_join(pthread3, &thread_result3);
	
	if(thread_result3 != NULL){
		printf("Result returned from thread 3 = %d\n",
					*(int *)thread_result3);
		free(thread_result3);
		thread_result3 = NULL;
	}


	return 0;
}
