#include <stdio.h>
#include <stdlib.h>
#include <pthread.h> /* For working with POSIX threads */
#include <unistd.h> /* For pause() and sleep() */

#define MAX_THREADS 4
#define MAX 16

int arr[] = {1,2,3,4,5,6,7,8,9,10};
int sum[MAX_THREADS] = {0};
int part = 0;

void *calculate_sum() {
	int thread_part = part++;
	
	for(int i = thread_part * (MAX/2); i < (thread_part + 1) * (MAX/2); i++) {
		sum[thread_part] += arr[i];
	}
}

int main(void) {
	pthread_t thread[MAX_THREADS];
	int total_sum = 0;

	//creating 2 threads
	for(int i = 0; i < MAX_THREADS; i++) {
		int rc = pthread_create(&thread[i], NULL, &calculate_sum, NULL);
		if(rc != 0) {
			printf("Failed to create threads.\n");
			exit(0);
		}
	}
	
	// joining threads i.e., waiting for all threads to complete
	for(int i = 0; i < MAX_THREADS; i++) {
		int rc = pthread_join(thread[i], NULL);
		if(rc != 0) {
			printf("Failed to join threads.\n");
			exit(0);
		}
	}
	
	for(int i = 0; i < MAX_THREADS; i++) {
		total_sum += sum[i];
	}
	
	printf("total sum: %d\n", total_sum);

	return 0;
}
