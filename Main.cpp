
//---------------------------------------------------------------//
////														   ////
//////				  	  Michael Cu						 //////
///////		 Introduction to Artificial Intelligence	   ////////
////////					CS461					       ////////
////////				  2/8/2019					         //////
/////					  									   ////
//---------------------------------------------------------------//


#include <string>
#include <iostream>
#include <fstream>
#include <queue>
using namespace std;

//Outer Bounds for Matrix
int row[] = { 1,0,-1,0 };
int col[] = { 0,1,0,-1 };

struct Node {

	Node* parent;

	//Matrix holding current puzzle
	string matrix[3][3];

	//E's Coordinate
	int x, y;

	//Current Moves
	int gScore;

	//Tiles not in Order
	int hScore;
};

Node* newNode(Node* parent, string matrix[3][3], string x, string y, string swappedX, string swappedY, int hScore) {
	
	Node* node = new Node;

	node->parent = parent;

	//Transfer parent's data to node
	node->x = parent->x;
	node->y = parent->y;
	node->matrix[3][3] = parent->matrix[3][3];


	return node;
}

//Checks if a move doesn't go out of bounds in the matrix
bool validMove(int x, int y) {
	return(x >= 0 && y >= 0 && x <= 3 && y <= 3);
}


//Calculates the cost of a given matrix to solve the puzzle
//Returns the Cost
int calcCost(string child[3][3], string goal[3][3]) {

	int cost = 0;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (child[i][j] != goal[i][j]) {
				cost++;
			}
		}
	}
	return cost;

}

//
//
void solvePuzzle(string start[3][3], string goal[3][3], int x, int y) {

	std::priority_queue<Node*, vector<Node*>> pqueue;

	//Initial node
	Node* parent = newNode(NULL, start, std::to_string(x), std::to_string(y), std::to_string(x), std::to_string(y), 0);
	parent->hScore = calcCost(start, goal );

	pqueue.push(parent);


	//Chooses best/most efficient node from children
	while (!pqueue.empty()) {

		Node* minNode = pqueue.top();

		pqueue.pop();

		for (int i = 0; i < 4; i++) {
			if (validMove(parent->x,parent->y)) {
				Node* child = newNode(parent, parent->matrix, std::to_string(parent->x), std::to_string(parent->y), std::to_string(parent->x) + row[i], std::to_string(parent->y) + column[i]);
				child->hScore = calcCost(child->matrix, goal);
				pqueue.push(child);
			}
		}


	}

}


int main() {

	//Opening file
	fstream puzzleFile;
	puzzleFile.open("prog1_input.txt");


	//Checks if file reading fails
	if (puzzleFile.fail()) {
		cout << "Couldn't find file / Invalid File Name!";
		getchar();
		return 1;
	}
	else {
		cout << "Hi!";
	}

	//Number of Puzzles
	string n;

	//file iterator
	int iter;

	//"Number" in matrix
	string number;


	//Read number of puzzles from file
	puzzleFile >> n;

	//
	string E;

	//
	string start[3][3];




	string goal[3][3]{


		{std::to_string(1)	,		std::to_string(2)	,		std::to_string(3)},
		{std::to_string(4)	,		std::to_string(5)	,		std::to_string(6)},
		{std::to_string(7)	,		std::to_string(8)	,						 E}

	};

	for (int k = 0; k < std::stoi(n); k++) {

		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				puzzleFile >> number;
				start[i][j] = number;
			}
		}
		solvePuzzle();

	}




	getchar();
	puzzleFile.close();
	return 0;
}
