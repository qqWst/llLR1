#ifndef QUEUE_H
#define QUEUE_H
#include <iostream>

struct QueueNode{
    std::string value;
    QueueNode* next;
};

struct Queue{
    QueueNode* head;
    QueueNode* tail;
};

void createQueue(Queue* queue);
bool isEmptyQueue(Queue* queue);
void pushQueue(Queue* queue, const std::string& value);
void popQueue(Queue* queue, std::string& valueToDelete);
void printQueue(const Queue& queue);
void freeQueue(Queue& queue);

#endif