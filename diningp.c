//Dijkstra Solution source: https://en.wikipedia.org/wiki/Dining_philosophers_problem#Dijkstra's_solution
#include <stdio.h>
#include <stdbool.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>

int philosopher_hunger[5] = {100, 100, 100, 100, 100};
int hunger_tick = 1;
pthread_mutex_t forks[5];
pthread_t philosophers[5];
pthread_mutex_t console_mutex;

//hungry
bool is_hungry(int philosopher_hunger[5], int i) {
    if (philosopher_hunger[i] <= 20) {
        return true;
    }
    return false;
}


//thinking
bool is_thinking(int philosopher_hunger[5], int i) {
    philosopher_hunger[i] -= hunger_tick;
    if (is_hungry(philosopher_hunger, i) == false) {
        return true;
    }
    return false;
}


//eating
void eating(int philosopher_hunger[5], int i) {
    philosopher_hunger[i] += hunger_tick; // Increment hunger meter
    if (philosopher_hunger[i] > 100) {
        philosopher_hunger[i] = 100;
    }
}

bool could_eat(int i) {
    // Check if any philosopher is hungry
    for (int j = 0; j < 5; j++) {
        if (is_hungry(philosopher_hunger, j)) {
            return false; // Prioritize hungry philosophers
        }
    }
    return philosopher_hunger[i] < 100; // Allow eating if hunger is less than 100
}

void* philosopher(void* num) {
    int i = *(int*)num;

    while (true) {


        // Decrement hunger level for each tick
        if (philosopher_hunger[i] <= 0) {
            philosopher_hunger[i] = 0;
            break;
        }


        // Thinking
        if (is_thinking(philosopher_hunger, i)) {
            pthread_mutex_lock(&console_mutex);
            printf("Philosopher %d is thinking. Hunger: %d \n", i, philosopher_hunger[i]);
            pthread_mutex_unlock(&console_mutex);
            sleep(1);
        }

        // Hungry or wants to eat
        if (is_hungry(philosopher_hunger, i)) {
            pthread_mutex_lock(&console_mutex);
             if (is_hungry(philosopher_hunger, i)){
                printf("Philosopher %d is hungry.  Hunger: %d\n", i, philosopher_hunger[i]);
             } else {
                printf("Philosopher %d wants to eat. Hunger: %d\n", i, philosopher_hunger[i]);
            }
    

            pthread_mutex_unlock(&console_mutex);

            // Pick up forks
            pthread_mutex_lock(&forks[i]);
            pthread_mutex_lock(&forks[(i + 1) % 5]);

            // Check if philosopher is dead
            if (philosopher_hunger[i] == 0) {
                pthread_mutex_lock(&console_mutex);
                printf("Philosopher %d has died while holding forks.\n", i);
                pthread_mutex_unlock(&console_mutex);
                // Do not release forks, causing a deadlock
                while (true) {
                    sleep(1); // Infinite loop to simulate deadlock
                }
            }

            // Eating
            pthread_mutex_lock(&console_mutex);
            printf("Philosopher %d is eating.  Hunger: %d \n", i, philosopher_hunger[i]);
            pthread_mutex_unlock(&console_mutex);
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
    //create health >=20 <=100 randomly
    srand(time(NULL));

    for(int i =0; i<5;i++){
        int x = rand()%101;
        if(x>20) {
            philosopher_hunger[i] = x;
        }
        else {
            philosopher_hunger[i] = 20;
        }
    }

    // Initialize mutexes
    for (int i = 0; i < 5; i++) {
        pthread_mutex_init(&forks[i], NULL);
    }
    pthread_mutex_init(&console_mutex, NULL);

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
    pthread_mutex_destroy(&console_mutex);


    return 0;
}