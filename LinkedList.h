#pragma once


using namespace std;

#define SMALL_BUFFER_SIZE 8
#define BUFFER_SIZE 1024

class Node {
	char name[BUFFER_SIZE];
	char previousName[BUFFER_SIZE];
	int distance;
	bool visited;
	Node* next;
public:
	Node(char* name, Node* next);
	~Node();
	char* GetName();
	char* GetPreviousName();
	void SetPreviousName(char* previousName);
	int GetDistance();
	void SetDistance(int distance);
	bool GetVisited();
	void SetVisited(bool visited);
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
	void Add(char* name);
	//void Remove(Organism* organism);
	void Remove(Node* node);
	void RemoveHead();
	void RemoveTail();
	Node* GetHead();
	Node* GetTail();
	Node* FindWith(char* name);
	Node* FindClosestUnvisited();
	int GetSize();
	void Print();
};

