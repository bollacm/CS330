//Dijkstra Solution source: https://en.wikipedia.org/wiki/Dining_philosophers_problem#Dijkstra's_solution
#include <stdio.h>
#include <stdbool.h>
#include <pthread.h>
#include <unistd.h>

int philosopher_hunger[5] = {100, 100, 100, 100, 100};
pthread_mutex_t forks[5];
pthread_t philosophers[5];

//hungry
bool is_hungry(int philosopher_hunger[5], int i) {
    if (philosopher_hunger[i] <= 20) {
        return true;
    }
    return false;
}


//thinking
bool is_thinking(int philosopher_hunger[5], int i) {
    if (is_hungry(philosopher_hunger, i) == false) {
        return true;
    }
    return false;
}


//eating
void eating(int philosopher_hunger[5], int i) {
    philosopher_hunger[i] += 10; // Increment hunger meter by 10
    if (philosopher_hunger[i] > 100) {
        philosopher_hunger[i] = 100;
    }
}

void* philosopher(void* num) {
    int i = *(int*)num;
    while (true) {


        // Decrement hunger level by 10 for each tick
        philosopher_hunger[i] -= 10;
        if (philosopher_hunger[i] <= 0) {
            philosopher_hunger[i] = 0;
            break;
        }


        // Thinking
        if (is_thinking(philosopher_hunger, i)) {
            printf("Philosopher %d is thinking. Hunger: %d \n", i, philosopher_hunger[i]);
            sleep(1);
        }

        // Hungry
        if (is_hungry(philosopher_hunger, i)) {
            printf("Philosopher %d is hungry.  Hunger: %d\n", i, philosopher_hunger[i]);

            // Pick up forks
            pthread_mutex_lock(&forks[i]);
            pthread_mutex_lock(&forks[(i + 1) % 5]);

            // Eating
            printf("Philosopher %d is eating.  Hunger: %d \n", i, philosopher_hunger[i]);
            eating(philosopher_hunger, i);
            sleep(1);

            // Put down forks
            pthread_mutex_unlock(&forks[i]);
            pthread_mutex_unlock(&forks[(i + 1) % 5]);
        }
    }
    printf("Philosopher is done");
    return NULL;
}


int main() {

    //int philosopher_hunger[5] = {100, 100, 100, 100, 100};
    //bool fork[5] = {true, true, true, true, true};
      // Initialize mutexes
    for (int i = 0; i < 5; i++) {
        pthread_mutex_init(&forks[i], NULL);
    }

    // Create philosopher threads
    int philosopher_ids[5];
    for (int i = 0; i < 5; i++) {
        philosopher_ids[i] = i;
        pthread_create(&philosophers[i], NULL, philosopher, &philosopher_ids[i]);
    }

    // Join philosopher threads
    for (int i = 0; i < 5; i++) {
        pthread_join(philosophers[i], NULL);
    }

    // Destroy mutexes
    for (int i = 0; i < 5; i++) {
        pthread_mutex_destroy(&forks[i]);
    }


}