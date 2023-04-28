#pragma once

using namespace std;

#define SMALL_BUFFER_SIZE 8
#define BUFFER_SIZE 1024

class AdjacencyNode {
	char destination[BUFFER_SIZE];
	int length;
	AdjacencyNode* next;
public:
	AdjacencyNode(char* destination, int length, AdjacencyNode* next);
	~AdjacencyNode();
	char* GetDestination();
	int GetLength();
	void SetLength(int length);
	AdjacencyNode* GetNext();
	void SetNext(AdjacencyNode* next);
};

class AdjacencyList {
	AdjacencyNode* head;
	AdjacencyNode* tail;
	int size;
public:
	AdjacencyList();
	~AdjacencyList();
	void Add(char* destination, int length);
	//void Remove(Organism* organism);
	void Remove(AdjacencyNode* node);
	void RemoveHead();
	void RemoveTail();
	AdjacencyNode* GetHead();
	AdjacencyNode* GetTail();
	AdjacencyNode* FindWith(char* destination);
	int GetSize();
	void Print();
};
