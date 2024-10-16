#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define NUM_PHILOSOPHERS 5

pthread_mutex_t forks[NUM_PHILOSOPHERS];
pthread_t philosophers[NUM_PHILOSOPHERS];

void* philosopher(void* num) {
    int id = *(int*)num;
    int leftFork = id;
    int rightFork = (id + 1) % NUM_PHILOSOPHERS;

    while (1) {
        printf("Philosopher %d is thinking.\n", id);
        sleep(1);

        // Pick up left fork
        pthread_mutex_lock(&forks[leftFork]);
        printf("Philosopher %d picked up left fork %d.\n", id, leftFork);

        // Pick up right fork
        pthread_mutex_lock(&forks[rightFork]);
        printf("Philosopher %d picked up right fork %d.\n", id, rightFork);

        // Eating
        printf("Philosopher %d is eating.\n", id);
        sleep(1);

        // Put down right fork
        pthread_mutex_unlock(&forks[rightFork]);
        printf("Philosopher %d put down right fork %d.\n", id, rightFork);

        // Put down left fork
        pthread_mutex_unlock(&forks[leftFork]);
        printf("Philosopher %d put down left fork %d.\n", id, leftFork);
    }
}

int main() {
    int i;
    int ids[NUM_PHILOSOPHERS];

    // Initialize mutexes
    for (i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_mutex_init(&forks[i], NULL);
    }

    // Create philosopher threads
    for (i = 0; i < NUM_PHILOSOPHERS; i++) {
        ids[i] = i;
        pthread_create(&philosophers[i], NULL, philosopher, &ids[i]);
    }

    // Join philosopher threads
    for (i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_join(philosophers[i], NULL);
    }

    // Destroy mutexes
    for (i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_mutex_destroy(&forks[i]);
    }

    return 0;
}