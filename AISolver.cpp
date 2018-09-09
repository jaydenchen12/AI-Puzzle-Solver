//============================================================================
// Name        : AISolver.cpp
// Author      : Jayden
// Description : AI Puzzle Solver Written in C++
//============================================================================
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <cstring>
#include <vector>
#include <utility>
#include <ctime>
#include "PuzzleMove.h"
using namespace std;

void loadGame(std::string filename);
void printGameState();
bool puzzleCheck(vector<vector<int> > input2dVector);
bool identicalCheck(vector<vector<int> > input2dVector1,
		vector<vector<int> > input2dVector2);
vector<vector<int> > normalize(vector<vector<int> > input2d);
vector<vector<int> > swapIdx(int idx1, int idx2, vector<vector<int> > input2dswap);
vector<vector<int> > cloneGameState(vector<vector<int> > input2dVector);
vector<pair<pair<vector<vector<int> >, vector<vector<int> > >, pair<vector<pair<int, string> >, pair<int, pair<int, string> > > > > expandNode(vector<vector<int> > input2dVector);
pair<int,int> breadthFirstSearch(vector<pair<pair<vector<vector<int> >, vector<vector<int> > >, pair<vector<pair<int, string> >, pair<int, pair<int, string> > > > > nodes);
pair<int,int> depthFirstSearch(vector<pair<pair<vector<vector<int> >, vector<vector<int> > >, pair<vector<pair<int, string> >, pair<int, pair<int, string> > > > > nodes);
pair<int, int> iterativeDeepeningSearch(vector<pair<pair<vector<vector<int> >, vector<vector<int> > >, pair<vector<pair<int, string> >, pair<int, pair<int, string> > > > > nodes);
pair<bool, pair<int,int> > iterRecursive(vector<pair<pair<vector<vector<int> >, vector<vector<int> > >, pair<vector<pair<int, string> >, pair<int, pair<int, string> > > > > nodes, int deep);
void randomWalk(vector<vector<int> > input2dVector, int n);
ifstream inputFile;
vector<vector<int> > gameState;
int row;
int column;
int main() {
	loadGame("SBP-level1.txt");
	printGameState();
	normalize(gameState);
	cout << "\nPart 1: Random Moves: \n";
	randomWalk(gameState, 3);
	pair<int,int> searchOut;
	clock_t begin = clock();
	cout << "\nPart 2: Breath First Search: \n";
	searchOut = breadthFirstSearch(expandNode(gameState));
	clock_t end = clock();
	double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
	cout << "Node Visited " << searchOut.first << ", Time " << elapsed_secs << " seconds, length "<< searchOut.second << "\n";
	begin = clock();
	cout << "\nPart 3: Depth First Search: \n";
	searchOut = depthFirstSearch(expandNode(gameState));
	end = clock();
	elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
	cout << "Node Visited " << searchOut.first << ", Time " << elapsed_secs << " seconds, length "<< searchOut.second << "\n";
	begin = clock();
	cout << "\nPart 4: Iterative Deepening Search: \n";
	searchOut = iterativeDeepeningSearch(expandNode(gameState));
	end = clock();
	elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
	cout << "Node Visited " << searchOut.first << ", Time " << elapsed_secs << " seconds, length "<< searchOut.second << "\n";
	return EXIT_SUCCESS;
}

