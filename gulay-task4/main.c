#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#define FILENAME "lorem.txt"
#define NUMOFPRGS 6

char prg0[] = "1-Tyger Tyger, burning bright, In the forests of the night; What immortal hand or eye, Could frame the fearful symmetry?";
char prg1[] = "2-In what distant deeps or skies Burnt the fire of thine eyes? On what wings dare he aspire? What the hand, dare seize the fire?";
char prg2[] = "3-And what shoulder, & what art, Could twist the sinews of the heart? And when the heart began to beat, What dread hand? & what dread feet?";
char prg3[] = "4-What the hammer? what the chain, In what furnace was the brain? What the anvil? what dread grasp, Dare its deadly terrors clasp!";
char prg4[] = "5-When the stars threw down their spears And water'd heaven with their tears, Did he smile his work to see? Did he who made the Lamb make thee?";
char prg5[] = "6-Tyger Tyger burning bright, In the forests of the night, What immortal hand or eye,Dare frame the fearful symmetry?";

const char *array_for_prgs[NUMOFPRGS] = {
        prg0,
        prg1,
        prg2,
        prg3,
        prg4,
        prg5,
};

long last_index = 0;
long max_index = 0;
unsigned long last_str_len = 0;
pthread_mutex_t lock;

long my_pow(int a, long b){
    if(b==0) return 1;
    return a * my_pow(a, b - 1);
}

void write_dummy_string_from_n_character(FILE *fp, unsigned long n){
    for(long i = 0; i < n; i++){
        char randomletter = "ABCDEFGHIJKLMNOPQRSTUVWXYZ    "[rand() % 30];
        fprintf(fp, "%c", randomletter);
    }
}

void write_to_file_index(FILE *fp, long index, char *str){
    if(index > max_index){
        max_index = index;
        unsigned long dummy_str_len = index - last_index - last_str_len;
        write_dummy_string_from_n_character(fp, dummy_str_len);
    }
    last_str_len = strlen(str);
    last_index = index;
    fseek(fp, index, SEEK_SET);
    fprintf(fp, "%s", str);
}

void custom_write_to_new_file(){
    FILE *fp= fopen(FILENAME, "w+");
    if(fp == NULL){
        perror("Cannot open file to write!");
    }
    write_to_file_index(fp, 1, prg0);
    for(int i=0; i<NUMOFPRGS; i++){
        //index that violates the series (it's 1000 because 1 and 100 is too close)
        if(i==1){
            write_to_file_index(fp, 1000, array_for_prgs[i]);
        }else{
            write_to_file_index(fp, my_pow(100, i), array_for_prgs[i]);
        }
    }

    fclose(fp);
}

void read_and_assert_with_index(FILE *fp, char prg[], long index){
    unsigned long len_of_prg = strlen(prg);
    char buffer[len_of_prg + 1];

    fseek(fp, index, SEEK_SET);
    fgets(buffer, sizeof(buffer), fp);
    assert(strcmp(prg, buffer)==0);
    printf("The %lu indexed content of the file (%s) matches with the predefined content.\n", index, FILENAME);
}

void *thread_read_even_index_func(){
    FILE *fp= fopen(FILENAME, "r+");
    if(fp == NULL){
        perror("Cannot open file to read! You can either provide an existing file and change the FILENAME, "
               "or run the custom_write_to_new_file() function once");
    }
    for(int i=0; i<NUMOFPRGS; i++){
        if((i == 0) || (i%2 == 0)){
            pthread_mutex_lock(&lock);
            printf("Inside the thread [%lu]: Prg %d - ", pthread_self(), i);
            read_and_assert_with_index(fp, array_for_prgs[i], my_pow(100, i));
            pthread_mutex_unlock(&lock);
        }
    }
    return NULL;
}

void *thread_read_odd_index_func(){
    FILE *fp= fopen(FILENAME, "r+");
    if(fp == NULL){
        perror("Cannot open file to read! You can either provide an existing file and change the FILENAME, "
               "or run the custom_write_to_new_file() function once");
    }

   for(int i=0; i<NUMOFPRGS; i++){
       if(i%2 != 0){
           pthread_mutex_lock(&lock);
           if(i==1){
               printf("Inside the thread [%lu]: Prg %d - ", pthread_self(), i);
               read_and_assert_with_index(fp, array_for_prgs[i], 1000);
           }else{
               printf("Inside the thread [%lu]: Prg %d - ", pthread_self(), i);
               read_and_assert_with_index(fp, array_for_prgs[i], my_pow(100, i));
           }
           pthread_mutex_unlock(&lock);
       }
    }
    return NULL;
}

int main() {
    FILE *fp= fopen(FILENAME, "r+");
    if(fp == NULL){
        perror("Cannot open file to read!");
    }
    pthread_t tid[2];

    if (pthread_mutex_init(&lock, NULL) != 0) {
        printf("\n mutex init failed\n");
        return 1;
    }

    pthread_create(&(tid[0]), NULL, &thread_read_even_index_func, NULL);
    pthread_create(&(tid[1]), NULL, &thread_read_odd_index_func, NULL);

    pthread_join(tid[0], NULL);
    pthread_join(tid[1], NULL);
    pthread_mutex_destroy(&lock);
    return 0;
}
