#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include "LinkedList.h"
#include "CityList.h"

using namespace std;

#define HASH_TABLE_SIZE 13
#define BUFFER_SIZE 1024

void clearCharArray(char* array) {
	for (int i = 0; i < BUFFER_SIZE; i++) {
		array[i] = '\0';
	}
}

void resetRoadMap(int** roadMap, int sizeY, int sizeX) {
	for (int i = 0; i < sizeY; i++) {
		for (int j = 0; j < sizeX; j++) {
			roadMap[i][j] = -1;
		}
	}
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
	if ((ch >= 'A' && ch <= 'Z') || (ch >= '0' && ch <= '9')) {
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
					if (j - 1 >= 0 && isInCityName(map[i][j - 1])) {
						//A CORRECT CHARACTER FOUND TO THE LEFT OF THE ORIGINAL CHARACTER
						strcpy(name, readFromRight(map, i, j));
					}
					else if (j + 1 < sizeX && isInCityName(map[i][j + 1])) {
						//A CORRECT CHARACTER FOUND TO THE RIGHT OF THE ORIGINAL CHARACTER
						strcpy(name, readFromLeft(map, sizeX, i, j));
					}
					else {
						//A NAME WITH ONLY ONE CHARACTER
						name[0] = map[i][j];
					}
					return name;
				}
			}
		}
	}
}

int findShortestPath(int** roadMap, int sizeY, int sizeX, int y, int x) {
	int shortest = 1000000;
	for (int i = y - 1; i <= y + 1; i++) {
		if (i >= 0 && i < sizeY) {
			for (int j = x - 1; j <= x + 1; j++) {
				if (j >= 0 && j < sizeX) {
					if (roadMap[i][j] > 0 && roadMap[i][j] < shortest) {
						shortest = roadMap[i][j];
					}
				}
			}
		}
	}
	return shortest;
}


void findRoads(AdjacencyList *connections, int** roadMap, char** map, int sizeY, int sizeX, int y, int x, int length) {
	roadMap[y][x] = length;
	if (y - 1 >= 0 && roadMap[y - 1][x] == -1) {
		//GOING UP
		if (map[y - 1][x] == '#') {
			findRoads(connections, roadMap, map, sizeY, sizeX, y - 1, x, length + 1);
		}
		else if (map[y - 1][x] == '*') {
			char destinationCity[BUFFER_SIZE];
			clearCharArray(destinationCity);
			strcpy(destinationCity, readCity(map, sizeY, sizeX, y - 1, x));
			//cout << "found a destination: " << destinationCity;
			connections->Add(destinationCity, length);
		}
	}
	if (y + 1 < sizeY && roadMap[y + 1][x] == -1) {
		//GOING DOWN
		if (map[y + 1][x] == '#') {
			findRoads(connections, roadMap, map, sizeY, sizeX, y + 1, x, length + 1);
		}
		else if (map[y + 1][x] == '*') {
			char destinationCity[BUFFER_SIZE];
			clearCharArray(destinationCity);
			strcpy(destinationCity, readCity(map, sizeY, sizeX, y + 1, x));
			//cout << "found a destination: " << destinationCity;
			connections->Add(destinationCity, length);
		}
	}
	if (x - 1 >= 0 && roadMap[y][x - 1] == -1) {
		//GOING LEFT
		if (map[y][x - 1] == '#') {
			findRoads(connections, roadMap, map, sizeY, sizeX, y, x - 1, length + 1);
		}
		else if (map[y][x - 1] == '*') {
			char destinationCity[BUFFER_SIZE];
			clearCharArray(destinationCity);
			strcpy(destinationCity, readCity(map, sizeY, sizeX, y, x - 1));
			//cout << "found a destination: " << destinationCity;
			connections->Add(destinationCity, length);
		}
	}
	if (x + 1 < sizeX && roadMap[y][x + 1] == -1) {
		//GOING RIGHT
		if (map[y][x + 1] == '#') {
			findRoads(connections, roadMap, map, sizeY, sizeX, y, x + 1, length + 1);
		}
		else if (map[y][x + 1] == '*') {
			char destinationCity[BUFFER_SIZE];
			clearCharArray(destinationCity);
			strcpy(destinationCity, readCity(map, sizeY, sizeX, y, x + 1));
			//cout << "found a destination: " << destinationCity;
			connections->Add(destinationCity, length);
		}
	}
}

