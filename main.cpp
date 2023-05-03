#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include "LinkedList.h"
#include "CityList.h"
#include "Stack.h"

using namespace std;

#define HASH_TABLE_SIZE 101
#define BUFFER_SIZE 64

void clearCharArray(char* array) {
	for (int i = 0; i < BUFFER_SIZE; i++) {
		array[i] = '\0';
	}
}

void resetRoadMap(int** roadMap, int sizeY, int sizeX, int y, int x) {
	Stack toVisit;
	toVisit.Add(y, x);
	roadMap[y][x] = -1;

	while (toVisit.GetSize() != 0) {
		int y = toVisit.GetTail()->GetY();
		int x = toVisit.GetTail()->GetX();
		toVisit.RemoveTail();

		if (x - 1 >= 0 && roadMap[y][x - 1] != -1) {
			//GOING LEFT
			roadMap[y][x - 1] = -1;
			toVisit.Add(y, x - 1);
		}

		if (y - 1 >= 0 && roadMap[y - 1][x] != -1) {
			//GOING UP
			roadMap[y - 1][x] = -1;
			toVisit.Add(y - 1, x);
		}

		if (x + 1 < sizeX && roadMap[y][x + 1] != -1) {
			//GOING RIGHT
			roadMap[y][x + 1] = -1;
			toVisit.Add(y, x + 1);
		}

		if (y + 1 < sizeY && roadMap[y + 1][x] != -1) {
			//GOING DOWN
			roadMap[y + 1][x] = -1;
			toVisit.Add(y + 1, x);
		}
	}
	//printRoadMap(roadMap, sizeY, sizeX);
}

void printRoadMap(int** roadMap, int sizeY, int sizeX) {
	cout << "\nROAD MAP\n";
	for (int i = 0; i < sizeY; i++) {
		for (int j = 0; j < sizeX; j++) {
			cout << roadMap[i][j] << "\t";
		}
		cout << "\n";
	}
}

bool isInCityName(char ch) {
	if ((ch >= 'A' && ch <= 'Z') || (ch>='a' && ch<='z') || (ch >= '0' && ch <= '9')) {
		return true;
	}
	return false;
}

char* readFromRight(char** map, int y, int x) {
	char name[BUFFER_SIZE];
	clearCharArray(name);
	while (x>=0 && isInCityName(map[y][x])) {
		int len = strlen(name);
		for (int i = len; i >= 0; i--) {
			name[i + 1] = name[i];
		}
		name[0] = map[y][x];
		x--;
	}
	return name;
}

char* readFromLeft(char** map, int sizeX, int y, int x) {
	char name[BUFFER_SIZE];
	clearCharArray(name);
	while (x < sizeX && isInCityName(map[y][x])) {
		name[strlen(name)] = map[y][x];
		x++;
	}
	return name;
}

char* readCity(char** map, int sizeY, int sizeX, int y, int x) {
	char name[BUFFER_SIZE];
	clearCharArray(name);
	for (int i = y-1; i <= y+1; i++) {
		if (i >=0 && i < sizeY) {
			for (int j = x-1; j <= x+1; j++) {
				if (j >= 0 && j < sizeX && isInCityName(map[i][j])) {
					if (j - 1 >= 0 && isInCityName(map[i][j - 1]) && (j + 1 == sizeX || (j + 1 < sizeX && isInCityName(map[i][j + 1]) == false))) {
						//A CORRECT CHARACTER FOUND TO THE LEFT OF THE ORIGINAL CHARACTER AND THERE IS NO CORRECT CHARACTER TO THE RIGHT OF THE ORIGINAL CHARACTER
						strcpy(name, readFromRight(map, i, j));
					}
					else if (j + 1 < sizeX && isInCityName(map[i][j + 1]) && (j == 0 || (j - 1 >= 0 && isInCityName(map[i][j - 1]) == false))) {
						//A CORRECT CHARACTER FOUND TO THE RIGHT OF THE ORIGINAL CHARACTER AND THERE IS NO CORRECT CHARACTER TO THE LEFT OF THE ORIGINAL CHARACTER
						strcpy(name, readFromLeft(map, sizeX, i, j));
					}
					else if ((j + 1 == sizeX || (j + 1 < sizeX && isInCityName(map[i][j + 1]) == false)) || (j == 0 || (j - 1 >= 0 && isInCityName(map[i][j - 1]) == false))){
						//A NAME WITH ONLY ONE CHARACTER BECAUSE THERE IS NO CORRECT CHARACTER TO THE LEFT OR RIGHT OF THE ORIGINAL CHARACTER
						name[0] = map[i][j];
					}
					if (name[0] != '\0') {
						return name;
					}
				}
			}
		}
	}
	return nullptr;
}

