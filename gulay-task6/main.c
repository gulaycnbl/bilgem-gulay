#include <stdio.h>
#include <stdlib.h>

#define FILE_NAME "task100.config"
#define MAX_LEN 300

int retrieved_number;

void get_number_from_first_line(FILE *fp){
    char buffer[MAX_LEN];
    fgets(buffer, sizeof(buffer), fp);
    retrieved_number = atoi(buffer);
    printf("%d, %s", retrieved_number, buffer);
}

int is_line_has_content(char buffer[]){
    return (buffer[0] != '#' && buffer[0] != '\n');
}

void read_file(FILE *fp){
    char buffer[MAX_LEN];
    int count = 0;
    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        if(is_line_has_content(buffer)){
            printf("%s\n", buffer);
            count++;
        }
    }
    printf("ret_num: %d, count: %d", retrieved_number, count);
}

int main() {
    FILE *fp = fopen(FILE_NAME, "r");
    if (fp == NULL){
        perror("Cannot open file!");
        return(-1);
    }
    get_number_from_first_line(fp);
    read_file(fp);

    fclose(fp);
    return 0;
}
