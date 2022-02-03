#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

#define FILENAME "lorem.txt"
//#define MAXLEN 350

char prg1[] = "Tyger Tyger, burning bright, In the forests of the night; What immortal hand or eye, Could frame thy fearful symmetry?";
char prg2[] = "In what distant deeps or skies. Burnt the fire of thine eyes?On what wings dare he aspire?What the hand, dare seize the fire?";
char prg3[] = "And what shoulder, & what art,Could twist the sinews of thy heart?And when thy heart began to beat,What dread hand? & what dread feet?";
char prg4[] = "What the hammer? what the chain, In what furnace was thy brain?What the anvil? what dread grasp, Dare its deadly terrors clasp!";

//int lineCount = 0;
int lastIndex = 0;
int maxIndex = 0;
unsigned long lastStrLen = 0;

/*
void writeToSpecificLine(FILE *fp, int line, char *str){
    //printf("%ld\n", ftell(fp));
    fseek(fp, 0, SEEK_END);
    for(int i = 1; i < line - lineCount; i++){
        fprintf(fp, "\n");
    }
    fprintf(fp, str);
    lineCount = line-1;
}
 */

void write_dummy_string_from_n_character(FILE *fp, int n){
    for(int i = 0; i < n; i++){
        //26 (alphabet) + 4 space character to increase the probability of space
        char randomletter = "ABCDEFGHIJKLMNOPQRSTUVWXYZ    "[rand() % 30];
        fprintf(fp, "%c", randomletter);
    }
}

void write_to_file_index(FILE *fp, int index, char *str){
    if(index>maxIndex){
        maxIndex = index;
        int dummyStrLen = index-lastIndex-lastStrLen;
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

    //writeToSpecificLine(fp, 4, PRG4);
    fclose(fp);
}

void read_and_assert_with_index(FILE *fp, char prg[], int index){
    unsigned long lenPrg = strlen(prg);
    char buffer[lenPrg+1];

    fseek(fp, index, SEEK_SET);
    fgets(buffer, sizeof(buffer), fp);
    assert(!strcmp(prg, buffer));
    printf("%s\n", buffer);
}

void read_the_file(){
    FILE *fp;
    fp = fopen(FILENAME, "r+");
    if(fp == NULL){
        perror("Cannot open file to read!");
    }

    read_and_assert_with_index(fp, prg1, 0);
    read_and_assert_with_index(fp, prg2, 1000);
    read_and_assert_with_index(fp, prg3, 10000);
    read_and_assert_with_index(fp, prg4, 1000000);

    fclose(fp);
}

int main() {
    custom_write_to_new_file();
    read_the_file();
    return 0;
}