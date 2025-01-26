# ThreadErrorGods
Gods to simplify thread creation and error handling in c

Structs as simple as possible that function as c++ classes methods. Almost no runtime overhead, other than mutexes. The purpose is to have similar error handling capabilities as c++ in c.

The philosophy of the threads is to create them as the program starts and have a queue with tasks for the threads to perform.

A thread_task is a struct with a function pointer of the form 
```c
void (*function_pointer)(void*)
```
 and a void pointer to potentially hold lead to the argument(s) of the function.

