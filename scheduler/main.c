#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <time.h>
#include <unistd.h>


#define MAX_TASKS 10

typedef struct {
    const char *name;
    uint32_t period_ms;
    uint32_t max_runs;
    uint64_t last_run_ms;
    uint32_t run_count;
    void (*func)(void);
} task_t;

static task_t tasks[MAX_TASKS];
static int task_count = 0;


uint64_t get_time_ms(void) {
    struct timespec time;
    clock_gettime(CLOCK_MONOTONIC, &time );
    printf( "%d\n", (time.tv_nsec/1000));
    return 0;
}

void task_register(const char *name, uint32_t period_ms, uint32_t max_runs, void (*func)(void)) {
    // TODO
    // register a task
    // !!! Check max tasks

    if (task_count == MAX_TASKS)
    {
        printf("ERROR: TASKS QUEUE FULL\n");
    }
    else
    {
        task_t newtask = {name, period_ms, max_runs};
        newtask.func = func;
        tasks[task_count] = newtask;
        task_count++;
        printf("SUCCESS: TASK %s ADDED \n", newtask.name);
    }
    return;

}

void task_1_handler(void) {
    printf("-> Task 1 logic executed\n");
}

void task_2_handler(void) {
    printf("-> Task 2 logic executed\n");
}

int main(void) {
    task_register("SensorTask", 100, 12, task_1_handler); // Runs 12 times
    task_register("LoggerTask", 500, 2, task_2_handler); // Runs 2 time
    printf("Number of task: %d \n", task_count);

    while (true) {
        for (int i = 0; i < task_count; i++)
        {
            for (int j = 0; j < tasks[i].max_runs; j++)
            {
                tasks[i].func;
            }
        }
        task_count = 0;
    }

    return 0;
}
