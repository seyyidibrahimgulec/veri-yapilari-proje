#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BUFFER_SIZE 1024
#define FILE_NAME_SIZE 20
#define WORD_SIZE 6
#define QUEUE_SIZE 1000

typedef struct Queue {
    int arr[QUEUE_SIZE];
    int rear;
}Queue;

char** createWordList(int*);
void printWordList(char**, int);
int** createAdjacencyMatrix(char**, int);
int isConnected(char**, int**, int, char*, char*);
Queue* createQueue();
int isEmpty(Queue*);
int isFull(Queue*);
int enqueue(Queue*, int);
int dequeue(Queue*);


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
    if(fp == NULL) {
        printf("Error opening file.\n");
        exit(-2);
    }
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
        *(wordList[i]+ 5) = '\0';
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

int isConnected(char **wordList, int **adjacencyMatrix, int length, char *word1, char *word2) {
    int i;
    int indexWord1;
    int indexWord2;

    i=0;
    while(i < length && strcmp(wordList[i], word1)) {
        i++;
    }
    indexWord1 = i;
    if(indexWord1 == length) {
        printf("%s not found!\n", word1);
        exit(-3);
    }
    i=0;
    while(i < length && strcmp(wordList[i], word2)) {
        i++;
    }
    indexWord2 = i;
    if(indexWord2 == length) {
        printf("%s not found!\n", word2);
        exit(-3);
    }
    if(adjacencyMatrix[indexWord1][indexWord2]) {
        printf("Baglanti var.\n");
        return 1;
    }
    printf("Baglanti yok.\n");
    return 0;
}

Queue* createQueue() {
    Queue *queue;
    queue = (Queue*) malloc(sizeof(Queue));
    if(queue == NULL) {
        printf("Allocation error.\n");
        exit(-1);
    }
    queue->rear = 0;
    return queue;
}

int isEmpty(Queue *queue) {
    if(queue->rear == 0) {
        printf("Queue is empty\n");
        return 1;
    }
    return 0;
}
int isFull(Queue *queue) {
    if(queue->rear == QUEUE_SIZE) {
        printf("Queue is full.\n");
        return 1;
    }
    return 0;
}

int enqueue(Queue *queue, int value) {
    if(!isFull(queue)) {
        queue->arr[queue->rear] = value;
        queue->rear++;
        return 1;
    }
    return 0;
}
int dequeue(Queue *queue) {
    int i;
    int value;
    if(!isEmpty(queue)) {
        value = queue->arr[0];
        for(i=0; i < queue->rear; i++) {
            queue->arr[i-1] = queue->arr[i];
        }
        queue->rear--;
        return value;
    }
    return -1;
}