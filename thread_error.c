#include "thread_error.h"

void critical_error_exit(int error_code) {

}





#define THREAD_QUEUE_SIZE 10

typedef struct {
    void (*function)(void*); // Function pointer for tasks
    void* argument;          // Arguments for the task
} Task;

// Task queue
thread_task taskQueue[THREAD_QUEUE_SIZE];
int queueStart = 0, queueEnd = 0, queueCount = 0;

// Synchronization
pthread_mutex_t queueMutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t queueNotEmpty = PTHREAD_COND_INITIALIZER;

// Function to add a task to the queue
void addTask(void (*function)(void*), void* argument) {
    pthread_mutex_lock(&queueMutex);
    if (queueCount == THREAD_QUEUE_SIZE) {
        usleep(100000);
    } else {
        taskQueue[queueEnd].function = function;
        taskQueue[queueEnd].argument = argument;
        queueEnd = (queueEnd + 1) % THREAD_QUEUE_SIZE;
        queueCount++;
        pthread_cond_signal(&queueNotEmpty); // Notify a thread
    }
    pthread_mutex_unlock(&queueMutex);
}

// Worker thread function
void* threadFunction(void* arg) {
    char exit_thread = 1;
    while (exit_thread) {
        thread_task task;
        pthread_mutex_lock(&queueMutex);

        // Wait for a task
        while (queueCount == 0) {
            pthread_cond_wait(&queueNotEmpty, &queueMutex);
        }

        // Get the next task
        task = taskQueue[queueStart];
        queueStart = (queueStart + 1) % THREAD_QUEUE_SIZE;
        queueCount--;

        pthread_mutex_unlock(&queueMutex);

        // Execute the task
        task.function(task.argument);
    }
    return NULL;
}

// Example task function
void exampleTask(void* arg) {
    int* num = (int*)arg;
    printf("Processing task: %d\n", *num);
    sleep(1); // Simulate work
    free(num); // Free allocated memory
}

