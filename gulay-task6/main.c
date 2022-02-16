#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>

#define FILE_NAME "task100.config"
#define MAX_LEN 1500
int retrieved_number; //number of paragraphs

pthread_mutex_t lock1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t lock2 = PTHREAD_MUTEX_INITIALIZER;

int get_number_from_first_line(FILE *fp){
    char buffer[10];
    fgets(buffer, sizeof(buffer), fp);
    return retrieved_number = atoi(buffer);
}

void read_file(int n){
    FILE *fp = fopen(FILE_NAME, "r+");
    if (fp == NULL) perror("Cannot open file!");

    get_number_from_first_line(fp);
    char line[MAX_LEN];
    fgets(line, sizeof line, fp);
    for(int i=0; i<retrieved_number; i++){
        if(i%4 == n){
            fscanf(fp, "%[^\n]\n", &line);
            printf("Inside child thread [%d]:\n%s\n\n", n, line);
        }else{
            fscanf(fp, "%[^\n]\n", &line);
        }
    }
    close(fp);
}

void *thread_func_parent(int n){
    FILE *fp = fopen(FILE_NAME, "r+");
    if (fp == NULL) perror("Cannot open file!");

    get_number_from_first_line(fp);
    char line[MAX_LEN];
    fgets(line, sizeof line, fp);
    for(int i=0; i<retrieved_number; i++){
        if(i%4 == n){
            pthread_mutex_lock(&lock1);
            fscanf(fp, "%[^\n]\n", &line);
            printf("Inside parent thread [%d]:\n%s\n\n", n, line);
            pthread_mutex_unlock(&lock1);
        }
        //fscanf(fp, "%[^\n]\n", &line);

    }

    fclose(fp);
    return NULL;
}

void *thread_func_child(int n){
    FILE *fp = fopen(FILE_NAME, "r+");
    if (fp == NULL) perror("Cannot open file!");

    get_number_from_first_line(fp);
    char line[MAX_LEN];
    fgets(line, sizeof line, fp);
    for(int i=0; i<retrieved_number; i++){

        if(i%4 == n){
            pthread_mutex_lock(&lock2);
            fscanf(fp, "%[^\n]\n", &line);
            printf("%s\n", line);
            pthread_mutex_unlock(&lock2);
        }
        //fscanf(fp, "%[^\n]\n", &line);

    }

    fclose(fp);
    return NULL;
}

int main() {
    pthread_t tid0, tid1, tid2, tid3;

    int pid = fork();
    if(pid == -1){
        perror("Fork failed!");
        return -1;
    }else if (pid == 0){
        if (pthread_create(&tid0, NULL, (void *(*)(void *)) thread_func_parent, 0) != 0) {
            printf("Failed to create thread0\n");
        }
        if (pthread_create(&tid1, NULL, (void *(*)(void *)) thread_func_parent, (void *) 1) != 0) {
            printf("Failed to create thread1\n");
        }
        printf("inside child retnum: %d\n", retrieved_number);

        pthread_join(tid0, NULL);
        pthread_join(tid1,NULL);
    }else{
        if (pthread_create(&tid2, NULL, (void *(*)(void *)) thread_func_child, (void *) 2) != 0) {
            printf("Failed to create thread2\n");
        }
        if (pthread_create(&tid3, NULL, (void *(*)(void *)) thread_func_child, (void *) 3) != 0) {
            printf("Failed to create thread3\n");
        }
        printf("Inside parent retnum: %d\n", retrieved_number);

        pthread_join(tid2,NULL);
        pthread_join(tid3,NULL);
    }

    pthread_mutex_destroy(&lock1);
    pthread_mutex_destroy(&lock2);

    return 0;
}
