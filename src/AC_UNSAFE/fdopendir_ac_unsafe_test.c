#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <fcntl.h>
#include <dirent.h>
#include <unistd.h>
#include <string.h>

#define NUM_THREADS 100  /**< Number of threads to create */
#define NUM_ITERATIONS 10  /**< Number of iterations per thread */

/**
 * @brief Worker function executed by each thread.
 *
 * This function opens a directory file descriptor, converts it to a DIR 
 * stream using fdopendir, performs a small delay, and then closes the DIR 
 * stream and file descriptor. This operation is repeated for a fixed number 
 * of iterations.
 *
 * @param arg Unused parameter for thread function.
 * @return Always returns NULL.
 */
void *worker_function(void *arg) {
    for (int i = 0; i < NUM_ITERATIONS; i++) {
        // Open the directory with a file descriptor
        int fd = open("/tmp", O_RDONLY | O_DIRECTORY);
        if (fd == -1) {
            return NULL; // Exit the function if open fails
        }

        // Convert the file descriptor into a DIR stream
        DIR *dir = fdopendir(fd);
        if (dir) {
            usleep(rand() % 100); // Add a small random delay
            closedir(dir);        // Close the DIR stream
        }
        close(fd);                // Close the file descriptor
    }
    return NULL;
}

/**
 * @brief Main function to create and manage threads.
 *
 * This function creates multiple threads that execute the worker_function.
 * It also attempts to cancel threads shortly after their creation.
 * Finally, it joins all threads and ensures they complete before the program exits.
 *
 * @return Returns 0 on successful execution.
 */
int main() {

    pthread_t threads[NUM_THREADS]; // Array to hold thread IDs

    // Create threads and cancel them shortly after creation
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_create(&threads[i], NULL, worker_function, NULL); // Create a thread
        usleep(100);  // Add a small delay before attempting to cancel
        pthread_cancel(threads[i]); // Cancel the thread
    }

    // Join all threads to ensure proper cleanup
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL); // Wait for thread completion
    }

    printf("All threads have been joined.\n");

    return 0;
}