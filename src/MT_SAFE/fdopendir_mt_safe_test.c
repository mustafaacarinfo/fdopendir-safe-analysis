#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <fcntl.h>
#include <dirent.h>
#include <unistd.h>

/**
 * @def NUM_THREADS
 * Number of threads to spawn for testing.
 */
#define NUM_THREADS 40

/**
 * @def NUM_ITERATIONS
 * Number of iterations each thread performs.
 */
#define NUM_ITERATIONS 40

/**
 * @brief Worker function for each thread.
 *
 * Each thread repeatedly opens the `/tmp` directory, converts the file descriptor
 * to a directory stream using `fdopendir`, and closes both the stream and file descriptor.
 *
 * @param arg Pointer to optional arguments (unused in this function).
 * @return NULL Always returns NULL.
 */
void *worker_function(void *arg) {
    for (int i = 0; i < NUM_ITERATIONS; i++) {
        int fd = open("/tmp", O_RDONLY | O_DIRECTORY);
        if (fd == -1) {
            perror("open failed");
            continue;
        }

        DIR *dir = fdopendir(fd);
        if (dir) {
            closedir(dir);
        } else {
            perror("fdopendir failed");
        }

        close(fd);
    }
    return NULL;
}


/**
 * @brief Main function.
 *
 * Spawns multiple threads to test the `fdopendir` function.
 * Each thread performs the test defined in `worker_function`.
 *
 * @return int Returns 0 upon successful completion.
 */
int main() {
    pthread_t threads[NUM_THREADS];

    // Create threads
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_create(&threads[i], NULL, worker_function, NULL);
    }

    // Wait for all threads to complete
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("All threads have completed.\n");
    return 0;
}
