#include <cstdio>
#include <cassert>
#include <cstdlib>
#include <cstring>

//#define PRG1 "Tyger Tyger, burning bright, In the forests of the night; What immortal hand or eye, Could frame thy fearful symmetry?"
//#define PRG2 "In what distant deeps or skies. Burnt the fire of thine eyes?On what wings dare he aspire?What the hand, dare seize the fire?"
//#define PRG3 "And what shoulder, & what art,Could twist the sinews of thy heart?And when thy heart began to beat,What dread hand? & what dread feet?"
//#define PRG4 "What the hammer? what the chain, In what furnace was thy brain?What the anvil? what dread grasp, Dare its deadly terrors clasp!"
//#define PRG5 "When the stars threw down their spears And water'd heaven with their tears: Did he smile his work to see?Did he who made the Lamb make thee?"
//#define PRG6 "Tyger Tyger burning bright, In the forests of the night: What immortal hand or eye,Dare frame thy fearful symmetry?"

#define FILENAME "newFile.txt"
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
    if(fp == nullptr){
        perror("Cannot open file to write!");
    }
    writeToSpecificIndex(fp, 0, prg1);
    writeToSpecificIndex(fp, 1000, prg2);
    writeToSpecificIndex(fp, 10000, prg3);
    writeToSpecificIndex(fp, 1000000, prg4);

    //writeToSpecificLine(fp, 4, PRG4);
    fclose(fp);
}

void readAndAssertWithIndex(FILE *fp, char prg[], int index){
    unsigned long lenPrg = strlen(prg);
    char buffer[lenPrg+1];
    char copybuf[lenPrg+1];
    memset(copybuf, '0', lenPrg*sizeof(char));

    fseek(fp, index, SEEK_SET);
    fgets(buffer, sizeof(buffer), fp);
    strncpy(copybuf, buffer, lenPrg+1);
    //assert(strcmp(prg, copybuf));
    printf("%s\n", copybuf);
    printf("%s\n", prg);
}

void readTheParagraphs(){
    FILE *fp;
    fp = fopen(FILENAME, "r+");
    if(fp == nullptr){
        perror("Cannot open file to read!");
    }

    readAndAssertWithIndex(fp, prg1, 0);
    readAndAssertWithIndex(fp, prg2, 1000);
    readAndAssertWithIndex(fp, prg3, 10000);
    readAndAssertWithIndex(fp, prg4, 1000000);

    fclose(fp);
}

int main() {
    customWriteToNewFile();
    readTheParagraphs();
    return 0;
}