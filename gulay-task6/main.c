#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>

#define FILE_NAME "task500.config"
#define MAX_LEN 1500
#define NUM_OF_THREADS 4
int retrieved_number_of_paragraphs;

int get_number_from_first_line(FILE *fp){
    char buffer[10];
    fgets(buffer, sizeof(buffer), fp);
    return retrieved_number_of_paragraphs = atoi(buffer);
}

void *thread_read_file(int n){
    FILE *fp = fopen(FILE_NAME, "r+");
    if (fp == NULL) perror("Cannot open file!");

    get_number_from_first_line(fp);
    char line[MAX_LEN];
    fgets(line, sizeof line, fp);
    for(int i=0; i < retrieved_number_of_paragraphs - 1; i++){
        if(i%NUM_OF_THREADS == n){
            fscanf(fp, "%[^\n]\n", &line);
            printf("Thread [%d] read paragraph %d\n", n, i);
        }else{
            fscanf(fp, "%[^\n]\n", &line);
        }
    }
    close(fp);
}

int main() {
    pthread_t tid0, tid1, tid2, tid3;

    int pid = fork();
    if(pid == -1){
        perror("Fork failed!");
        return -1;
    }else if (pid == 0){
        if (pthread_create(&tid0, NULL, (void *(*)(void *)) thread_read_file, 0) != 0) {
            printf("Failed to create thread0\n");
        }
        if (pthread_create(&tid1, NULL, (void *(*)(void *)) thread_read_file, 1) != 0) {
            printf("Failed to create thread0\n");
        }
        pthread_join(tid0, NULL);
        pthread_join(&tid1, NULL);
    }else{
        if (pthread_create(&tid2, NULL, (void *(*)(void *)) thread_read_file, 2) != 0) {
            printf("Failed to create thread0\n");
        }
        if (pthread_create(&tid3, NULL, (void *(*)(void *)) thread_read_file, 3) != 0) {
            printf("Failed to create thread0\n");
        }
        pthread_join(tid2, NULL);
        pthread_join(&tid3, NULL);
    }
    return 0;
}
