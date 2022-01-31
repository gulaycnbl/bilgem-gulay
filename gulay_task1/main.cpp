#include <cstdio>
#include <cassert>
#include <cstdlib>
#include <cstring>

#define PRG1 "Tyger Tyger, burning bright, In the forests of the night; What immortal hand or eye, Could frame thy fearful symmetry?"
#define PRG2 "In what distant deeps or skies. Burnt the fire of thine eyes?On what wings dare he aspire?What the hand, dare seize the fire?"
#define PRG3 "And what shoulder, & what art,Could twist the sinews of thy heart?And when thy heart began to beat,What dread hand? & what dread feet?"
#define PRG4 "What the hammer? what the chain, In what furnace was thy brain?What the anvil? what dread grasp, Dare its deadly terrors clasp!"
#define PRG5 "When the stars threw down their spears And water'd heaven with their tears: Did he smile his work to see?Did he who made the Lamb make thee?"
#define PRG6 "Tyger Tyger burning bright, In the forests of the night: What immortal hand or eye,Dare frame thy fearful symmetry?"

#define FILEPATH "/home/admin/Genel/CLionProjects/gulay_task1/lorem.txt"
#define MAXLEN 350
#define NUMOFLINES 5

char **lines_to_check = (char **)malloc(NUMOFLINES*sizeof(char*));
/*const char * myarray[]{
    PRG1,
    PRG2,
    PRG3,
    PRG4,
};
*/ //can also be used as lines_to_check

void assignLines(){
    for(int i=0; i<NUMOFLINES; i++){
        lines_to_check[i] = (char *)malloc(MAXLEN*sizeof(char));
    }
    lines_to_check[0] = PRG1;
    lines_to_check[1] = PRG2;
    lines_to_check[2] = PRG3;
    lines_to_check[3] = PRG4;
}

void freeLines(char **lines){
    for(int i=0; i<NUMOFLINES; i++) free(lines[i]);
    free(lines);
}

int main() {
    char buffer[MAXLEN];
    FILE *fp;
    fp = fopen(FILEPATH, "r");
    if(fp == nullptr){
        perror("Cannot open file!");
        return(-1);
    }

    assignLines();

    int count = 0;
    int count_for_assert = 0;

    while(fgets(buffer, sizeof(buffer), fp) != nullptr){
        count++;
        if(buffer[0] == '#' || buffer[0] == '\n'){
            continue;
        } else{
            assert(strcmp(lines_to_check[count_for_assert], buffer));
            count_for_assert++;
            printf("Paragraph in line %d: ", count);
            puts(buffer);
        }
    }

    freeLines(lines_to_check);
    fclose(fp);
    return 0;
}
