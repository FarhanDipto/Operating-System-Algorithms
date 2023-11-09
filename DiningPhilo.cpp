#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#define NUM_PHILOSOPHERS 5

using namespace std;

enum PhilosopherStatus {
    THINKING,
    DINING
};

sem_t chopsticks[NUM_PHILOSOPHERS];

void* philosopher(void* arg) {
    int philosopherID = *(int*)arg;
    int leftChopstick = philosopherID;
    int rightChopstick = (philosopherID + 1) % NUM_PHILOSOPHERS;

    while (true) {

        cout << "Philosopher " << philosopherID << " is thinking." << endl;
        sleep(2);

        sem_wait(&chopsticks[leftChopstick]);
        sem_wait(&chopsticks[rightChopstick]);

        cout << "Philosopher " << philosopherID << " is dining." << endl;
        sleep(2);

        sem_post(&chopsticks[leftChopstick]);
        sem_post(&chopsticks[rightChopstick]);
    }

    pthread_exit(NULL);
}

int main() {
    pthread_t philosophers[NUM_PHILOSOPHERS];
    int philosopherIDs[NUM_PHILOSOPHERS];

    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        sem_init(&chopsticks[i], 0, 1);
    }

    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        philosopherIDs[i] = i;
        pthread_create(&philosophers[i], NULL, philosopher, (void*)&philosopherIDs[i]);
    }

    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_join(philosophers[i], NULL);
    }

    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        sem_destroy(&chopsticks[i]);
    }
    return 0;
}
