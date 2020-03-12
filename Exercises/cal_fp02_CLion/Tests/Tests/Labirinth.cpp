/*
 * labirinth.cpp
 */

#include "Labirinth.h"
#include <iostream>

using namespace std;

Labirinth::Labirinth(int values[10][10]) {
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 10; j++)
			labirinth[i][j] = values[i][j];

    initializeVisited();
}

void Labirinth::initializeVisited() {
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 10; j++)
			visited[i][j] = false;
}

void  Labirinth::printLabirinth() {
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++)
			cout << labirinth[i][j] << " ";

		cout << endl;
	}
}

bool Labirinth::findGoal(int x, int y) {
    if (!(x >= 0 && x <= 9 && y >= 0 && y <= 9) || visited[y][x])
        return false;

    visited[y][x] = true;

    if (labirinth[y][x] == 0)
        return false;

    if (labirinth[y][x] == 2)
        return true;

    return findGoal(x + 1, y) || findGoal(x - 1, y) || findGoal(x, y + 1) || findGoal(x, y - 1);
}


