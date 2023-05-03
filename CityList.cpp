#define _CRT_SECURE_NO_WARNINGS
using namespace std;
#include <iostream>
#include "CityList.h"

class AdjacencyList;

CityNode::CityNode(char* name, int locationY, int locationX, CityNode* next) {
	strcpy(this->name, name);
	this->next = next;
	this->locationY = locationY;
	this->locationX = locationX;
	neighbours = new AdjacencyList();
}

CityNode::CityNode(int locationY, int locationX, CityNode* next) {
	strcpy(this->name, "");
	this->next = next;
	this->locationY = locationY;
	this->locationX = locationX;
	neighbours = new AdjacencyList();
}

CityNode::~CityNode() {}

char* CityNode::GetName() {
	return name;
}

CityNode* CityNode::GetNext() {
	return next;
}

int CityNode::GetLocationX() {
	return locationX;
}

int CityNode::GetLocationY() {
	return locationY;
}

void CityNode::SetNext(CityNode* next) {
	this->next = next;
}

AdjacencyList* CityNode::GetNeighbours() {
	return neighbours;
}

CityList::CityList() {
	head = nullptr;
	tail = nullptr;
	size = 0;
}

CityList::~CityList() {
	CityNode* node = head;
	while (node != nullptr) {
		CityNode* next = node->GetNext();
		delete node;
		node = next;
	}
}

void CityList::Add(char* name, int locationY, int locationX) {
	if (FindWith(name) != nullptr) {
		return;
	}
	if (head == nullptr) {
		head = new CityNode(name, locationY, locationX, nullptr);
		tail = head;
	}
	else {
		head = new CityNode(name, locationY, locationX, head);
	}
	//cout << "Added city: " << name << " at: " << locationY << " " << locationX << endl;
	size++;
	return;
}

void CityList::Add(int locationY, int locationX) {
	if (head == nullptr) {
		head = new CityNode(locationY, locationX, nullptr);
		tail = head;
	}
	else {
		head = new CityNode(locationY, locationX, head);
	}
	//cout << "Added city with no name at: " << locationY << " " << locationX << endl;
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

void CityList::Remove(CityNode* node) {
	CityNode* prev = nullptr;
	CityNode* current = head;
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

void CityList::RemoveHead() {
	if (head != nullptr) {
		head = head->GetNext();
		size--;
	}
}

void CityList::RemoveTail() {
	if (tail != nullptr) {
		CityNode* node = head;
		CityNode* prev = NULL;
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

CityNode* CityList::GetHead() {
	return head;
}

CityNode* CityList::GetTail() {
	return tail;
}

CityNode* CityList::GetAtPos(int position) {
	if (position >= size) {
		return nullptr;
	}
	CityNode* node = head;
	for (int i = 0; i < position; i++) {
		node = node->GetNext();
	}
	return node;
}

CityNode* CityList::FindWith(char* name) {
	CityNode* node = head;
	while (node != nullptr) {
		if (strcmp(node->GetName(), name) == 0) {
			return node;
		}
		node = node->GetNext();
	}
	return nullptr;
}

int CityList::GetSize() {
	return size;
}

void CityList::Print() {
	CityNode* node = head;
	cout << "Cities: " << size << endl;
	while (node != nullptr) {
		cout << " city name: " << node->GetName() << " ";
		if (node->GetNeighbours() != nullptr) node->GetNeighbours()->Print();
		cout << endl;
		node = node->GetNext();
	}
	cout << endl;
}