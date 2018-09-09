/*
 * PuzzleMove.h
 *
 *  Created on: Oct 16, 2017
 *      Author: Jayden Chen
 */

#ifndef PUZZLEMOVE_H_
#define PUZZLEMOVE_H_
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <cstring>
#include <vector>
#include <algorithm>
#include <utility>
using namespace std;
class PuzzleMove {
public:
	PuzzleMove();
	vector<pair<int, string> > OpenMovesPiece(vector< vector<int> > input2dVector, int piece);
	vector<pair<int, string> > OpenMoves(vector< vector<int> > input2dVector);
	void applyMove(vector< vector<int> > input2dVector, pair<int, string> move);
	vector< vector<int> > applyMoveClone(vector< vector<int> > input2dVector, pair<int, string> move);

};

#endif /* PUZZLEMOVE_H_ */
