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

#define FILENAME "lorem.txt"
#define MAXLEN 350

const char * myarray[]{
    PRG1,
    PRG2,
    PRG3,
    PRG4,
    PRG5,
    PRG6,
};

int main() {
    char buffer[MAXLEN];
    FILE *fp;
    fp = fopen(FILENAME, "r");
    if(fp == nullptr){
        perror("Cannot open file!");
        return(-1);
    }

    int count = 0;
    int count_for_assert = 0;

    while(fgets(buffer, sizeof(buffer), fp) != nullptr){
        count++;
        if(buffer[0] == '#' || buffer[0] == '\n'){
            continue;
        } else{
            assert(strcmp(myarray[count_for_assert], buffer));
            count_for_assert++;
            printf("Paragraph in line %d: ", count);
            puts(buffer);
        }
    }
    fclose(fp);
    return 0;
}
