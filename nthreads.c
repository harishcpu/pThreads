/* 
 * Filename:    nthreads.c
 * Description: This file contains the code for creating N number of detachable threads.
 * Author:      Harish Kumar(github: harishkumar101)
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <errno.h>

void*
thread_fn_cb(void *arg) {
    
    int thread_num = *(int *)arg;
    free(arg);
    
    printf("%d\n", thread_num);
    
    return NULL;
}

int
main(int argc, char **argv) {
    
    int num;
    int *thread_input;
    
	/* read the input from command line */
    if(argc <= 1) {
        printf("Usage: ./<binary-file-name> <value of N>\n");
        printf("Example: ./nthreads 5\n");
        exit(1);
    }
    
    num = atoi(argv[1]);
    printf("Entered Number: %d\n", num);

    pthread_t pthread[num];
    pthread_attr_t attr;
    
	/* set attributes for detachable threads */
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr,
                    PTHREAD_CREATE_DETACHED);
    
    for(int i = 0; i < num; i++) {
        
        thread_input = calloc(1, sizeof(int));
        
        *thread_input = num - i;
        
		/* create detachable thread */
        pthread_create(&pthread[i],
                        &attr,
                        &thread_fn_cb,
                        (void *)thread_input);
    }
    pthread_exit(0);
}
