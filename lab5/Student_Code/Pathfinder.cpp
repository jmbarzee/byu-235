#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <queue>
#include <vector>
#include <sstream>
#include "Pathfinder.h"
#include "Node3D.h"

using namespace std;

void Pathfinder::setMaze(char maze[5][5][5]) {
	for (int x = 0; x < 5; x++) {
		for (int y = 0; y < 5; y++) {
			for (int z = 0; z < 5; z++) {
				this->maze[x][y][z] = maze[x][y][z];
			}
		}
	}
}

Pathfinder::Pathfinder() {
	for (int x = 0; x < 5; x++) {
		for (int y = 0; y < 5; y++) {
			for (int z = 0; z < 5; z++) {
				maze[x][y][z] = '1';
			}
		}
	}
}

string Pathfinder::getMaze() {
	string mazeString = "";
	for (int x = 0; x < 5; x++) {
		for (int y = 0; y < 5; y++) {
			for (int z = 0; z < 5; z++) {
				mazeString += maze[x][y][z];
				if (z < 4)
					mazeString += ' ';
			}
			if (y < 4)
				mazeString += '\n';
		}
		if (x < 4)
			mazeString += "\n\n";
	}
	return mazeString;
}

void Pathfinder::createRandomMaze() {
	char maze[5][5][5];
	for (int x = 0; x < 5; x++) {
		for (int y = 0; y < 5; y++) {
			for (int z = 0; z < 5; z++) {
				if (rand() % 4 == 0)
					maze[x][y][z] = '0';
				else
					maze[x][y][z] = '1';
			}
		}
	}
	maze[0][0][0] = '1';
	maze[4][4][4] = '1';
	setMaze(maze);
}
bool Pathfinder::importMaze(string file_name) {
	ifstream infile;
	infile.open(file_name.c_str());
	if (infile.fail()) {
		return false;
	}
	char maze[5][5][5];
	char temp;
	for (int x = 0; x < 5; x++) {
		for (int y = 0; y < 5; y++) {
			for (int z = 0; z < 5; z++) {
				infile >> temp;
				if (infile.fail()) {
					return false;
				}
				if (temp != '0' && temp != '1') {
					return false;
				}
				maze[x][y][z] = temp;
			}
		}
	}
	infile >> temp;
	if (!infile.eof()) {
		return false;
	}
	if (maze[0][0][0] == '0') {
		return false;
	}
	if (maze[4][4][4] == '0') {
		return false;
	}
	setMaze(maze);
	return true;
}

/*
 * solveMaze
 *
 * Attempts to solve the current maze and returns a solution if one is found.
 *
 * A solution to a maze is a list of coordinates for the path from the entrance to the exit
 * (or an empty vector if no solution is found). This list cannot contain duplicates, and
 * any two consecutive coordinates in the list can only differ by 1 for only one
 * coordinate. The entrance cell (0, 0, 0) and the exit cell (4, 4, 4) should be included
 * in the solution-> Each string in the solution vector must be of the format "(x, y, z)",
 * where x, y, and z are the integer coordinates of a cell.
 *
 * Understand that most mazes will contain multiple solutions
 *
 * Returns:		vector<string>
 *				A solution to the current maze, or an empty vector if none exists
 */
Node3D* Pathfinder::find(deque<Node3D*> set, Node3D* tofind) {
	for (int i = 0; i < set.size(); i++) {
		if (set[i] == tofind)
			return set[i];
	}
	return NULL;
}

