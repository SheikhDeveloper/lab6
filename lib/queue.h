#ifndef QUEUE_H
#define QUEUE_H

#include <stdio.h>
#include <stdlib.h>

#define TAKE_ERROR "Ошибка доступа к памяти при доставании элемента из очереди.\nЗавершение работы программы..." 

typedef struct Queue_elem {
    int priority;
    char elem;
} Node;

typedef struct Queue {
    Node **body;
    size_t size;
} Queue;

int put(Queue *q, char elem, int priority); 
char take_highest_priority(Queue *q, int *priority);
int del_item(Queue *q, size_t index);
void swap(Node **elem1, Node **elem2);
void heapify(Queue *q, int root);
int insert(Queue *q, Node *n);

#endif
