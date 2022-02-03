#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>

#define FILENAME "lorem.txt"

char prg1[] = "1-Tyger Tyger, burning bright, In the forests of the night; What immortal hand or eye, Could frame the fearful symmetry?";
char prg2[] = "2-In what distant deeps or skies Burnt the fire of thine eyes? On what wings dare he aspire? What the hand, dare seize the fire?";
char prg3[] = "3-And what shoulder, & what art, Could twist the sinews of the heart? And when the heart began to beat, What dread hand? & what dread feet?";
char prg4[] = "4-What the hammer? what the chain, In what furnace was the brain? What the anvil? what dread grasp, Dare its deadly terrors clasp!";
char prg5[] = "5-When the stars threw down their spears And water'd heaven with their tears, Did he smile his work to see? Did he who made the Lamb make thee?";
char prg6[] = "6-Tyger Tyger burning bright, In the forests of the night, What immortal hand or eye,Dare frame the fearful symmetry?";

long lastIndex = 0;
long maxIndex = 0;
unsigned long lastStrLen = 0;

void write_dummy_string_from_n_character(FILE *fp, unsigned long n){
    for(int i = 0; i < n; i++){
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
    write_to_file_index(fp, 0, prg1);
    write_to_file_index(fp, 1000, prg2);
    write_to_file_index(fp, 10000, prg3);
    write_to_file_index(fp, 1000000, prg4);
    write_to_file_index(fp, 100000000, prg5);
    write_to_file_index(fp, 10000000000, prg6);

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

void open_file(){
    FILE *fp= fopen(FILENAME, "r+");
    if(fp == NULL){
        perror("Cannot open file to read! You can either provide an existing file and change the FILENAME, "
               "or run the custom_write_to_new_file() function once");
    }
}

void *thread_func(){
    /*pthread_once_t once_control = PTHREAD_ONCE_INIT;
    pthread_once(&once_control, open_file);*/
    FILE *fp= fopen(FILENAME, "r+");
    if(fp == NULL){
        perror("Cannot open file to read!");
    }

    read_and_assert_with_index(fp, prg1, 0);
}

int main() {
    pthread_t tid;

    pthread_create(&tid, NULL, thread_func, NULL);
    pthread_create(&tid, NULL, thread_func, NULL);

    pthread_exit(NULL);
    return 0;
}
