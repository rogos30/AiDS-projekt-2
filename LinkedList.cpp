#define _CRT_SECURE_NO_WARNINGS
using namespace std;
#include <iostream>
#include "LinkedList.h"

Node::Node(char* from, char* to, int length, Node* next) {
	strcpy(this->from, from);
	strcpy(this->to, to);
	this->length = length;
	this->next = next;
}

Node::~Node() {}

char* Node::GetFrom() {
	return from;
}

char* Node::GetTo() {
	return to;
}

int Node::GetLength() {
	return length;
}

Node* Node::GetNext() {
	return next;
}

void Node::SetNext(Node* next) {
	this->next = next;
}

LinkedList::LinkedList() {
	head = nullptr;
	tail = nullptr;
	size = 0;
}

LinkedList::~LinkedList() {
	while (head != nullptr) {
		RemoveHead();
	}
}

void LinkedList::Add(char* from, char* to, int length) {
	Node* node = head;
	if (head == nullptr) {
		head = new Node(from, to, length, nullptr);
		tail = head;
		size++;
		return;
	}
	else {
		head = new Node(from, to, length, node);
		size++;
		return;
	}
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

void LinkedList::Remove(Node* node) {
	Node* prev = nullptr;
	Node* current = head;
	while (current != nullptr) {
		if (current == node) {
			if (prev == nullptr) {
				RemoveHead();
			}
			else if (current->GetNext() == nullptr) {
				RemoveTail();
			}
			else {
				prev->SetNext(current->GetNext());
				delete current;
				size--;
			}
			return;
		}
		prev = current;
		current = current->GetNext();
	}
}

void LinkedList::RemoveHead() {
	if (head != nullptr) {
		Node* node = head;
		head = head->GetNext();
		//delete node;
		size--;
	}
}

void LinkedList::RemoveTail() {
	if (tail != nullptr) {
		Node* node = head;
		Node* prev = NULL;
		while (node != NULL) {
			if (node->GetNext() == NULL) {
				if (prev == NULL) {
					head = NULL;
					tail = NULL;
				}
				else {
					prev->SetNext(NULL);
					tail = prev;
				}
				//delete node;
				size--;
				return;
			}
			prev = node;
			node = node->GetNext();
		}
	}
}

Node* LinkedList::GetHead() {
	return head;
}

Node* LinkedList::GetTail() {
	return tail;
}


int LinkedList::GetSize() {
	return size;
}


void LinkedList::Print() {
	Node* node = head;
	cout << "Roads: " << size << endl;
	while (node != nullptr) {
		cout << "from: " << node->GetFrom() << " to: " << node->GetTo() << " length: " << node->GetLength() << endl;
		node = node->GetNext();
	}
	cout << endl;
}