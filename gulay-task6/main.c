#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>

#define FILE_NAME "task100.config"
#define MAX_LEN 1500
int retrieved_number = 10; //number of paragraphs

pthread_cond_t cond0 = PTHREAD_COND_INITIALIZER;
pthread_cond_t cond1 = PTHREAD_COND_INITIALIZER;
pthread_cond_t cond2 = PTHREAD_COND_INITIALIZER;
pthread_cond_t cond3 = PTHREAD_COND_INITIALIZER;

pthread_mutex_t lock0 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t lock1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t lock2 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t lock3 = PTHREAD_MUTEX_INITIALIZER;

int get_number_from_first_line(FILE *fp){
    char buffer[10];
    fgets(buffer, sizeof(buffer), fp);
    return retrieved_number = atoi(buffer);
}

void read_file(FILE *fp){
    get_number_from_first_line(fp);
    char line[MAX_LEN];
    fgets(line, sizeof line, fp);
    for(int i=0; i<retrieved_number; i++){
        fscanf(fp, "%[^\n]\n", &line);
        printf("%s\n", line);
    }
    //printf("ret_num: %d, count: %d", retrieved_number, count);
}

void *parent_thread_func0(void *arg){
    while(retrieved_number!=0){
        pthread_mutex_lock(&lock0);
        //JOB Here
        retrieved_number--;

        pthread_cond_wait(&cond0, &lock0);
        printf("I am thread0 PARENT generating the final report and inserting into a table \n");
        pthread_cond_signal(&cond1);
        pthread_mutex_unlock(&lock0);
    }
    pthread_exit(NULL);
}

void *parent_thread_func1(void *arg){
    while(retrieved_number!=0){
        pthread_mutex_lock(&lock1);
        //JOB Here
        retrieved_number--;

        pthread_cond_wait(&cond1, &lock1);
        printf("I am thread1 PARENT generating the final report and inserting into a table \n");
        pthread_cond_signal(&cond2);
        pthread_mutex_unlock(&lock1);
    }
    pthread_exit(NULL);
}

void *child_thread_func2(void *arg){
    while(retrieved_number!=0){
        pthread_mutex_lock(&lock2);
        //JOB Here
        retrieved_number--;

        pthread_cond_wait(&cond2, &lock2);
        printf("I am thread2 CHILD generating the final report and inserting into a table \n");
        pthread_cond_signal(&cond3);
        pthread_mutex_unlock(&lock2);
    }
    pthread_exit(NULL);
}

void *child_thread_func3(void *arg){
    while(retrieved_number!=0){
        pthread_mutex_lock(&lock3);
        //JOB Here
        retrieved_number--;

        pthread_cond_wait(&cond3, &lock3);
        printf("I am thread3 CHILD generating the final report and inserting into a table \n");
        pthread_cond_signal(&cond0);
        pthread_mutex_unlock(&lock3);
    }
    pthread_exit(NULL);
}

int main() {
    FILE *fp = fopen(FILE_NAME, "r");
    if (fp == NULL){
        perror("Cannot open file!");
        return(-1);
    }

    get_number_from_first_line(fp);
    printf("ret_num: %d\n", retrieved_number);

    pthread_t tid0, tid1, tid2, tid3;

   /* int pid = fork();
    if(pid == -1){
        perror("Fork failed!");
        return -1;
    }else if (pid == 0){
        if( pthread_create(&tid[0], NULL, parent_thread_func0, NULL) != 0 )
            printf("Failed to create thread0\n");
        if( pthread_create(&tid[1], NULL, parent_thread_func1, NULL) != 0 )
            printf("Failed to create thread1\n");

    }else{
        if( pthread_create(&tid[2], NULL, child_thread_func2(), NULL) != 0 )
            printf("Failed to create thread2\n");
        if( pthread_create(&tid[3], NULL, child_thread_func3(), NULL) != 0 )
            printf("Failed to create thread3\n");
    }*/

    if( pthread_create(&tid0, NULL, parent_thread_func0, NULL) != 0 )
        printf("Failed to create thread0\n");
    if( pthread_create(&tid1, NULL, parent_thread_func1, NULL) != 0 )
        printf("Failed to create thread1\n");
    if( pthread_create(&tid2, NULL, child_thread_func2, NULL) != 0 )
        printf("Failed to create thread2\n");
    if( pthread_create(&tid3, NULL, child_thread_func3, NULL) != 0 )
        printf("Failed to create thread3\n");

    pthread_cond_signal(&cond0);

    sleep(3);
    printf("HERE\n");

    pthread_mutex_destroy(&lock0);
    pthread_mutex_destroy(&lock1);
    pthread_mutex_destroy(&lock2);
    pthread_mutex_destroy(&lock3);

    pthread_cond_destroy(&cond0);
    pthread_cond_destroy(&cond1);
    pthread_cond_destroy(&cond2);
    pthread_cond_destroy(&cond3);

    pthread_join(tid0, NULL);
    pthread_join(tid1,NULL);
    pthread_join(tid2,NULL);
    pthread_join(tid3,NULL);

    fclose(fp);
    return 0;
}
