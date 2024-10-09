
#include "incl/malloc.h"
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

// Number of threads and iterations per thread
#define NUM_THREADS 10
#define NUM_ITERATIONS 100

// Structure to hold thread data
typedef struct {
    int thread_id;
} thread_data_t;

// Function to be executed by each thread
void* thread_function(void* arg) 
{
    thread_data_t* data = (thread_data_t*)arg;
    for (int i = 0; i < NUM_ITERATIONS; i++) 
    {
        // Allocate memory
        int* arr = malloc(10 * sizeof(int));
        if (arr == NULL) 
        {
            write(1, "Error Malloc\n", 13);
            return (NULL);
        }

        for (int j = 0; j < 10; j++)
            arr[j] = data->thread_id * 10 + j; // Just filling with some values
                                               //
        arr = realloc(arr, 20 * sizeof(int));
        if (arr == NULL) 
        {
            write(1, "Error Realloc\n", 14);
            free(arr);
            continue ;
        }
        show_alloc_mem();
        free(arr);
    }
    return (NULL);
}

int main() {
    pthread_t threads[NUM_THREADS];
    thread_data_t thread_data[NUM_THREADS];

    for (int i = 0; i < NUM_THREADS; i++) 
    {
        thread_data[i].thread_id = i;
        if (pthread_create(&threads[i], NULL, thread_function, (void*)&thread_data[i])) 
            return (1);
    }
    for (int i = 0; i < NUM_THREADS; i++)
        pthread_join(threads[i], NULL);

    printf("here\n");
    return (0);
}
