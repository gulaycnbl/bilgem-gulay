#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>

#define FILENAME "lorem.txt"
#define NUMOFPRGS 6

char prg0[] = "1-Tyger Tyger, burning bright, In the forests of the night; What immortal hand or eye, Could frame the fearful symmetry?";
char prg1[] = "2-In what distant deeps or skies Burnt the fire of thine eyes? On what wings dare he aspire? What the hand, dare seize the fire?";
char prg2[] = "3-And what shoulder, & what art, Could twist the sinews of the heart? And when the heart began to beat, What dread hand? & what dread feet?";
char prg3[] = "4-What the hammer? what the chain, In what furnace was the brain? What the anvil? what dread grasp, Dare its deadly terrors clasp!";
char prg4[] = "5-When the stars threw down their spears And water'd heaven with their tears, Did he smile his work to see? Did he who made the Lamb make thee?";
char prg5[] = "6-Tyger Tyger burning bright, In the forests of the night, What immortal hand or eye,Dare frame the fearful symmetry?";

const char *arrayForPrgs[6] = {
        prg0,
        prg1,
        prg2,
        prg3,
        prg4,
        prg5,
};

long lastIndex = 0;
long maxIndex = 0;
unsigned long lastStrLen = 0;
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
    if(index>maxIndex){
        maxIndex = index;
        unsigned long dummyStrLen = index-lastIndex-lastStrLen;
        write_dummy_string_from_n_character(fp, dummyStrLen);
    }
    lastStrLen = strlen(str);
    lastIndex = index;
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
            write_to_file_index(fp, 1000, arrayForPrgs[i]);
        }else{
            write_to_file_index(fp, my_pow(100, i), arrayForPrgs[i]);
        }
    }

    fclose(fp);
}

void read_and_assert_with_index(FILE *fp, char prg[], long index){
    unsigned long lenPrg = strlen(prg);
    char buffer[lenPrg+1];

    fseek(fp, index, SEEK_SET);
    fgets(buffer, sizeof(buffer), fp);
    assert(!strcmp(prg, buffer));
    printf("The %lu indexed content of the file (%s) matches with the predefined content.\n", index, FILENAME);
}

void *thread_func(int *indArr[]){
    /*pthread_once_t once_control = PTHREAD_ONCE_INIT;
    pthread_once(&once_control, open_file);*/
    /*FILE *fp= fopen(FILENAME, "r+");
    if(fp == NULL){
        perror("Cannot open file to read! You can either provide an existing file and change the FILENAME, "
               "or run the custom_write_to_new_file() function once");
    }*/

    /*
   for(int i=0; i<3; i++){
        pthread_mutex_lock(&lock);
        read_and_assert_with_index(fp, array[i], indArr[i]);
        pthread_mutex_unlock(&lock);
    }
    */

    //printf("%d\n",indArr[0]);

    //printf("%s\n", array[0]);
    //read_and_assert_with_index(fp, array[0], indArr[0]);
    //read_and_assert_with_index(fp, arrayForAssertForThread2[0], indexArray2[0]);
    return NULL;
}

int main() {
    FILE *fp= fopen(FILENAME, "r+");
    if(fp == NULL){
        perror("Cannot open file to read!");
    }

    for(int i=0; i<NUMOFPRGS; i++){
        //index that violates the series (it's 1000 because 1 and 100 is too close)
        if(i==1){
            read_and_assert_with_index(fp, arrayForPrgs[i], 1000);
        }else{
            read_and_assert_with_index(fp, arrayForPrgs[i], my_pow(100, i));
        }
    }
    /*
    pthread_t tid[2];

    printf("MAİN, indexArr1[0]: %d\n", indexArray1[0]);
    printf("MAİN, indexArr1[1]: %d\n", indexArray1[1]);
    printf("MAİN, indexArr1[2]: %d\n", indexArray1[2]);

    if (pthread_mutex_init(&lock, NULL) != 0)
    {
        printf("\n mutex init failed\n");
        return 1;
    }

    pthread_create(&(tid[0]), NULL, &thread_func, (void *)indexArray1);
    //pthread_create(&(tid[1]), NULL, &thread_func, (arrayForAssertForThread2, indexArray2));

    pthread_join(tid[0], NULL);
    //pthread_join(tid[1], NULL);
    pthread_mutex_destroy(&lock);*/
    return 0;
}
