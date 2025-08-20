#include <stdio.h>
#include <pthread.h>

#define MAX 100

int counter = 1;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

void* print_numbers(void* arg) {
    int is_odd = *(int*)arg;

    while (1) {
        pthread_mutex_lock(&lock);

        if (counter > MAX) {
            pthread_mutex_unlock(&lock);
            break;
        }

        if ((counter % 2 == 1 && is_odd) || (counter % 2 == 0 && !is_odd)) {
            printf("%s Thread: %d\n", is_odd ? "Odd" : "Even", counter);
            counter++;
        }

        pthread_mutex_unlock(&lock);
    }

    return NULL;
}

int main() {
    pthread_t t1, t2;
    int odd = 1, even = 0;

    pthread_create(&t1, NULL, print_numbers, &odd);
    pthread_create(&t2, NULL, print_numbers, &even);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    return 0;
}
