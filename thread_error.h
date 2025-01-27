#include <setjmp.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>



#define MAX_N_TASKS_IN_QUEUE 10

typedef struct {
    void (*function)(void*);
    void* argument;
}thread_task;

struct god_thread {
    void (*createThreads)(int n_threads);
    void (*addTask)(thread_task task);
    void (*destroyThreads)();
};
extern const struct god_thread ThreadGod;

//To implement: Inside the main function
struct god_error {
    void (*criticalErrorExit)(int error_code);
    int (*anchorCriticalErrorExitPoint)();
};





thread_task __thread_task_queue[MAX_N_TASKS_IN_QUEUE];



//Add inside main function
#define ANCHOR_ERROR_EXIT if(int __anchor_error_code = setjmp(__anchor_jump_buffer)) return __anchor_error_code;

void critical_error_exit(int error_code);

volatile jmp_buf __anchor_jump_buffer;







