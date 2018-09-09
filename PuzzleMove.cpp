/*
 * PuzzleMove.cpp
 *
 *  Created on: Oct 16, 2017
 *      Author: Jayden Chen
 */

#include "PuzzleMove.h"
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
PuzzleMove::PuzzleMove() {
	// TODO Auto-generated constructor stub
}
vector<pair<int, string> > PuzzleMove::OpenMovesPiece(
		vector<vector<int> > input2dVector, int piece) {
	vector<vector<int> > pieceCordinates;
	for (int i = 0; i < input2dVector.size(); i++) {
		for (int j = 0; j < input2dVector[i].size(); j++) {
			if (input2dVector[i][j] == piece) {
				vector<int> temparray;
				temparray.push_back(i);
				temparray.push_back(j);
				pieceCordinates.push_back(temparray);
			}

		}
	}
	int pieceSize = pieceCordinates.size();
	vector<pair<int, string> > possibleMoves;
	string orientation = "default";
	if (pieceSize == 1) {
		int x;
		int y;
		x = pieceCordinates[0][0];
		y = pieceCordinates[0][1];
		if (input2dVector[x - 1][y] == 0
				|| (piece == 2 && input2dVector[x - 1][y] == -1))
			possibleMoves.push_back(make_pair(piece, "up"));
		if (input2dVector[x + 1][y] == 0
				|| (piece == 2 && input2dVector[x + 1][y] == -1))
			possibleMoves.push_back(make_pair(piece, "down"));
		if (input2dVector[x][y - 1] == 0
				|| (piece == 2 && input2dVector[x][y - 1] == -1))
			possibleMoves.push_back(make_pair(piece, "left"));
		if (input2dVector[x][y + 1] == 0
				|| (piece == 2 && input2dVector[x][y + 1] == -1))
			possibleMoves.push_back(make_pair(piece, "right"));

	} else if (pieceSize == 2) {
		int x1;
		int y1;
		x1 = pieceCordinates[0][0];
		y1 = pieceCordinates[0][1];
		int x2;
		int y2;
		x2 = pieceCordinates[1][0];
		y2 = pieceCordinates[1][1];
		if (pieceCordinates[0][0] == pieceCordinates[1][0])
			orientation = "h";
		if (pieceCordinates[0][1] == pieceCordinates[1][1])
			orientation = "v";
		if (orientation == "h") {
			if ((input2dVector[x1 - 1][y1] == 0
					&& input2dVector[x2 - 1][y2] == 0)
					|| (piece == 2 && input2dVector[x1 - 1][y1] == -1
							&& input2dVector[x2 - 1][y2] == -1))
				possibleMoves.push_back(make_pair(piece, "up"));
			if ((input2dVector[x1 + 1][y1] == 0
					&& input2dVector[x2 + 1][y2] == 0)
					|| (piece == 2 && input2dVector[x1 + 1][y1] == -1
							&& input2dVector[x2 + 1][y2] == -1))
				possibleMoves.push_back(make_pair(piece, "down"));
			if (input2dVector[x1][y1 - 1] == 0
					|| (piece == 2 && input2dVector[x1][y1 - 1] == -1))
				possibleMoves.push_back(make_pair(piece, "left"));
			if (input2dVector[x1][y1 + 1] == 0
					|| (piece == 2 && input2dVector[x1][y1 + 1] == -1))
				possibleMoves.push_back(make_pair(piece, "right"));

		} else if (orientation == "v") {
			if (input2dVector[x1 - 1][y1] == 0
					|| (piece == 2 && input2dVector[x1 - 1][y1] == -1))
				possibleMoves.push_back(make_pair(piece, "up"));
			if (input2dVector[x1 + 1][y1] == 0
					|| (piece == 2 && input2dVector[x1 + 1][y1] == -1))
				possibleMoves.push_back(make_pair(piece, "down"));
			if ((input2dVector[x1][y1 - 1] == 0
					&& input2dVector[x2][y2 - 1] == 0)
					|| (piece == 2 && input2dVector[x1][y1 - 1] == -1
							&& input2dVector[x2][y2 - 1] == -1))
				possibleMoves.push_back(make_pair(piece, "left"));
			if ((input2dVector[x1][y1 + 1] == 0
					&& input2dVector[x2][y2 + 1] == 0)
					|| (piece == 2 && input2dVector[x1][y1 + 1] == -1
							&& input2dVector[x2][y2 + 1] == -1))
				possibleMoves.push_back(make_pair(piece, "right"));
		}
	} else if (pieceSize == 4) {
		int x1;
		int y1;
		x1 = pieceCordinates[0][0];
		y1 = pieceCordinates[0][1];
		int x2;
		int y2;
		x2 = pieceCordinates[1][0];
		y2 = pieceCordinates[1][1];
		int x3;
		int y3;
		x3 = pieceCordinates[2][0];
		y3 = pieceCordinates[2][1];
		int x4;
		int y4;
		x4 = pieceCordinates[3][0];
		y4 = pieceCordinates[3][1];
		if ((input2dVector[x1 - 1][y1] == 0 && input2dVector[x2 - 1][y2] == 0)
				|| (piece == 2 && input2dVector[x1 - 1][y1] == -1
						&& input2dVector[x2 - 1][y2] == -1))
			possibleMoves.push_back(make_pair(piece, "up"));
		if ((input2dVector[x3 + 1][y3] == 0 && input2dVector[x4 + 1][y4] == 0)
				|| (piece == 2 && input2dVector[x3 + 1][y3] == -1
						&& input2dVector[x4 + 1][y4] == -1))
			possibleMoves.push_back(make_pair(piece, "down"));
		if ((input2dVector[x1][y1 - 1] == 0 && input2dVector[x3][y3 - 1] == 0)
				|| (piece == 2 && input2dVector[x1][y1 - 1] == -1
						&& input2dVector[x3][y3 - 1] == -1))
			possibleMoves.push_back(make_pair(piece, "left"));
		if ((input2dVector[x2][y2 + 1] == 0 && input2dVector[x4][y4 + 1] == 0)
				|| (piece == 2 && input2dVector[x2][y2 + 1] == -1
						&& input2dVector[x4][y4 + 1] == -1))
			possibleMoves.push_back(make_pair(piece, "right"));

	}
	return possibleMoves;
}
vector<pair<int, string> > PuzzleMove::OpenMoves(
		vector<vector<int> > input2dVector) {
	vector<string> openMoves;
	int max = 0;
	for (int i = 0; i < input2dVector.size(); i++) {
		for (int j = 0; j < input2dVector[i].size(); j++) {
			if (input2dVector[i][j] > max)
				max = input2dVector[i][j];
		}
	}
	vector<pair<int, string> > moves;
	moves = OpenMovesPiece(input2dVector, 2);
	for (int i = 3; i < max + 1; i++) {
		vector<pair<int, string> > tempMoves = OpenMovesPiece(input2dVector, i);
		if (tempMoves.size() > 0) {
			for (int j = 0; j < tempMoves.size(); j++)
				moves.push_back(tempMoves[j]);
		}
	}
	return moves;
}
void PuzzleMove::applyMove(vector<vector<int> > input2dVector,
		pair<int, string> move) {
	vector<vector<int> > pieceCordinates;
	string orientation;
	for (int i = 0; i < input2dVector.size(); i++) {
		for (int j = 0; j < input2dVector[i].size(); j++) {
			if (input2dVector[i][j] == move.first) {
				vector<int> temparray;
				temparray.push_back(i);
				temparray.push_back(j);
				pieceCordinates.push_back(temparray);
			}
		}
	}
	switch (pieceCordinates.size()) {
	case 1:
		if (move.second == "up") {
			input2dVector[pieceCordinates[0][0] - 1][pieceCordinates[0][1]] =
					move.first;
			input2dVector[pieceCordinates[0][0]][pieceCordinates[0][1]] = 0;
		} else if (move.second == "down") {
			input2dVector[pieceCordinates[0][0] + 1][pieceCordinates[0][1]] =
					move.first;
			input2dVector[pieceCordinates[0][0]][pieceCordinates[0][1]] = 0;
		} else if (move.second == "left") {
			input2dVector[pieceCordinates[0][0]][pieceCordinates[0][1] - 1] =
					move.first;
			input2dVector[pieceCordinates[0][0]][pieceCordinates[0][1]] = 0;
		} else if (move.second == "right") {
			input2dVector[pieceCordinates[0][0]][pieceCordinates[0][1] + 1] =
					move.first;
			input2dVector[pieceCordinates[0][0]][pieceCordinates[0][1]] = 0;
		}
		break;
	case 2:
		int x1;
		int y1;
		x1 = pieceCordinates[0][0];
		y1 = pieceCordinates[0][1];
		int x2;
		int y2;
		x2 = pieceCordinates[1][0];
		y2 = pieceCordinates[1][1];
		if (move.second == "up") {
			input2dVector[pieceCordinates[0][0] - 1][pieceCordinates[0][1]] =
					move.first;
			input2dVector[pieceCordinates[0][0]][pieceCordinates[0][1]] = 0;
			input2dVector[pieceCordinates[1][0] - 1][pieceCordinates[1][1]] =
					move.first;
			input2dVector[pieceCordinates[1][0]][pieceCordinates[1][1]] = 0;
		} else if (move.second == "down") {
			input2dVector[pieceCordinates[1][0] + 1][pieceCordinates[1][1]] =
					move.first;
			input2dVector[pieceCordinates[1][0]][pieceCordinates[1][1]] = 0;
			input2dVector[pieceCordinates[0][0] + 1][pieceCordinates[0][1]] =
					move.first;
			input2dVector[pieceCordinates[0][0]][pieceCordinates[0][1]] = 0;
		} else if (move.second == "left") {
			input2dVector[pieceCordinates[0][0]][pieceCordinates[0][1] - 1] =
					move.first;
			input2dVector[pieceCordinates[0][0]][pieceCordinates[0][1]] = 0;
			input2dVector[pieceCordinates[1][0]][pieceCordinates[1][1] - 1] =
					move.first;
			input2dVector[pieceCordinates[1][0]][pieceCordinates[1][1]] = 0;
		} else if (move.second == "right") {
			input2dVector[pieceCordinates[1][0]][pieceCordinates[1][1] + 1] =
					move.first;
			input2dVector[pieceCordinates[1][0]][pieceCordinates[1][1]] = 0;
			input2dVector[pieceCordinates[0][0]][pieceCordinates[0][1] + 1] =
					move.first;
			input2dVector[pieceCordinates[0][0]][pieceCordinates[0][1]] = 0;
		}
		break;
	case 4:
		if (move.second == "up") {
			input2dVector[pieceCordinates[2][0] - 2][pieceCordinates[2][1]] =
					move.first;
			input2dVector[pieceCordinates[2][0]][pieceCordinates[2][1]] = 0;

			input2dVector[pieceCordinates[3][0] - 2][pieceCordinates[3][1]] =
					move.first;
			input2dVector[pieceCordinates[3][0]][pieceCordinates[3][1]] = 0;

		} else if (move.second == "down") {
			input2dVector[pieceCordinates[1][0] + 2][pieceCordinates[1][1]] =
					move.first;
			input2dVector[pieceCordinates[1][0]][pieceCordinates[1][1]] = 0;
			input2dVector[pieceCordinates[0][0] + 2][pieceCordinates[0][1]] =
					move.first;
			input2dVector[pieceCordinates[0][0]][pieceCordinates[0][1]] = 0;
		} else if (move.second == "left") {
			input2dVector[pieceCordinates[1][0]][pieceCordinates[1][1] - 2] =
					move.first;
			input2dVector[pieceCordinates[1][0]][pieceCordinates[1][1]] = 0;
			input2dVector[pieceCordinates[3][0]][pieceCordinates[3][1] - 2] =
					move.first;
			input2dVector[pieceCordinates[3][0]][pieceCordinates[3][1]] = 0;
		} else if (move.second == "right") {
			input2dVector[pieceCordinates[0][0]][pieceCordinates[0][1] + 2] =
					move.first;
			input2dVector[pieceCordinates[0][0]][pieceCordinates[0][1]] = 0;
			input2dVector[pieceCordinates[2][0]][pieceCordinates[2][1] + 2] =
					move.first;
			input2dVector[pieceCordinates[2][0]][pieceCordinates[2][1]] = 0;
		}

	}

	for (int i = 0; i < input2dVector.size(); i++) {
		for (int j = 0; j < input2dVector[i].size(); j++) {
			cout << input2dVector[i][j] << ",";
		}
		cout << "\n";
	}
}
vector<vector<int> > PuzzleMove::applyMoveClone(
		vector<vector<int> > input2dVector, pair<int, string> move) {
	vector<vector<int> > pieceCordinates;
	string orientation;
	for (int i = 0; i < input2dVector.size(); i++) {
		for (int j = 0; j < input2dVector[i].size(); j++) {
			if (input2dVector[i][j] == move.first) {
				vector<int> temparray;
				temparray.push_back(i);
				temparray.push_back(j);
				pieceCordinates.push_back(temparray);
			}
		}
	}
	switch (pieceCordinates.size()) {
	case 1:
		if (move.second == "up") {
			input2dVector[pieceCordinates[0][0] - 1][pieceCordinates[0][1]] =
					move.first;
			input2dVector[pieceCordinates[0][0]][pieceCordinates[0][1]] = 0;
		} else if (move.second == "down") {
			input2dVector[pieceCordinates[0][0] + 1][pieceCordinates[0][1]] =
					move.first;
			input2dVector[pieceCordinates[0][0]][pieceCordinates[0][1]] = 0;
		} else if (move.second == "left") {
			input2dVector[pieceCordinates[0][0]][pieceCordinates[0][1] - 1] =
					move.first;
			input2dVector[pieceCordinates[0][0]][pieceCordinates[0][1]] = 0;
		} else if (move.second == "right") {
			input2dVector[pieceCordinates[0][0]][pieceCordinates[0][1] + 1] =
					move.first;
			input2dVector[pieceCordinates[0][0]][pieceCordinates[0][1]] = 0;
		}
		break;
	case 2:
		int x1;
		int y1;
		x1 = pieceCordinates[0][0];
		y1 = pieceCordinates[0][1];
		int x2;
		int y2;
		x2 = pieceCordinates[1][0];
		y2 = pieceCordinates[1][1];
		if (move.second == "up") {
			input2dVector[pieceCordinates[0][0] - 1][pieceCordinates[0][1]] =
					move.first;
			input2dVector[pieceCordinates[0][0]][pieceCordinates[0][1]] = 0;
			input2dVector[pieceCordinates[1][0] - 1][pieceCordinates[1][1]] =
					move.first;
			input2dVector[pieceCordinates[1][0]][pieceCordinates[1][1]] = 0;
		} else if (move.second == "down") {
			input2dVector[pieceCordinates[1][0] + 1][pieceCordinates[1][1]] =
					move.first;
			input2dVector[pieceCordinates[1][0]][pieceCordinates[1][1]] = 0;
			input2dVector[pieceCordinates[0][0] + 1][pieceCordinates[0][1]] =
					move.first;
			input2dVector[pieceCordinates[0][0]][pieceCordinates[0][1]] = 0;
		} else if (move.second == "left") {
			input2dVector[pieceCordinates[0][0]][pieceCordinates[0][1] - 1] =
					move.first;
			input2dVector[pieceCordinates[0][0]][pieceCordinates[0][1]] = 0;
			input2dVector[pieceCordinates[1][0]][pieceCordinates[1][1] - 1] =
					move.first;
			input2dVector[pieceCordinates[1][0]][pieceCordinates[1][1]] = 0;
		} else if (move.second == "right") {
			input2dVector[pieceCordinates[1][0]][pieceCordinates[1][1] + 1] =
					move.first;
			input2dVector[pieceCordinates[1][0]][pieceCordinates[1][1]] = 0;
			input2dVector[pieceCordinates[0][0]][pieceCordinates[0][1] + 1] =
					move.first;
			input2dVector[pieceCordinates[0][0]][pieceCordinates[0][1]] = 0;
		}
		break;
	case 4:
		if (move.second == "up") {
			input2dVector[pieceCordinates[2][0] - 2][pieceCordinates[2][1]] =
					move.first;
			input2dVector[pieceCordinates[2][0]][pieceCordinates[2][1]] = 0;

			input2dVector[pieceCordinates[3][0] - 2][pieceCordinates[3][1]] =
					move.first;
			input2dVector[pieceCordinates[3][0]][pieceCordinates[3][1]] = 0;

		} else if (move.second == "down") {
			input2dVector[pieceCordinates[1][0] + 2][pieceCordinates[1][1]] =
					move.first;
			input2dVector[pieceCordinates[1][0]][pieceCordinates[1][1]] = 0;
			input2dVector[pieceCordinates[0][0] + 2][pieceCordinates[0][1]] =
					move.first;
			input2dVector[pieceCordinates[0][0]][pieceCordinates[0][1]] = 0;
		} else if (move.second == "left") {
			input2dVector[pieceCordinates[1][0]][pieceCordinates[1][1] - 2] =
					move.first;
			input2dVector[pieceCordinates[1][0]][pieceCordinates[1][1]] = 0;
			input2dVector[pieceCordinates[3][0]][pieceCordinates[3][1] - 2] =
					move.first;
			input2dVector[pieceCordinates[3][0]][pieceCordinates[3][1]] = 0;
		} else if (move.second == "right") {
			input2dVector[pieceCordinates[0][0]][pieceCordinates[0][1] + 2] =
					move.first;
			input2dVector[pieceCordinates[0][0]][pieceCordinates[0][1]] = 0;
			input2dVector[pieceCordinates[2][0]][pieceCordinates[2][1] + 2] =
					move.first;
			input2dVector[pieceCordinates[2][0]][pieceCordinates[2][1]] = 0;
		}

	}

	return input2dVector;
}