vector<string> Pathfinder::evaluateNode(Node3D maze[5][5][5], Node3D* crntN, deque<Node3D*>* closedSet) {
	if (crntN == &maze[4][4][4]) {
		vector<string> solution;
		stringstream ss;
		ss << '(' << crntN->getX() << ", " << crntN->getY() << ", " << crntN->getZ() << ')';
		solution.insert(solution.begin(), ss.str());
		return solution;
	}
	closedSet->push_back(crntN);
	deque<vector<string>> paths;
	int x = crntN->getX();
	int y = crntN->getY();
	int z = crntN->getZ();
	//cout << "Evaluating "  << crntN->getX() << crntN->getY() << crntN->getZ() << endl;
	if (x < 4) {
		Node3D* sideN = &maze[x + 1][y][z];
		if (sideN != find(*closedSet, sideN)) {
			if (sideN->isOpen()) {
				//GO EAST
				//cout << "   found possible path " << sideN->getX() << sideN->getY() << sideN->getZ() << ' ' << sideN->isOpen() << endl;
				paths.push_back(evaluateNode(maze,sideN,closedSet));
			} else {
				closedSet->push_back(sideN);
			}
		}
	}
	if (y < 4) {
		Node3D* sideN = &maze[x][y + 1][z];
		if (sideN != find(*closedSet, sideN)) {
			if (sideN->isOpen()) {
				//GO EAST
				//cout << "   found possible path " << sideN->getX() << sideN->getY() << sideN->getZ() << ' ' << sideN->isOpen() << endl;
				paths.push_back(evaluateNode(maze,sideN,closedSet));
			} else {
				closedSet->push_back(sideN);
			}
		}
	}
	if (z < 4) {
		Node3D* sideN = &maze[x][y][z + 1];
		if (sideN != find(*closedSet, sideN)) {
			if (sideN->isOpen()) {
				//GO EAST
				//cout << "   found possible path " << sideN->getX() << sideN->getY() << sideN->getZ() << ' ' << sideN->isOpen() << endl;
				paths.push_back(evaluateNode(maze,sideN,closedSet));
			} else {
				closedSet->push_back(sideN);
			}
		}
	}
	if (x > 0) {
		Node3D* sideN = &maze[x - 1][y][z];
		if (sideN != find(*closedSet, sideN)) {
			if (sideN->isOpen()) {
				//GO EAST
				//cout << "   found possible path " << sideN->getX() << sideN->getY() << sideN->getZ() << ' ' << sideN->isOpen() << endl;
				paths.push_back(evaluateNode(maze,sideN,closedSet));
			} else {
				closedSet->push_back(sideN);
			}
		}
	}
	if (y > 0) {
		Node3D* sideN = &maze[x][y - 1][z];
		if (sideN != find(*closedSet, sideN)) {
			if (sideN->isOpen()) {
				//GO EAST
				//cout << "   found possible path " << sideN->getX() << sideN->getY() << sideN->getZ() << ' ' << sideN->isOpen() << endl;
				paths.push_back(evaluateNode(maze,sideN,closedSet));
			} else {
				closedSet->push_back(sideN);
			}
		}
	}
	if (z > 0) {
		Node3D* sideN = &maze[x][y][z - 1];
		if (sideN != find(*closedSet, sideN)) {
			if (sideN->isOpen()) {
				//GO EAST
				//cout << "   found possible path " << sideN->getX() << sideN->getY() << sideN->getZ() << ' ' << sideN->isOpen() << endl;
				paths.push_back(evaluateNode(maze,sideN,closedSet));
			} else {
				closedSet->push_back(sideN);
			}
		}
	}
	int best = -1;
	for(int i = 0; i<paths.size(); i++) {
		if(paths[i].size() != 0) {
			if(best == -1) {
				best = i;
			} else if(paths[i].size() < paths[best].size()) {
				best = i;
			}
		}
	}
	if (best == -1) {
		vector<string> empty;
		return empty;
	}
	stringstream ss;
	ss << '(' << crntN->getX() << ", " << crntN->getY() << ", " << crntN->getZ() << ')';
	paths[best].insert(paths[best].begin(), ss.str());
	return paths[best];
}

