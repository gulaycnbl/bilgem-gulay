#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_NAME "task100.config"
#define MAX_LEN 1500

int get_number_from_first_line(FILE *fp){
    char buffer[10];
    fgets(buffer, sizeof(buffer), fp);
    return atoi(buffer);
}

void read_file(FILE *fp){
    char buffer[MAX_LEN];
    int count = 0;
    fscanf(fp, "%200s %[\n\n]");
    //printf("ret_num: %d, count: %d", retrieved_number, count);
}

int main() {
    FILE *fp = fopen(FILE_NAME, "r");
    if (fp == NULL){
        perror("Cannot open file!");
        return(-1);
    }

    int num = get_number_from_first_line(fp);
    char line[MAX_LEN];
    fgets(line, sizeof line, fp);
    for(int i=0; i<num; i++){
        fscanf(fp, "%[^\n]\n", &line);
        printf("%s\n", line);
    }


    fclose(fp);
    return 0;
}
