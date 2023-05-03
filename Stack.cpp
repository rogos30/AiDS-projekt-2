#define _CRT_SECURE_NO_WARNINGS
using namespace std;
#include <iostream>
#include "Stack.h"

StackNode::StackNode(int y, int x, StackNode* next, StackNode* previous) {
	this->y = y;
	this->x = x;
	this->next = next;
	this->previous = previous;
}

StackNode::~StackNode() {}

int StackNode::GetX() {
	return x;
}

int StackNode::GetY() {
	return y;
}

StackNode* StackNode::GetNext() {
	return next;
}

StackNode* StackNode::GetPrevious() {
	return previous;
}

void StackNode::SetNext(StackNode* next) {
	this->next = next;
}

void StackNode::SetPrevious(StackNode* previous) {
	this->previous = previous;
}

Stack::Stack() {
	head = nullptr;
	tail = nullptr;
	size = 0;
}

Stack::Stack(const Stack& other) {
	head = nullptr;
	tail = nullptr;
	size = 0;
	StackNode* node = other.head;
	while (node != nullptr) {
		Add(node->GetX(), node->GetY());
		node = node->GetNext();
	}
}

Stack::~Stack() {
	StackNode* node = head;
	while (node != nullptr) {
		StackNode* next = node->GetNext();
		delete node;
		node = next;
	}
}

void Stack::Add(int y, int x) {
	//INSERTING A NEW CONNECTION
	if (head == nullptr) {
		head = new StackNode(y, x, nullptr, nullptr);
		tail = head;
	}
	else {
		head = new StackNode(y, x, head, nullptr);
		head->GetNext()->SetPrevious(head);
	}
	size++;
	return;
}

/*
void LinkedList::Remove(Organism* organism) {
	Node* node = head;
	Node* prev = nullptr;
	while (node != nullptr) {
		if (node->GetOrganism() == organism) {
			if (prev == NULL) {
				RemoveHead();
			}
			else if (node->GetNext() == NULL) {
				RemoveTail();
			}
			else {
				prev->SetNext(node->GetNext());
				//delete node;
				size--;
			}
			return;
		}
		prev = node;
		node = node->GetNext();
	}
}*/

void Stack::Remove(StackNode* node) {
	StackNode* current = head;
	while (current != nullptr) {
		if (current == node) {
			if (current->GetPrevious() == nullptr) {
				RemoveHead();
			}
			else if (current->GetNext() == nullptr) {
				RemoveTail();
			}
			else {
				current->GetPrevious()->SetNext(current->GetNext());
				delete current;
				size--;
			}
			return;
		}
		current = current->GetNext();
	}
}

void Stack::RemoveHead() {
	if (head != nullptr) {
		StackNode* node = head;
		head = head->GetNext();
		if (head == nullptr) {
			tail = nullptr;
		}
		else {
			head->SetPrevious(nullptr);
		}
		delete node;
		size--;
	}
}

void Stack::RemoveTail() {
	if (tail != nullptr) {
		StackNode* node = tail;
		tail = tail->GetPrevious();
		if (tail == nullptr) {
			head = nullptr;
		}
		else {
			tail->SetNext(nullptr);
		}
		delete node;
		size--;
	}
}

StackNode* Stack::GetHead() {
	return head;
}

StackNode* Stack::GetTail() {
	return tail;
}

int Stack::GetSize() {
	return size;
}

void Stack::Print() {
	StackNode* node = head;
	cout << "Roads: " << size << endl;
	while (node != nullptr) {
		cout << "x: " << node->GetX() << " y: " << node->GetY() << endl;
		node = node->GetNext();
	}
	cout << endl;
}