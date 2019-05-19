#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BUFFER_SIZE 1024
#define FILE_NAME_SIZE 20
#define WORD_SIZE 5

char** createWordList(int*);
void printWordList(char**, int);

int main (int argc, char *argv[]) {
    char **wordList;
    int length;
    wordList = createWordList(&length);
    printWordList(wordList, length);
    return 0;
}

char** createWordList(int *length) {
    FILE *fp;
    char buffer[BUFFER_SIZE];
    char *fileName;
    char **wordList;
    int count = 0;
    int i;
    fileName = (char*) malloc(FILE_NAME_SIZE * sizeof(char));
    printf("Enter word list file name :");
    scanf("%s", fileName);
    fp = fopen(fileName, "r");
    while(!feof(fp)) {
        fgets(buffer, BUFFER_SIZE, fp);
        count++;
    }
    *length = count;
    fseek(fp,0,SEEK_SET);
    wordList = (char**) malloc(count * sizeof(char*));
    for(i=0; i < count; i++) {
        wordList[i] = (char*) malloc(WORD_SIZE * sizeof(char));
    }
    i = 0;
    while(!feof(fp)) {
        fgets(buffer, BUFFER_SIZE, fp);
        strcpy(wordList[i], buffer);
        i++;
    }
    fclose(fp);
    free(fileName);
    return wordList;
}

void printWordList(char **wordList, int length) {
    int i;
    for(i=0; i < length; i++) {
        printf("%s", wordList[i]);
    }
    printf("\n");
}