unsigned int hashFunction(char* name) {
	//BASED ON THE DJB2 ALGORITHM
	unsigned long hash = 5381;
	for (int i = 0; i < strlen(name); i++) {
		hash = ((hash << 5) + hash) + name[i]; //hash = hash*32 + hash + name[i] / hash*33 + name[i]
	}
	return hash;
}






int main()
{
	CityList* cities = new CityList[HASH_TABLE_SIZE];
	LinkedList connections;
	int sizeX, sizeY, flights;
	char ch, buffer[BUFFER_SIZE], bufferTest[BUFFER_SIZE];

	clearCharArray(buffer); clearCharArray(bufferTest);

	/*
	strcpy(buffer, "CHUJ");
	cities[0].Add(buffer);
	strcpy(buffer, "KURWA");
	cities[0].Add(buffer);
	strcpy(buffer, "PIZDA");
	cities[0].Add(buffer);
	cities[0].Print();
	clearCharArray(buffer);
	strcpy(buffer, "CHUJ");
	strcpy(buffer2, "MIASTO");
	cities[0].FindWith(buffer)->GetNeighbours()->Add(buffer2, 7);
	cities[0].Print();

	clearCharArray(buffer); clearCharArray(buffer2);
	strcpy(buffer, "CHUJ");
	strcpy(buffer2, "MIASTO 2");
	cities[0].FindWith(buffer)->GetNeighbours()->Add(buffer2, 2);

	clearCharArray(buffer); clearCharArray(buffer2);
	strcpy(buffer, "CHUJ");
	strcpy(buffer2, "MIASTO");
	cities[0].FindWith(buffer)->GetNeighbours()->Add(buffer2, 4);
	cities[0].Print();*/

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

	cout << "sizeX: " << sizeX << " sizeY: " << sizeY << "\n";


	//CREATING A MAP AND FILLING IT
	char **map = new char*[sizeY];
	int **roadMap = new int*[sizeY];
	for (int i = 0; i < sizeY; i++)
	{
		map[i] = new char[sizeX];
		roadMap[i] = new int[sizeX];
		cin >> map[i];
	}
	resetRoadMap(roadMap, sizeY, sizeX);


	//ANALYZING THE MAP
	//cout << "\nANALYZING THE MAP\n";
	for (int i = 0; i < sizeY; i++) {
		for (int j = 0; j < sizeX; j++) {
			if (map[i][j] == '*') {
				resetRoadMap(roadMap, sizeY, sizeX);
				clearCharArray(buffer);
				strcpy(buffer, readCity(map, sizeY, sizeX, i, j));
				cities[hashFunction(buffer) % HASH_TABLE_SIZE].Add(buffer);
				cout << "adding a city at cities[" << hashFunction(buffer) % HASH_TABLE_SIZE << "]\n";
				findRoads(cities[hashFunction(buffer) % HASH_TABLE_SIZE].FindWith(buffer)->GetNeighbours(), roadMap, map, sizeY, sizeX, i, j, 0);
				//printRoadMap(roadMap, sizeY, sizeX);
			}
		}
	}


	//READING THE FLIGHTS
	cin >> buffer;
	flights = atoi(buffer);
	
	char from[BUFFER_SIZE], to[BUFFER_SIZE];
	int length;
	for (int i = 0; i < flights; i++) {
		clearCharArray(from); clearCharArray(to);
		index = 0;
		while ((ch = getchar()) != ' ') {
			if (ch != '\n') {
				from[index] = ch;
				index++;
			}
		}
		from[index]='\0';
		cities[hashFunction(from) % HASH_TABLE_SIZE].Add(from);

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
		cities[hashFunction(from) % HASH_TABLE_SIZE].FindWith(from)->GetNeighbours()->Add(to, length);
		
	}

	cout << endl;
	for (int i = 0; i < HASH_TABLE_SIZE; i++) {
		cout << "cities[" << i << "] "; cities[i].Print();
	}

	delete map;
	delete roadMap;
	for (int i = 0; i < HASH_TABLE_SIZE; i++) {
		delete &cities[i];
	}
	//delete cities;

	return 0;
}