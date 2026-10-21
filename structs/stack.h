#ifndef STACK_H
#define STACK_H
#include <iostream>

struct StackNode {
    int value;
    StackNode* next;
};

struct Stack {
    StackNode* head;
};

void createStack(Stack* stack);
bool isEmptyStack(Stack* stack);
void pushStack(Stack* stack, const int& value);
void popStack(Stack& stack);
void printStack(const Stack& stack);
void deleteStack(Stack& stack);

#endif