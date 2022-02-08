#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <pthread.h>
#include <unistd.h>

#define FILE_NAME "lorem.txt"
#define NUMBER_OF_PARAGRAPHS 12
#define NUMBER_OF_THREADS 4

char prg0[] = "Once when I was six years old I saw a magnificent picture in a book, called True Stories from Nature, about the primeval forest. It was a picture of a boa constrictor in the act of swallowing an animal. Here is a copy of the drawing.";
char prg1[] = "In the book it said: \"Boa constrictors swallow their prey whole, without chewing it. After that they are not able to move, and they sleep through the six months that they need for digestion. I pondered deeply, then, over the adventures of the jungle. And after some work with a colored pencil I succeeded in making my first drawing. My Drawing Number One. It looked something like this:";
char prg2[] = "I showed my masterpiece to the grown-ups, and asked them whether the drawing frightened them.";
char prg3[] = "But they answered: \"Frighten? Why should any one be frightened by a hat?\"";
char prg4[] = "My drawing was not a picture of a hat. It was a picture of a boa constrictor digesting an elephant. But since the grown-ups were not able to understand it, I made another drawing: I drew the inside of a boa constrictor, so that the grown-ups could see it clearly. They always need to have things explained. My Drawing Number Two looked like this:";
char prg5[] = "The grown-ups' response, this time, was to advise me to lay aside my drawings of boa constrictors, whether from the inside or the outside, and devote myself instead to geography, history, arithmetic, and grammar.";
char prg6[] = "That is why, at the age of six, I gave up what might have been a magnificent career as a painter. I had been disheartened by the failure of my Drawing Number One and my Drawing Number Two. Grown-ups never understand anything by themselves, and it is tiresome for children to be always and forever explaining things to them.";
char prg7[] = "So then I chose another profession, and learned to pilot airplanes. I have flown a little over all parts of the world; and it is true that geography has been very useful to me. At a glance I can distinguish China from Arizona. If one gets lost in the night, such knowledge is valuable.";
char prg8[] = "In the course of this life I have had a great many encounters with a great many people who have been concerned with matters of consequence.";
char prg9[] = "I have lived a great deal among grown-ups. I have seen them intimately, close at hand. And that hasn't much improved my opinion of them.";
char prg10[] = "Whenever I met one of them who seemed to me at all clear-sighted, I tried the experiment of showing him my Drawing Number One, which I have always kept. I would try to find out, so, if this was a person of true understanding. But, whoever it was, he, or she, would always say: \"That is a hat.\"";
char prg11[] = "Then I would never talk to that person about boa constrictors, or primeval forests, or stars. I would bring myself down to his level. I would talk to him about bridge, and golf, and politics, and neckties. And the grown-up would be greatly pleased to have met such a sensible man.";

const char *paragraphs[NUMBER_OF_PARAGRAPHS] = {
        prg0, prg1, prg2, prg3, prg4, prg5, prg6, prg7, prg8, prg9, prg10, prg11,
};

const int index_arr[NUMBER_OF_PARAGRAPHS] = {0, 10000, 20000, 30000, 40000, 50000, 60000, 70000, 80000, 90000, 100000, 110000};

pthread_mutex_t lock1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t lock2 = PTHREAD_MUTEX_INITIALIZER;

void read_and_assert_with_index(FILE *fp, char prg[], long index){
    unsigned long len_of_prg = strlen(prg);
    char buffer[len_of_prg + 1];

    fseek(fp, index, SEEK_SET);
    fgets(buffer, sizeof(buffer), fp);
    assert(!strcmp(prg, buffer));
    printf("The %lu indexed content of the file (%s) matches with the predefined content.\n", index, FILE_NAME);
}

void *thread_func(const int arr[]) {
    FILE *fp= fopen(FILE_NAME, "r+");
    if(fp == NULL){
        perror("Cannot open file to read! You can either provide an existing file and change the FILE_NAME, "
               "or run the custom_write_to_new_file() function once");
    }

    for(int i=0; i < NUMBER_OF_PARAGRAPHS / NUMBER_OF_THREADS; i++){
        int index = arr[i];
        pthread_mutex_lock(&lock1);
        printf("Inside the thread [%lu]: Prg %d - ", pthread_self(), index);
        read_and_assert_with_index(fp, paragraphs[index], index_arr[index]);
        pthread_mutex_unlock(&lock1);
    }

    fclose(fp);
    return NULL;
}

void *thread_func_parent(const int arr[]) {
    FILE *fp= fopen(FILE_NAME, "r+");
    if(fp == NULL){
        perror("Cannot open file to read! You can either provide an existing file and change the FILE_NAME, "
               "or run the custom_write_to_new_file() function once");
    }

    for(int i=0; i<3; i++){
        int index = arr[i];
        pthread_mutex_lock(&lock2);
        printf("Inside the thread [%lu]: Prg %d - ", pthread_self(), index);
        read_and_assert_with_index(fp, paragraphs[index], index_arr[index]);
        pthread_mutex_unlock(&lock2);
    }
    fclose(fp);
    return NULL;
}

int main() {
    FILE *fp= fopen(FILE_NAME, "r+");
    if(fp == NULL){
        perror("Cannot open file to read! You can either provide an existing file and change the FILE_NAME, "
               "or run the custom_write_to_new_file() function once");
    }

    int arr1[] = {0, 4, 8};
    int arr2[] = {1, 5, 9};
    int arr3[] = {2, 6, 10};
    int arr4[] = {3, 7, 11};

    pthread_t tid[4];

    if(fork()==0){

        pthread_create(&(tid[0]), NULL, (void *(*)(void *)) &thread_func, (void *)arr1);
        pthread_create(&(tid[1]), NULL, (void *(*)(void *)) &thread_func, (void *)arr2);

        pthread_join(tid[0], NULL);
        pthread_join(tid[1], NULL);
    }else{

        pthread_create(&(tid[2]), NULL, (void *(*)(void *)) &thread_func_parent, (void *)arr3);
        pthread_create(&(tid[3]), NULL, (void *(*)(void *)) &thread_func_parent, (void *)arr4);

        pthread_join(tid[2], NULL);
        pthread_join(tid[3], NULL);
    }

    fclose(fp);
    pthread_mutex_destroy(&lock1);
    pthread_mutex_destroy(&lock2);
    return 0;
}
