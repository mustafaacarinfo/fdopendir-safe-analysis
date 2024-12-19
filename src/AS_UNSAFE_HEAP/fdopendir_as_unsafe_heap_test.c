#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <pthread.h>

/**
 * @def NUM_ITERATIONS
 * Number of iterations for the main directory handling loop.
 */
#define NUM_ITERATIONS 75

/**
 * @def NUM_THREADS
 * Number of threads used to send signals.
 */
#define NUM_THREADS 75

/**
 * @var stop_signal
 * @brief Flag to control the termination of signal-sending threads.
 */
volatile int stop_signal = 0;

/**
 * @brief Signal handler for SIGUSR1.
 *
 * Performs intensive heap allocations and deallocations when triggered.
 *
 * @param signum The signal number received.
 */
void signal_handler(int signum) {
    for (int i = 0; i < 5; i++) { // Perform intensive heap operations
        void *temp = malloc(1024); // Allocate a small block of memory
        if (temp) {
            free(temp); // Free the allocated memory
        }
    }
}

/**
 * @brief Signal-sending thread function.
 *
 * Continuously sends SIGUSR1 to the current process until `stop_signal` is set.
 *
 * @param arg Pointer to optional arguments (unused in this function).
 * @return NULL Always returns NULL.
 */
void *signal_sender(void *arg) {
    while (!stop_signal) {
        raise(SIGUSR1); // Trigger the signal
        usleep(10);     // Small delay to avoid overwhelming the process
    }
    return NULL;
}

/**
 * @brief Main function.
 *
 * Sets up the signal handler, spawns signal-sending threads, and tests
 * `fdopendir` under stress conditions.
 *
 * @return int Returns 0 upon successful completion.
 */
int main() {
    // Set up the signal handler
    signal(SIGUSR1, signal_handler);

    // Create signal-sending threads
    pthread_t threads[NUM_THREADS];
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_create(&threads[i], NULL, signal_sender, NULL);
    }

    // Main test loop
    for (int i = 0; i < NUM_ITERATIONS; i++) {
        int fd = open("/tmp", O_RDONLY | O_DIRECTORY); // Open the directory
        if (fd == -1) {
            perror("open failed");
            continue;
        }

        DIR *dir = fdopendir(fd); // Convert file descriptor to directory stream
        if (dir) {
            closedir(dir); // Close the directory stream
        } else {
            perror("fdopendir failed");
        }

        close(fd); // Close the file descriptor
    }

    // Stop signal-sending threads
    stop_signal = 1;
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    return 0;
}