int findShortestPath(int** roadMap, int sizeY, int sizeX, int y, int x) {
	int shortest = 1000000;

	if (y - 1 >= 0 && roadMap[y-1][x] >= 0 && roadMap[y-1][x] < shortest) {
		shortest = roadMap[y-1][x];
	}
	if (y + 1 < sizeY && roadMap[y + 1][x] >= 0 && roadMap[y + 1][x] < shortest) {
		shortest = roadMap[y+1][x];
	}
	if (x - 1 >= 0 && roadMap[y][x - 1] >= 0 && roadMap[y][x - 1] < shortest) {
		shortest = roadMap[y][x-1];
	}
	if (x + 1 < sizeX && roadMap[y][x + 1] >= 0 && roadMap[y][x + 1] < shortest) {
		shortest = roadMap[y][x+1];
	}

	return shortest;
}

unsigned int hashFunction(char* name) {
	//BASED ON THE DJB2 ALGORITHM
	unsigned long hash = 5381;
	for (int i = 0; i < strlen(name); i++) {
		hash = ((hash << 5) + hash) + name[i]; //hash = hash*32 + hash + name[i] / hash*33 + name[i]
	}
	return hash % HASH_TABLE_SIZE;
}

void findRoads(CityList* cities, char* startingCity, int** roadMap, char** map, int sizeY, int sizeX, int y, int x) {
	Stack toVisit;
	toVisit.Add(y, x);
	roadMap[y][x] = 0;
	//cout << startingCity << "\n";

	while (toVisit.GetSize() != 0) {
		int y = toVisit.GetTail()->GetY();
		int x = toVisit.GetTail()->GetX();
		toVisit.RemoveTail();

		if (x - 1 >= 0 && roadMap[y][x - 1] == -1) {
			//GOING LEFT
			if (map[y][x - 1] == '#') {
				//CONTINUATION OF A ROAD FOUND
				roadMap[y][x - 1] = findShortestPath(roadMap, sizeY, sizeX, y, x - 1) + 1;
				toVisit.Add(y, x - 1);
			}
			else if (map[y][x - 1] == '*') {
				//ANOTHER CITY FOUND
				char destinationCity[BUFFER_SIZE];
				clearCharArray(destinationCity);
				strcpy(destinationCity, readCity(map, sizeY, sizeX, y, x - 1));
				//cout << "found a destination: " << destinationCity;
				cities[hashFunction(startingCity)].FindWith(startingCity)->GetNeighbours()->Add(destinationCity, roadMap[y][x] + 1);
				cities[hashFunction(destinationCity)].Add(destinationCity, y, x - 1);
				cities[hashFunction(destinationCity)].FindWith(destinationCity)->GetNeighbours()->Add(startingCity, roadMap[y][x] + 1);
			}
		}

		if (y - 1 >= 0 && roadMap[y - 1][x] == -1) {
			//GOING UP
			if (map[y - 1][x] == '#') {
				//CONTINUATION OF A ROAD FOUND
				roadMap[y - 1][x] = findShortestPath(roadMap, sizeY, sizeX, y - 1, x) + 1;
				toVisit.Add(y - 1, x);
			}
			else if (map[y - 1][x] == '*') {
				//ANOTHER CITY FOUND
				char destinationCity[BUFFER_SIZE];
				clearCharArray(destinationCity);
				strcpy(destinationCity, readCity(map, sizeY, sizeX, y - 1, x));
				//cout << "found a destination: " << destinationCity;
				cities[hashFunction(startingCity)].FindWith(startingCity)->GetNeighbours()->Add(destinationCity, roadMap[y][x] + 1);
				cities[hashFunction(destinationCity)].Add(destinationCity, y - 1, x);
				cities[hashFunction(destinationCity)].FindWith(destinationCity)->GetNeighbours()->Add(startingCity, roadMap[y][x] + 1);
			}
		}

		if (x + 1 < sizeX && roadMap[y][x + 1] == -1) {
			//GOING RIGHT
			if (map[y][x + 1] == '#') {
				//CONTINUATION OF A ROAD FOUND
				roadMap[y][x + 1] = findShortestPath(roadMap, sizeY, sizeX, y, x + 1) + 1;
				toVisit.Add(y, x + 1);
			}
			else if (map[y][x + 1] == '*') {
				//ANOTHER CITY FOUND
				char destinationCity[BUFFER_SIZE];
				clearCharArray(destinationCity);
				strcpy(destinationCity, readCity(map, sizeY, sizeX, y, x + 1));
				//cout << "found a destination: " << destinationCity;
				cities[hashFunction(startingCity)].FindWith(startingCity)->GetNeighbours()->Add(destinationCity, roadMap[y][x] + 1);
				cities[hashFunction(destinationCity)].Add(destinationCity, y, x + 1);
				cities[hashFunction(destinationCity)].FindWith(destinationCity)->GetNeighbours()->Add(startingCity, roadMap[y][x] + 1);
			}
		}

		if (y + 1 < sizeY && roadMap[y + 1][x] == -1) {
			//GOING DOWN
			if (map[y + 1][x] == '#') {
				//CONTINUATION OF A ROAD FOUND
				roadMap[y + 1][x] = findShortestPath(roadMap, sizeY, sizeX, y + 1, x) + 1;
				toVisit.Add(y + 1, x);
			}
			else if (map[y + 1][x] == '*') {
				//ANOTHER CITY FOUND
				char destinationCity[BUFFER_SIZE];
				clearCharArray(destinationCity);
				strcpy(destinationCity, readCity(map, sizeY, sizeX, y + 1, x));
				//cout << "found a destination: " << destinationCity;
				cities[hashFunction(startingCity)].FindWith(startingCity)->GetNeighbours()->Add(destinationCity, roadMap[y][x] + 1);
				cities[hashFunction(destinationCity)].Add(destinationCity, y + 1, x);
				cities[hashFunction(destinationCity)].FindWith(destinationCity)->GetNeighbours()->Add(startingCity, roadMap[y][x] + 1);
			}
		}
		//printRoadMap(roadMap, sizeY, sizeX);
	}
}

