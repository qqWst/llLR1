#include "queue.h"
using namespace std;

void createQueue(Queue* queue) {
    queue->head = nullptr;
    queue->tail = nullptr;
}

bool isEmptyQueue(Queue* queue) {
    return queue->head == nullptr;
}

void pushQueue(Queue* queue, const int& value) {
    QueueNode* newNode = new QueueNode{value, nullptr};
    if (queue->tail == nullptr) {
        queue->head = newNode;
        queue->tail = newNode	;

        return;
    } else {
        queue->tail->next = newNode;
        queue->tail = newNode;
    }
}

void popQueue(Queue* queue, string& valueToDelete) {
	if (isEmptyQueue(queue)) {
		return;
	}
	QueueNode* nodeToDelete = queue->head;
	valueToDelete = nodeToDelete->value;
	queue->head = nodeToDelete->next;
	if (queue->head == nullptr) {
		queue->tail = nullptr;
	}

    delete nodeToDelete;
}

void printQueue(const Queue& queue) {
    if (queue.head == nullptr) {
        return;
    }
    for (const QueueNode* currentNode = queue.head; currentNode != nullptr; currentNode = currentNode->next) {
        cout << currentNode->value << " ";
    }
    cout << endl;
}

void freeQueue(Queue& queue) {
    while (queue.head != nullptr) {
        QueueNode* nodeToDelete = queue.head;
        queue.head = nodeToDelete->next;
        delete nodeToDelete;
    }
    queue.tail = nullptr;
}