vector<string> Pathfinder::solveMaze() {  // AWFUL RECURSIVE SEARCH
	Node3D maze[5][5][5];
	for (int x = 0; x < 5; x++) {
		for (int y = 0; y < 5; y++) {
			for (int z = 0; z < 5; z++) {
				if (this->maze[x][y][z] == '1') {
					maze[x][y][z].setOpen(true);
				}
				if (this->maze[x][y][z] == '0') {
					maze[x][y][z].setOpen(false);
				}
				maze[x][y][z].setXYZ(x, y, z);
			}
		}
	}
	return evaluateNode(maze, &maze[0][0][0], new deque<Node3D*>);
}
/*
vector<string> Pathfinder::solveMaze() {  // BEAUTIFUL A* ALGORITH
	Node3D maze[5][5][5];
	for (int x = 0; x < 5; x++) {
		for (int y = 0; y < 5; y++) {
			for (int z = 0; z < 5; z++) {
				if (this->maze[x][y][z] == '1') {
					maze[x][y][z].setOpen(true);
				}
				if (this->maze[x][y][z] == '0') {
					maze[x][y][z].setOpen(false);
				}
				maze[x][y][z].setXYZ(x, y, z);
			}
		}
	}
	//cout << getMaze();
	deque<Node3D*> openSet;
	deque<Node3D*> closedSet;
	maze[0][0][0].setCost(1);
	openSet.push_back(&maze[0][0][0]);
	while (openSet.size() > 0) {
		Node3D* crntN = openSet.front();
		//cout << "Evaluating "  << crntN->getX() << crntN->getY() << crntN->getZ() << endl;
		if (crntN == &maze[4][4][4]) {
			stringstream ss;
			vector <string> solution;
			while (crntN->getPrev() != NULL) {
				ss.str("");
				ss << '(' << crntN->getX() << ", " << crntN->getY() << ", " << crntN->getZ() << ')';
				solution.insert(solution.begin(), ss.str());
				crntN = crntN->getPrev();
			}
			ss.str("");
			ss << '(' << crntN->getX() << ", " << crntN->getY() << ", " << crntN->getZ() << ')';
			solution.insert(solution.begin(), ss.str());
			//cout << "am I really giving a solution?" << endl;
			return solution;
		}
		int x = crntN->getX();
		int y = crntN->getY();
		int z = crntN->getZ();
		if (x < 4) {
			Node3D* sideN = &maze[x + 1][y][z];
			if (sideN != find(closedSet, sideN)) {
				if (sideN->isOpen()) {
					//cout << "   found possible path " << sideN->getX() << sideN->getY() << sideN->getZ() << ' ' << sideN->isOpen() << endl;
					//GO EAST
					int cost = crntN->getCost() + 1;
					if (cost < sideN->getCost() || sideN != find(openSet, sideN)) {
						sideN->setPrev(crntN);
						sideN->setCost(cost);
						if (sideN != find(openSet, sideN)) {
							openSet.push_back(sideN);
						}
					}
				} else {
					closedSet.push_back(sideN);
				}
			}
		}
		if (y < 4) {
			Node3D* sideN = &maze[x][y + 1][z];
			if (sideN != find(closedSet, sideN)) {
				if (sideN->isOpen()) {
					//cout << "   found possible path " << sideN->getX() << sideN->getY() << sideN->getZ() << ' ' << sideN->isOpen() << endl;
					//GO SOUTH
					int cost = crntN->getCost() + 1;
					if (cost < sideN->getCost() || sideN != find(openSet, sideN)) {
						sideN->setPrev(crntN);
						sideN->setCost(cost);
						if (sideN != find(openSet, sideN)) {
							openSet.push_back(sideN);
						}
					}
				} else {
					closedSet.push_back(sideN);
				}
			}
		}
		if (z < 4) {
			Node3D* sideN = &maze[x][y][z + 1];
			if (sideN != find(closedSet, sideN)) {
				if (sideN->isOpen()) {
					//cout << "   found possible path " << sideN->getX() << sideN->getY() << sideN->getZ() << ' ' << sideN->isOpen() << endl;
					//GO UP
					int cost = crntN->getCost() + 1;
					if (cost < sideN->getCost() || sideN != find(openSet, sideN)) {
						sideN->setPrev(crntN);
						sideN->setCost(cost);
						if (sideN != find(openSet, sideN)) {
							openSet.push_back(sideN);
						}
					}
				} else {
					closedSet.push_back(sideN);
				}
			}
		}
		if (x > 0) {
			Node3D* sideN = &maze[x - 1][y][z];
			if (sideN != find(closedSet, sideN)) {
				if (sideN->isOpen()) {
					//cout << "   found possible path " << sideN->getX() << sideN->getY() << sideN->getZ() << ' ' << sideN->isOpen() << endl;
					//GO WEST
					int cost = crntN->getCost() + 1;
					if (cost < sideN->getCost() || sideN != find(openSet, sideN)) {
						sideN->setPrev(crntN);
						sideN->setCost(cost);
						if (sideN != find(openSet, sideN)) {
							openSet.push_back(sideN);
						}
					}
				} else {
					closedSet.push_back(sideN);
				}
			}
		}
		if (y > 0) {
			Node3D* sideN = &maze[x][y - 1][z];
			if (sideN != find(closedSet, sideN)) {
				if (sideN->isOpen()) {
					//cout << "   found possible path " << sideN->getX() << sideN->getY() << sideN->getZ() << ' ' << sideN->isOpen() << endl;
					//GO NORTH
					int cost = crntN->getCost() + 1;
					if (cost < sideN->getCost() || sideN != find(openSet, sideN)) {
						sideN->setPrev(crntN);
						sideN->setCost(cost);
						if (sideN != find(openSet, sideN)) {
							openSet.push_back(sideN);
						}
					}
				} else {
					closedSet.push_back(sideN);
				}
			}
		}
		if (z > 0) {
			Node3D* sideN = &maze[x][y][z - 1];
			if (sideN != find(closedSet, sideN)) {
				if (sideN->isOpen()) {
					//cout << "   found possible path " << sideN->getX() << sideN->getY() << sideN->getZ() << ' ' << sideN->isOpen() << endl;
					//GO DOWN
					int cost = crntN->getCost() + 1;
					if (cost < sideN->getCost() || sideN != find(openSet, sideN)) {
						sideN->setPrev(crntN);
						sideN->setCost(cost);
						if (sideN != find(openSet, sideN)) {
							openSet.push_back(sideN);
						}
					}
				} else {
					closedSet.push_back(sideN);
				}
			}
		}
		openSet.pop_front();
		closedSet.push_back(crntN);
		//SORT OPNESET HERE FOR ADDED SPEED
	}
	vector<string> empty;
	return empty;
}*/