void dijkstraAlgorithm(LinkedList dijkstraListA, CityList* cities, char* startingCity, char* destinationCity, int mode) {
	LinkedList dijkstraList(dijkstraListA);
	int unvisited = dijkstraList.GetSize();
	dijkstraList.FindWith(startingCity)->SetDistance(0);
	dijkstraList.FindWith(startingCity)->SetPreviousName(startingCity);
	//cout << "New function" << endl;
	while (unvisited > 0) {
		//cout << "Printing list: "; dijkstraList.Print();
		Node* current = dijkstraList.FindClosestUnvisited();
		//cout << "CURRENT: " << current->GetName() << endl;
		current->SetVisited(true);
		AdjacencyList currentNeighbours = *cities[hashFunction(current->GetName())].FindWith(current->GetName())->GetNeighbours();
		//cout << "Printing neighbours for " << startingCity << ": "; currentNeighbours.Print();
		for (int i = 0; i < currentNeighbours.GetSize(); i++) {
			if (dijkstraList.FindWith(currentNeighbours.GetAtPos(i)->GetDestination())->GetVisited() == false) {
				//ITERATING THROUGH UNVISITED NEIGHBOURS OF THE CURRENT NODE
				if (current->GetDistance() + currentNeighbours.GetAtPos(i)->GetLength() < dijkstraList.FindWith(currentNeighbours.GetAtPos(i)->GetDestination())->GetDistance()) {
					dijkstraList.FindWith(currentNeighbours.GetAtPos(i)->GetDestination())->SetDistance(current->GetDistance() + currentNeighbours.GetAtPos(i)->GetLength());
					dijkstraList.FindWith(currentNeighbours.GetAtPos(i)->GetDestination())->SetPreviousName(current->GetName());
				}
			}
		}
		unvisited--;
	}

	cout << dijkstraList.FindWith(destinationCity)->GetDistance();
	if (mode == 1) {
		char** path = new char*[dijkstraList.GetSize()];
		for (int i = 0; i < dijkstraList.GetSize() - 1; i++) {
			path[i] = new char[BUFFER_SIZE];
		}
		Node* current = dijkstraList.FindWith(destinationCity);
		int index = 0;
		while (strcmp(current->GetName(), current->GetPreviousName())!=0) {
			//cout << "current->GetName(): " << current->GetName() << " current->GetPreviousName()" << current->GetPreviousName() << endl;
			strcpy(path[index], current->GetName());
			current = dijkstraList.FindWith(current->GetPreviousName());
			index++;
		}
		for (int i = index-1; i > 0; i--) {
			cout << " " << path[i];
		}
		delete[] path;
	}
	cout << endl;
}






