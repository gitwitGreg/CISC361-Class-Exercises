#include <iostream>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <pthread.h>

#define MAX_NO_OF_ELEMENTS 100000000
static long long int sum;
static int arr[MAX_NO_OF_ELEMENTS];
int current_thread_sum;
int endpart = arr[arr[MAX_NO_OF_ELEMENTS]];
int startpart = arr[0];
#define MAX_NO_OF_THREADS 2



typedef struct arg_data{
    int thread_number;
} arg_data;


void* thread_function(void* arg){
    arg_data arg_arr[MAX_NO_OF_THREADS];
    clock_t start, end;
    double cpu_time_taken;
    int thread_no = 1;
    arg_data *current_thread_data = (arg_data*)arg;
    start = clock();
    for (int i = 0; i < MAX_NO_OF_ELEMENTS; i++){
        arr[i] = i + 1;
    }
    end = clock();
    cpu_time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("All child threads has finished their works...\n");
    printf("Total sum: %lld\n", sum);
    printf("Time taken to sum all the numbers are %lf\n", cpu_time_taken);
    pthread_exit(NULL);
}

int main(){
    pid_t pid, grandpid;
    pid_t parent_pid = getpid();
    pid = fork();
    pid_t child_Pid = getpid();
    if (pid == 0) {
        grandpid = fork();
        
        if (grandpid == 0) {
            printf("I am the grandchild process %d\n", getpid());
            printf("I am the child process %d\n", child_Pid);
            printf("I am the parent %d\n", parent_pid);
        }
    }
    int no_of_threads = MAX_NO_OF_THREADS;
    printf("Creating %d number of threads...\n", no_of_threads);
    pthread_t tid;
    pthread_create(&tid, NULL, thread_function,NULL);
    pthread_join(tid,NULL);
    return 0;
}



void* worker_sum(void* arg){
    arg_data* current_thread_data = (arg_data*)arg;
    printf("Current thread no is : %d\n", current_thread_data->thread_number);
    printf("Here we will sum %d to %d\n", arr[startpart], arr[endpart - 1]);
    sum += current_thread_sum;
    return NULL;
}

