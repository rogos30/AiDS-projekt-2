#pragma once

using namespace std;

#define SMALL_BUFFER_SIZE 8
#define BUFFER_SIZE 1024

class StackNode {
	int y;
	int x;
	StackNode* next;
	StackNode* previous;
public:
	StackNode(int y, int x, StackNode* next, StackNode* previous);
	~StackNode();
	int GetX();
	int GetY();
	StackNode* GetNext();
	StackNode* GetPrevious();
	void SetNext(StackNode* next);
	void SetPrevious(StackNode* previous);
};

class Stack {
	StackNode* head;
	StackNode* tail;
	int size;
public:
	Stack();
	Stack(const Stack& other);
	~Stack();
	void Add(int y, int x);
	//void Remove(Organism* organism);
	void Remove(StackNode* node);
	void RemoveHead();
	void RemoveTail();
	StackNode* GetHead();
	StackNode* GetTail();
	int GetSize();
	void Print();
};


