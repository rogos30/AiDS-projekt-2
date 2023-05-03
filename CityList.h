#pragma once
#include "AdjacencyList.h"

using namespace std;

class AdjacencyList;

#define SMALL_BUFFER_SIZE 8
#define BUFFER_SIZE 1024

class CityNode {
	char name[BUFFER_SIZE];
	int locationX;
	int locationY;
	AdjacencyList* neighbours;
	CityNode* next;
public:
	CityNode(char* name, int locationY, int locationX, CityNode* next);
	CityNode(int locationY, int locationX, CityNode* next);
	~CityNode();
	char* GetName();
	CityNode* GetNext();
	int GetLocationX();
	int GetLocationY();
	void SetNext(CityNode* next);
	AdjacencyList* GetNeighbours();
};

class CityList {
	CityNode* head;
	CityNode* tail;
	int size;
public:
	CityList();
	~CityList();
	void Add(char* name, int locationY, int locationX);
	void Add(int locationY, int locationX);
	//void Remove(Organism* organism);
	void Remove(CityNode* node);
	void RemoveHead();
	void RemoveTail();
	CityNode* GetHead();
	CityNode* GetTail();
	CityNode* GetAtPos(int position);
	CityNode* FindWith(char* name);
	int GetSize();
	void Print();
};
