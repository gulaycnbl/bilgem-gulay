#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

#define PRG1 "bchfvs dfcbhsdjfbsı bcdfızvbdı gvdbkbdn ngvffdıogn ngvkjxgbdkf rfg hı huı hukhgkdfhkgxdhn hjodghıdlxş gfhıoufhgodgtrh ghbr"
#define PRG2 "djfbsı bcdfızvbdı gvdbkbdn ngvffdıogn ngvkjxgbdkf rfg hıhuı hukhgkdfh bkbdn ngvffdıogn ngvkjhıhuı hukhgkdfh bkbjfbsı bcdfızvbdı gvdbkbdn ngvffdıogn ngvk"
#define PRG3 "jfbsı bcdfızvbdı gvdbkbdn ngvffdıogn ngvkjfbsı bcdfızvbdı gvdbkbdn ngvffdıogn ngvkjxgbdkf rfgıjisrejgesiı rjgıofvdşhsrb podgjudpfıohjb gtdtxhb hukhgkdfhkgxdhn hjodghıdlxş gfhıoufh"
#define PRG4 "fugvdhnd kfvnfızvbdı gvdbkbdn ngvffdıogn ngvkjxgbdkf rfg hıhuı hukhgkdfh bkbdn ngvffdıogn gvdbkbdn ngvffdıogn ngvkjxgbdkf rfghgkdfh bkbdn ngvffdıogn ngvkjhıhuı hukhgkdfh bkbjfbsı"

#define FILEPATH "./gulay_task2/lorem.txt"
#define MAXLEN 350
#define NUMOFLINES 5

char **lines_to_check = (char **)malloc(NUMOFLINES*sizeof(char*));


void assignLines(){
    /*for(int i=0; i<NUMOFLINES; i++){
        lines_to_check[i] = (char *)malloc(MAXLEN*sizeof(char));
    }*/
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
    if (fp == NULL) {
        perror("Cannot open file!");
        return (-1);
    }

    assignLines();

    int count = 0;
    int count_for_assert = 0;

    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        count++;
        if (buffer[0] == '#' || buffer[0] == '\n') {
            continue;
        } else {
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