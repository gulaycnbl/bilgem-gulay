#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define FILENAME "lorem.txt"

char prg1[] = "1-Tyger Tyger, burning bright, In the forests of the night; What immortal hand or eye, Could frame the fearful symmetry?";
char prg2[] = "2-In what distant deeps or skies Burnt the fire of thine eyes? On what wings dare he aspire? What the hand, dare seize the fire?";
char prg3[] = "3-And what shoulder, & what art, Could twist the sinews of the heart? And when the heart began to beat, What dread hand? & what dread feet?";
char prg4[] = "4-What the hammer? what the chain, In what furnace was the brain? What the anvil? what dread grasp, Dare its deadly terrors clasp!";
char prg5[] = "5-When the stars threw down their spears And water'd heaven with their tears, Did he smile his work to see? Did he who made the Lamb make thee?";
char prg6[] = "6-Tyger Tyger burning bright, In the forests of the night, What immortal hand or eye,Dare frame the fearful symmetry?";

int lastIndex = 0;
int maxIndex = 0;
unsigned long lastStrLen = 0;

//Function to write given paragraph 'str' into given index in the file fp
//by inserting meaningless arbitrary letters between the paragraphs
void writeToSpecificIndex(FILE *fp, int index, char *str){
    if(index>maxIndex){
        maxIndex = index;
        for(int i = 0; i < index-lastIndex-lastStrLen; i++){
            //26 (alphabet) + 4 space character to increase the possibility of space
            char randomletter = "ABCDEFGHIJKLMNOPQRSTUVWXYZ    "[random () % 30];
            fprintf(fp, "%c", randomletter);
        }
    }
    lastStrLen = strlen(str);
    lastIndex = index;
    fseek(fp, index, SEEK_SET);
    fprintf(fp, "%s", str);
}

void customWriteToNewFile(){
    FILE *fp= fopen(FILENAME, "w+");
    if(fp == NULL){
        perror("Cannot open file to write!");
    }
    writeToSpecificIndex(fp, 0, prg1);
    writeToSpecificIndex(fp, 1000, prg2);
    writeToSpecificIndex(fp, 10000, prg3);
    writeToSpecificIndex(fp, 1000000, prg4);
    writeToSpecificIndex(fp, 100000000, prg5);
    writeToSpecificIndex(fp, 10000000000, prg6);

    fclose(fp);
}

void readAndAssertWithIndex(FILE *fp, char prg[], int index){
    unsigned long lenPrg = strlen(prg);
    char buffer[lenPrg+1];

    fseek(fp, index, SEEK_SET);
    fgets(buffer, sizeof(buffer), fp);
    assert(!strcmp(prg, buffer)); //strcmp gives 0 (false) if the strings are equal
    printf("%s\n", buffer);
}

void readTheParagraphs(){
    FILE *fp;
    fp = fopen(FILENAME, "r+");
    if(fp == NULL){
        perror("Cannot open file to read!");
    }

    readAndAssertWithIndex(fp, prg1, 0);
    readAndAssertWithIndex(fp, prg2, 1000);
    readAndAssertWithIndex(fp, prg3, 10000);
    readAndAssertWithIndex(fp, prg4, 1000000);
    readAndAssertWithIndex(fp, prg5, 100000000);
    readAndAssertWithIndex(fp, prg6, 10000000000);

    fclose(fp);
}

int main() {
    customWriteToNewFile();
    FILE *fp;
    fp = fopen(FILENAME, "r+");
    if(fp == NULL){
        perror("Cannot open file to read!");
    }

    //child process
    if(fork()==0){
        readAndAssertWithIndex(fp, prg1, 0);
        readAndAssertWithIndex(fp, prg3, 10000);
        readAndAssertWithIndex(fp, prg5, 100000000);
    }else{
        readAndAssertWithIndex(fp, prg2, 1000);
        readAndAssertWithIndex(fp, prg4, 1000000);
        readAndAssertWithIndex(fp, prg6, 10000000000);
    }

    fclose(fp);
    return 0;
}