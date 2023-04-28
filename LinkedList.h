#pragma once


using namespace std;

#define SMALL_BUFFER_SIZE 8
#define BUFFER_SIZE 1024

class Node {
	char from[BUFFER_SIZE];
	char to[BUFFER_SIZE];
	int length;
	Node* next;
public:
	Node(char* from, char* to, int length, Node* next);
	~Node();
	char* GetFrom();
	char* GetTo();
	int GetLength();
	void SetLength(int length);
	Node* GetNext();
	void SetNext(Node* next);
};

class LinkedList {
	Node* head;
	Node* tail;
	int size;
public:
	LinkedList();
	~LinkedList();
	void Add(char* from, char* to, int length);
	//void Remove(Organism* organism);
	void Remove(Node* node);
	void RemoveHead();
	void RemoveTail();
	Node* GetHead();
	Node* GetTail();
	Node* FindWith(char* from, char* to);
	int GetSize();
	void Print();
};

