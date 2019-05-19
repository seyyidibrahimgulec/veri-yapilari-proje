#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BUFFER_SIZE 1024
#define FILE_NAME_SIZE 20
#define WORD_SIZE 5

char** createWordList(int*);
void printWordList(char**, int);
int** createAdjacencyMatrix(char**, int);

int main (int argc, char *argv[]) {
    char **wordList;
    int length;
    int **adjacencyMatrix;
    wordList = createWordList(&length);
    adjacencyMatrix = createAdjacencyMatrix(wordList, length);
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
    if(fileName == NULL) {
        printf("Allocation error\n");
        exit(-1);
    }
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
    if(wordList == NULL) {
        printf("Allocation error\n");
        exit(-1);
    }
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

int** createAdjacencyMatrix(char **wordList, int length) {
    int **adjacencyMatrix;
    int i;
    int j;
    int k;
    int difLetterCount;
    adjacencyMatrix = (int**) malloc(length * sizeof(int*));
    if(adjacencyMatrix == NULL) {
        printf("Allocation error.\n");
        exit(-1);
    }
    for(i=0; i<length; i++) {
        adjacencyMatrix[i] = (int*) malloc(length * sizeof(int));
    }
    for(i=0; i<length; i++) {
        for(j=0; j<length; j++) {
            k=0;
            difLetterCount = 0;
            while(difLetterCount<2 && k < WORD_SIZE) {
                if(*(wordList[i]+k) != *(wordList[j]+k)) {
                    difLetterCount++;
                }
                k++;
            }
            if(difLetterCount == 1) {
                adjacencyMatrix[i][j] = 1;
            } else {
                adjacencyMatrix[i][j] = 0;
            }
        }
    }
    return adjacencyMatrix;
}