void loadGame(std::string filename) {
	inputFile.open(filename);
}
void printGameState() {
	string line;

	if (inputFile.is_open()) {
		getline(inputFile, line, ',');
		row = stoi(line);
		getline(inputFile, line, ',');
		column = stoi(line);
		cout << row << ',' << column << ',';
		while (getline(inputFile, line)) {
			cout << line << '\n';
			vector<int> ints;
			stringstream ss(line);
			int n;
			char ch;
			while (ss >> n) {
				if (ss >> ch)
					ints.push_back(n);
				else
					ints.push_back(n);
			}
			gameState.push_back(ints);
		}
		inputFile.close();
	}
}
vector<vector<int> > cloneGameState(vector<vector<int> > input2dVector) {
	return input2dVector;
}
bool puzzleCheck(vector<vector<int> > input2dVector) {
	bool isComplete = false;
	for (int i = 0; i < input2dVector.size(); i++) {
		for (int j = 0; j < input2dVector[i].size(); j++) {
			if (input2dVector[i][j] != -1)
				isComplete = true;
			else
				return false;
		}
	}
	return isComplete;
}
bool identicalCheck(vector<vector<int> > input2dVector1,
		vector<vector<int> > input2dVector2) {
	bool isIdentical = false;
	for (int m = 0; m < input2dVector1.size(); m++) {
		for (int n = 0; n < input2dVector1[m].size(); n++) {
			if (input2dVector1[m][n] == input2dVector2[m][n])
				isIdentical = true;
			else
				return false;
		}
	}
	return isIdentical;
}
vector<vector<int> > normalize(vector<vector<int> > input2d) {
	int nextIdx = 3;
	for (int m = 0; m < input2d.size(); m++) {
		for (int n = 0; n < input2d[m].size(); n++) {
			if (input2d[m][n] == nextIdx) {
				nextIdx++;
			} else if (input2d[m][n] > nextIdx) {
				input2d = swapIdx(nextIdx, input2d[m][n], input2d);
				nextIdx++;
			}
		}
	}
//	for (int i = 0; i < input2d.size(); i++) {
//		for (int j = 0; j < input2d[i].size(); j++) {
//			cout << input2d[i][j] << ",";
//		}
//		cout << "\n";
//	}
	return input2d;
}
vector<vector<int> > swapIdx(int idx1, int idx2, vector<vector<int> > input2dswap) {
	for (int i = 0; i < input2dswap.size(); i++) {
		for (int j = 0; j < input2dswap[i].size(); j++) {
			if (input2dswap[i][j] == idx1) {
				input2dswap[i][j] = idx2;
			} else if (input2dswap[i][j] == idx2) {
				input2dswap[i][j] = idx1;
			}
		}
	}
	return input2dswap;
}
void randomWalk(vector<vector<int> > input2dVector, int n) {
	for (int i = 0; i < n; i++) {
		PuzzleMove puzzle;
		vector<pair<int, string> > moves = puzzle.OpenMoves(input2dVector);
		int randMoveIndex = rand() % moves.size();
		cout <<"\n("<< moves[randMoveIndex].first << ","<< moves[randMoveIndex].second << ") \n";
		input2dVector = puzzle.applyMoveClone(input2dVector, moves[randMoveIndex]);
		input2dVector = normalize(input2dVector);
		cout << "\n" <<row << "," << column;
		for (int i = 0; i < input2dVector.size(); i++) {
			for (int j = 0; j < input2dVector[i].size(); j++) {
				cout << input2dVector[i][j] << ",";
			}
			cout << "\n";
		}
		if (puzzleCheck(input2dVector))
			break;
	}
}
vector<pair<pair<vector<vector<int> >, vector<vector<int> > >, pair<vector<pair<int, string> >, pair<int, pair<int, string> > > > > expandNode(vector<vector<int> > input2dVector){
	PuzzleMove puzzle;
	vector<pair<int, string> > moves = puzzle.OpenMoves(input2dVector);
	//vector node of currentState, previous state, possible moves, depth,
	//pair of < pair < current state, previous state>, pair<possible moves, pair<depth, previous move> > >
	vector<pair<pair<vector<vector<int> >, vector<vector<int> > >, pair<vector<pair<int, string> >, pair<int, pair<int, string> > > > > node;
	node.push_back(make_pair(make_pair(input2dVector, input2dVector), make_pair(puzzle.OpenMoves(input2dVector), make_pair(1, make_pair(0, "Start")))));
	int nodeDepth = 1;
	bool breakWhile = false;
	while (!breakWhile){
		for (int g = 0; g < node.size(); g++){
			if(nodeDepth == node[g].second.second.first){
				for (int i = 0; i < node[g].second.first.size() && node[g].second.first.size() > 0; i++){
					bool duplicateState = false;
					for (int j = 0; j < node.size(); j++){
						if(identicalCheck(normalize(puzzle.applyMoveClone(node[g].first.first, node[g].second.first[i])), node[j].first.first)){
							duplicateState = true;
							break;
						}
					}
					if (!duplicateState){
						vector<pair<int, string> > movesCheck = puzzle.OpenMoves(normalize(puzzle.applyMoveClone(node[g].first.first, node[g].second.first[i])));
						for (int k = 0; k < movesCheck.size(); k++){
							for (int j = 0; j < node.size(); j++){
								if(identicalCheck(normalize(puzzle.applyMoveClone(node[g].first.first, movesCheck[k])), node[j].first.first)){
									movesCheck.erase( movesCheck.begin() + k);
									break;
								}
							}
						}
						node.push_back(make_pair(make_pair(normalize(puzzle.applyMoveClone(node[g].first.first, node[g].second.first[i])), node[g].first.first), make_pair( movesCheck, make_pair(nodeDepth+1, node[g].second.first[i]))));
					}
				}
			}
			if (puzzleCheck(node[g].first.first)){
				breakWhile = true;
			}
		}
		nodeDepth = nodeDepth + 1;
	}
	return node;
//	for (int i = 0; i < node.size(); i++){
//		vector<vector<int> > matrix = node[i].first.first;
//		for (int j = 0; j < matrix.size(); j++) {
//			for (int k = 0; k < matrix[j].size(); k++) {
//				cout << matrix[j][k] << ",";
//			}
//			cout << "\n";
//
//		}
//		for ( int j = 0; j < node[i].second.first.size(); j++){
//			cout << node[i].second.first[j].first << " " << node[i].second.first[j].second << "\n";
//		}
//		cout << "depth: " <<node[i].second.second.first << "\n";
//		cout << "open: " <<node[i].second.second.second << "\n";
//	}
}
pair<int, int> breadthFirstSearch(vector<pair<pair<vector<vector<int> >, vector<vector<int> > >, pair<vector<pair<int, string> >, pair<int, pair<int, string> > > > > nodes){
	vector<pair<int, string> > movesTaken;
	int depthCurrent = 1;
	int nodeVisisted = 0;
	pair<pair<vector<vector<int> >, vector<vector<int> > >, pair<vector<pair<int, string> >, pair<int, pair<int, string> > > > solutionNode, workingNode;
	vector<vector<int> > solutionState;
	for (int i = 0; i < nodes.size(); i++){
		if (nodes[i].second.second.first == depthCurrent) {
			nodeVisisted++;
			if (puzzleCheck(nodes[i].first.first)){
				solutionNode = nodes[i];
				workingNode = nodes[i];
				solutionState = nodes[i].first.first;
				break;
			}
		} else {
			depthCurrent++;
			nodeVisisted++;
			if (puzzleCheck(nodes[i].first.first)){
				solutionNode = nodes[i];
				workingNode = nodes[i];
				solutionState = nodes[i].first.first;
				break;
			}
		}
	}
	while (depthCurrent > 1){
		for (int j = 0; j < nodes.size(); j++){
			if (identicalCheck(nodes[j].first.first, workingNode.first.second )){
				movesTaken.push_back(nodes[j].second.second.second);
				workingNode = nodes[j];
			}
		}
		depthCurrent--;
	}
	reverse(movesTaken.begin(), movesTaken.end());
	movesTaken.erase(movesTaken.begin());
	for (int k = 0; k < movesTaken.size(); k++){
		cout << "\n(" << movesTaken[k].first << "," << movesTaken[k].second << ")";
	}
	cout << "\n(" << solutionNode.second.second.second.first << "," << solutionNode.second.second.second.second << ")";
	cout << "\n" <<row << "," << column;
	for (int i = 0; i < solutionState.size(); i++) {
		for (int j = 0; j < solutionState[i].size(); j++) {
			cout << solutionState[i][j] << ",";
		}
		cout << "\n";
	}

	return make_pair(nodeVisisted, solutionNode.second.second.first);
}
pair<int, int> depthFirstSearch(vector<pair<pair<vector<vector<int> >, vector<vector<int> > >, pair<vector<pair<int, string> >, pair<int, pair<int, string> > > > > nodes){
	vector<pair<int, string> > movesTaken;
	int depthCurrent = 1;
	int nodeVisisted = 0;
	vector<pair<pair<pair<vector<vector<int> >, vector<vector<int> > >, pair<vector<pair<int, string> >, pair<int, pair<int, string> > > >, int> > editNode;
	pair<pair<vector<vector<int> >, vector<vector<int> > >, pair<vector<pair<int, string> >, pair<int, pair<int, string> > > > solutionNode, workingNode;
	vector<vector<int> > solutionState;
	for (int i1 = 0; i1 < nodes.size(); i1++){
		editNode.push_back(make_pair(nodes[i1], 0));
	}
	bool breakwhie = false;
	while (!breakwhie){
		int depthCurrent = 1;
		for (int i = 0; i < editNode.size(); i++){
			if (editNode[i].first.second.second.first == depthCurrent && editNode[i].second == 0) {
				nodeVisisted++;
				depthCurrent++;
				if (puzzleCheck(editNode[i].first.first.first)){
					solutionNode = editNode[i].first;
					workingNode = editNode[i].first;
					solutionState = editNode[i].first.first.first;
					breakwhie = true;
					break;
				}
				editNode[i].second = 1;
			}
		}
	}
	depthCurrent = solutionNode.second.second.first;
	while (depthCurrent > 1){
		for (int j = 0; j < nodes.size(); j++){
			if (identicalCheck(nodes[j].first.first, workingNode.first.second )){
				movesTaken.push_back(nodes[j].second.second.second);
				workingNode = nodes[j];
			}
		}
		depthCurrent--;
	}
	reverse(movesTaken.begin(), movesTaken.end());
	movesTaken.erase(movesTaken.begin());
	for (int k = 0; k < movesTaken.size(); k++){
		cout << "\n(" << movesTaken[k].first << "," << movesTaken[k].second << ")";
	}
	cout << "\n(" << solutionNode.second.second.second.first << "," << solutionNode.second.second.second.second << ")";
	cout << "\n" <<row << "," << column;
	for (int i = 0; i < solutionState.size(); i++) {
		for (int j = 0; j < solutionState[i].size(); j++) {
			cout << solutionState[i][j] << ",";
		}
		cout << "\n";
	}

	return make_pair(nodeVisisted, solutionNode.second.second.first);
}
pair<int, int> iterativeDeepeningSearch(vector<pair<pair<vector<vector<int> >, vector<vector<int> > >, pair<vector<pair<int, string> >, pair<int, pair<int, string> > > > > nodes){
	vector<pair<int, string> > movesTaken;
	int depthCurrent = 1;
	int foundIndex = 0;
	int nodeVisisted = 0;
	pair<pair<vector<vector<int> >, vector<vector<int> > >, pair<vector<pair<int, string> >, pair<int, pair<int, string> > > > solutionNode, workingNode;
	vector<vector<int> > solutionState;
	while(true){
		pair<bool, pair<int,int> > outcome = iterRecursive(nodes, depthCurrent);
		if (outcome.first == true){
			foundIndex = outcome.second.first;
			solutionNode = nodes[foundIndex];
			workingNode = nodes[foundIndex];
			solutionState = nodes[foundIndex].first.first;
			nodeVisisted = nodeVisisted + outcome.second.second;
			break;
		} else {
			depthCurrent++;
			nodeVisisted = nodeVisisted + outcome.second.second;
		}
	}
	depthCurrent = solutionNode.second.second.first;
	while (depthCurrent > 1){
		for (int j = 0; j < nodes.size(); j++){
			if (identicalCheck(nodes[j].first.first, workingNode.first.second )){
				movesTaken.push_back(nodes[j].second.second.second);
				workingNode = nodes[j];
			}
		}
		depthCurrent--;
	}
	reverse(movesTaken.begin(), movesTaken.end());
	movesTaken.erase(movesTaken.begin());
	for (int k = 0; k < movesTaken.size(); k++){
		cout << "\n(" << movesTaken[k].first << "," << movesTaken[k].second << ")";
	}
	cout << "\n(" << solutionNode.second.second.second.first << "," << solutionNode.second.second.second.second << ")";
	cout << "\n" <<row << "," << column;
	for (int i = 0; i < solutionState.size(); i++) {
		for (int j = 0; j < solutionState[i].size(); j++) {
			cout << solutionState[i][j] << ",";
		}
		cout << "\n";
	}

	return make_pair(nodeVisisted, solutionNode.second.second.first);
}
pair<bool, pair<int,int> > iterRecursive(vector<pair<pair<vector<vector<int> >, vector<vector<int> > >, pair<vector<pair<int, string> >, pair<int, pair<int, string> > > > > nodes, int deep){
	vector<pair<int, string> > movesTaken;
	int depthCurrent = deep;
	int nodeVisisted = 0;
	int foundIndex= 0;
	bool found = false;
	pair<pair<vector<vector<int> >, vector<vector<int> > >, pair<vector<pair<int, string> >, pair<int, pair<int, string> > > > solutionNode, workingNode;
	vector<vector<int> > solutionState;
	for (int i = 0; i < nodes.size(); i++){
		if (nodes[i].second.second.first == depthCurrent) {
			nodeVisisted++;
			if (puzzleCheck(nodes[i].first.first)){
				found = true;
				foundIndex = i;
				break;
			}
		}
	}
	// pair of bool ( pair of indexIfFound, nodeVisit)
	return make_pair(found, make_pair(foundIndex, nodeVisisted));
}

