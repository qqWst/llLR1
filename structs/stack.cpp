#include "stack.h"
using namespace std;

void createStack(Stack* stack) {
	stack->head = nullptr;
}

bool isEmptyStack(Stack* stack) {
	return stack-> head == nullptr;
}

void pushStack(Stack* stack, const int& value) {
	StackNode* newNode = new StackNode{value, nullptr};
	newNode->next = stack->head;
	stack->head = newNode;
}

void popStack(Stack& stack) {
	if (isEmptyStack(&stack)) {
		return;

	} else {
		StackNode* newHead = stack.head->next;
		delete stack.head;
		stack.head = newHead;
	}
}

void printStack(const Stack& stack) {
	if (stack.head == nullptr) {
		cout << "Стэк пуст." << endl;
		return;
	}
	for (const StackNode* currentNode = stack.head; currentNode != nullptr; currentNode = currentNode->next) {
		cout << currentNode->value << " ";
	}
	cout << endl;
}

void deleteStack(Stack& stack) {
	while (stack.head != nullptr) {
		StackNode* temp= stack.head;
		stack.head = temp->next;
		delete temp;
	}
}