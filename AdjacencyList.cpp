#define _CRT_SECURE_NO_WARNINGS
using namespace std;
#include <iostream>
#include "AdjacencyList.h"

AdjacencyNode::AdjacencyNode(char* destination, int length, AdjacencyNode* next) {
	strcpy(this->destination, destination);
	this->length = length;
	this->next = next;
}

AdjacencyNode::~AdjacencyNode() {}

char* AdjacencyNode::GetDestination() {
	return destination;
}

int AdjacencyNode::GetLength() {
	return length;
}

void AdjacencyNode::SetLength(int length) {
	this->length = length;
}

AdjacencyNode* AdjacencyNode::GetNext() {
	return next;
}

void AdjacencyNode::SetNext(AdjacencyNode* next) {
	this->next = next;
}

AdjacencyList::AdjacencyList() {
	head = nullptr;
	tail = nullptr;
	size = 0;
}

AdjacencyList::~AdjacencyList() {
	while (head != nullptr) {
		RemoveHead();
	}
}

void AdjacencyList::Add(char* destination, int length) {
	AdjacencyNode* node = FindWith(destination);
	if (node != nullptr) {
		//FOUND A NODE WITH THE SAME DESTINATION
		if (node->GetLength() > length) {
			//AND A SHORTER LENGTH
			node->SetLength(length);
			return;
		}
	}
	else {
		//INSERTING A NEW CONNECTION
		node = head;
		if (head == nullptr) {
			head = new AdjacencyNode(destination, length, nullptr);
			tail = head;
			size++;
			return;
		}
		else {
			head = new AdjacencyNode(destination, length, node);
			size++;
			return;
		}
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

void AdjacencyList::Remove(AdjacencyNode* node) {
	AdjacencyNode* prev = nullptr;
	AdjacencyNode* current = head;
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

void AdjacencyList::RemoveHead() {
	if (head != nullptr) {
		AdjacencyNode* node = head;
		head = head->GetNext();
		//delete node;
		size--;
	}
}

void AdjacencyList::RemoveTail() {
	if (tail != nullptr) {
		AdjacencyNode* node = head;
		AdjacencyNode* prev = NULL;
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

AdjacencyNode* AdjacencyList::GetHead() {
	return head;
}

AdjacencyNode* AdjacencyList::GetTail() {
	return tail;
}

AdjacencyNode* AdjacencyList::GetAtPos(int position) {
	if (position >= size) {
		return nullptr;
	}
	AdjacencyNode* node = head;
	for (int i = 0; i < position; i++) {
		node = node->GetNext();
	}
	return node;
}

AdjacencyNode* AdjacencyList::FindWith(char* destination) {
	AdjacencyNode* node = head;
	while (node != nullptr) {
		if (strcmp(node->GetDestination(), destination) == 0) {
			return node;
		}
		node = node->GetNext();
	}
	return nullptr;
}

int AdjacencyList::GetSize() {
	return size;
}


void AdjacencyList::Print() {
	AdjacencyNode* node = head;
	cout << "Roads: " << size << endl;
	while (node != nullptr) {
		cout << "\t to: " << node->GetDestination() << ", length: " << node->GetLength() << endl;
		node = node->GetNext();
	}
}