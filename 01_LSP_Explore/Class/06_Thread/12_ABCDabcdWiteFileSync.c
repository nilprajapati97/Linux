#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

FILE *fp;
pthread_mutex_t mutex;
pthread_cond_t cond;
int turn = 0; // 0 for capital thread, 1 for small thread

void* write_caps(void* arg) {
    for (char ch = 'A'; ch <= 'Z'; ch++) {
        pthread_mutex_lock(&mutex);
        while (turn != 0)
            pthread_cond_wait(&cond, &mutex);
        printf("%c",ch);
        fputc(ch, fp);
        fflush(fp);
        turn = 1;
        pthread_cond_signal(&cond);
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

void* write_smalls(void* arg) {
    for (char ch = 'a'; ch <= 'z'; ch++) {
        pthread_mutex_lock(&mutex);
        while (turn != 1)
            pthread_cond_wait(&cond, &mutex);
        printf(" %c\n",ch);
        fputc(ch, fp);
        fflush(fp);
        turn = 0;
        pthread_cond_signal(&cond);
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

int main() {
    pthread_t t1, t2;

    fp = fopen("output.txt", "w");
    if (!fp) {
        perror("fopen");
        return 1;
    }

    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&cond, NULL);

    pthread_create(&t1, NULL, write_caps, NULL);
    pthread_create(&t2, NULL, write_smalls, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    fclose(fp);
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond);

    printf("Written AaBbCc...Zz pattern to output.txt\n");
    return 0;
}
