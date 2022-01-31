#include <cstdio>
#include <cassert>
#include <cstdlib>
#include <cstring>

#define PRG1 "bchfvs dfcbhsdjfbsı bcdfızvbdı gvdbkbdn ngvffdıogn ngvkjxgbdkf rfg hı huı hukhgkdfhkgxdhn hjodghıdlxş gfhıoufhgodgtrh ghbr"
#define PRG2 "djfbsı bcdfızvbdı gvdbkbdn ngvffdıogn ngvkjxgbdkf rfg hıhuı hukhgkdfh bkbdn ngvffdıogn ngvkjhıhuı hukhgkdfh bkbjfbsı bcdfızvbdı gvdbkbdn ngvffdıogn ngvk"
#define PRG3 "jfbsı bcdfızvbdı gvdbkbdn ngvffdıogn ngvkjfbsı bcdfızvbdı gvdbkbdn ngvffdıogn ngvkjxgbdkf rfgıjisrejgesiı rjgıofvdşhsrb podgjudpfıohjb gtdtxhb hukhgkdfhkgxdhn hjodghıdlxş gfhıoufh"
#define PRG4 "fugvdhnd kfvnfızvbdı gvdbkbdn ngvffdıogn ngvkjxgbdkf rfg hıhuı hukhgkdfh bkbdn ngvffdıogn gvdbkbdn ngvffdıogn ngvkjxgbdkf rfghgkdfh bkbdn ngvffdıogn ngvkjhıhuı hukhgkdfh bkbjfbsı"

#define FILEPATH "/home/admin/Belgeler/GitHub/bilgem-gulay/gulay_task1/lorem.txt"
#define MAXLEN 350

int main() {
    char buffer[MAXLEN];
    FILE *fp;
    fp = fopen(FILEPATH, "r");
    if(fp == nullptr){
        perror("Cannot open file!");
        return(-1);
    }

    int count = 0;

    while(fgets(buffer, sizeof(buffer), fp) != nullptr){
        count++;
        if(buffer[0] == '#' || buffer[0] == '\n'){
            continue;
        } else{
            printf("Paragraph in line %d: ", count);
            puts(buffer);
        }
    }

    fclose(fp);
    return 0;
}
