#define _CRT_SECURE_NO_WARNINGS
using namespace std;
#include <iostream>
#include "LinkedList.h"

Node::Node(char* name, Node* next) {
	strcpy(this->name, name);
	strcpy(this->previousName, "");
	this->distance = 1000000;
	this->visited = false;
	this->next = next;
}

Node::~Node() {}

char* Node::GetName() {
	return name;
}

char* Node::GetPreviousName() {
	return previousName;
}

void Node::SetPreviousName(char* previousName) {
	strcpy(this->previousName, previousName);
}

int Node::GetDistance() {
	return distance;
}

void Node::SetDistance(int distance) {
	this->distance = distance;
}

bool Node::GetVisited() {
	return visited;
}

void Node::SetVisited(bool visited) {
	this->visited = visited;
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

void LinkedList::Add(char* name) {
	//INSERTING A NEW CONNECTION
	Node* node = head;
	if (head == nullptr) {
		head = new Node(name, nullptr);
		tail = head;
		size++;
		return;
	}
	else {
		head = new Node(name, node);
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

Node* LinkedList::FindWith(char* name) {
	Node* node = head;
	while (node != nullptr) {
		if (strcmp(node->GetName(), name) == 0) {
			return node;
		}
		node = node->GetNext();
	}
	return nullptr;
}

Node* LinkedList::FindClosestUnvisited() {
	Node* node = head;
	int min = 1000000;
	while (node != nullptr) {
		if (node->GetVisited() == false && node->GetDistance() < min) {
			min = node->GetDistance();
		}
		node = node->GetNext();
	}

	node = head;
	while (node != nullptr) {
		if (node->GetDistance() == min && node->GetVisited() == false) {
			return node;
		}
		node = node->GetNext();
	}
	return nullptr;
}

int LinkedList::GetSize() {
	return size;
}


void LinkedList::Print() {
	Node* node = head;
	cout << "Roads: " << size << endl;
	while (node != nullptr) {
		cout << "name: " << node->GetName() << " prev name: " << node->GetPreviousName() << " distance: " << node->GetDistance() << endl;
		node = node->GetNext();
	}
	cout << endl;
}