int main()
{
	CityList* cities = new CityList[HASH_TABLE_SIZE], *citiesList = new CityList;
	LinkedList dijkstraList;
	int sizeX, sizeY, information;
	char ch, buffer[BUFFER_SIZE], bufferTest[BUFFER_SIZE];

	clearCharArray(buffer); clearCharArray(bufferTest);


	//READING THE SIZE OF THE MAP
	int index = 0;
	while ((ch = getchar()) != ' ') {
		buffer[index] = ch;
		index++;
	}
	sizeX = atoi(buffer);

	clearCharArray(buffer);
	index = 0;
	while ((ch = getchar()) != '\n') {
		buffer[index] = ch;
		index++;
	}
	sizeY = atoi(buffer);



	//CREATING A MAP AND FILLING IT
	char **map = new char*[sizeY];
	int **roadMap = new int*[sizeY];
	for (int i = 0; i < sizeY; i++)
	{
		map[i] = new char[sizeX];
		roadMap[i] = new int[sizeX];
		cin >> map[i];
		for (int j = 0; j < sizeX; j++) {
			if (map[i][j] == '*') {
				citiesList->Add(i, j);
			}
			roadMap[i][j] = -1;
		}
	}


	//READING THE FLIGHTS
	cin >> buffer;
	information = atoi(buffer);

	char from[BUFFER_SIZE], to[BUFFER_SIZE];
	int length;
	for (int i = 0; i < information; i++) {
		//clearCharArray(from); clearCharArray(to);
		index = 0;
		while ((ch = getchar()) != ' ') {
			if (ch != '\n') {
				from[index] = ch;
				index++;
			}
		}
		from[index] = '\0';
		cities[hashFunction(from)].Add(from, 0, 0);

		index = 0;
		while ((ch = getchar()) != ' ') {
			to[index] = ch;
			index++;
		}
		to[index] = '\0';

		clearCharArray(buffer);
		index = 0;
		while ((ch = getchar()) != '\n') {
			buffer[index] = ch;
			index++;
		}
		length = atoi(buffer);
		cities[hashFunction(from)].FindWith(from)->GetNeighbours()->Add(to, length);
	}


	/*
	cout << endl;
	for (int i = 0; i < HASH_TABLE_SIZE; i++) {
		cout << "cities[" << i << "] "; cities[i].Print();
	}*/
	
	//cout << citiesList.GetSize() << endl;

	CityNode* node = citiesList->GetHead();
	while (node != nullptr) {
		strcpy(buffer, readCity(map, sizeY, sizeX, node->GetLocationY(), node->GetLocationX()));
		dijkstraList.Add(buffer);
		cities[hashFunction(buffer)].Add(buffer, node->GetLocationY(), node->GetLocationX());
		dijkstraList.Add(buffer);
		findRoads(cities, buffer, roadMap, map, sizeY, sizeX, node->GetLocationY(), node->GetLocationX());
		resetRoadMap(roadMap, sizeY, sizeX, node->GetLocationY(), node->GetLocationX());
		node = node->GetNext();
	}

	delete citiesList;
	
	/*cout << endl;
	for (int i = 0; i < HASH_TABLE_SIZE; i++) {
		cout << "cities[" << i << "] "; cities[i].Print();
	}*/

	//READING THE COMMANDS
	clearCharArray(buffer);
	cin >> buffer;
	information = atoi(buffer);
	for (int i = 0; i < information; i++) {
		//clearCharArray(from); clearCharArray(to);
		index = 0;
		while ((ch = getchar()) != ' ') {
			if (ch != '\n') {
				from[index] = ch;
				index++;
			}
		}
		from[index] = '\0';

		index = 0;
		while ((ch = getchar()) != ' ') {
			to[index] = ch;
			index++;
		}
		to[index] = '\0';

		clearCharArray(buffer);
		index = 0;
		while ((ch = getchar()) != '\n') {
			buffer[index] = ch;
			index++;
		}
		length = atoi(buffer);

		if (strcmp(from, to) == 0) {
			cout << "0\n";
		}
		else {
			//DIJKSTRA'S ALGORITHM
			dijkstraAlgorithm(dijkstraList, cities, from, to, length);
		}
	}

	delete[] map;
	for (int i=0; i<sizeY; i++) delete[] roadMap[i];
	delete[] roadMap;
	delete[] cities;


	return 0;
}