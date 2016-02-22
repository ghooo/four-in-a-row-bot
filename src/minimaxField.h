// Copyright 2016 ghooo (https://github.com/ghooo)

//    Licensed under the Apache License, Version 2.0 (the "License");
//    you may not use this file except in compliance with the License.
//    You may obtain a copy of the License at

//        http://www.apache.org/licenses/LICENSE-2.0

//    Unless required by applicable law or agreed to in writing, software
//    distributed under the License is distributed on an "AS IS" BASIS,
//    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//    See the License for the specific language governing permissions and
//    limitations under the License.
//  
//    For the full copyright and license information, please view the LICENSE
//    file that was distributed with this source code.

#ifndef MINIMAXFIELD_H
#define MINIMAXFIELD_H

#include "field.h"

using namespace std;
#define debug(x) cout << (#x) << ": " << (x) << endl;


class MinimaxField {
public:
	MinimaxField(Field* field, int playerId, int base = 10) {
		cols_ = field->getNrColumns();
		rows_ = field->getNrRows();
		playerScore_[0] = playerScore_[1] = 0;
		discsPerColumn = std::vector<int>(cols_,0);
		numOfWinningNs_ = calcMatrix();
		base_ = base;
		basePower_[0] = 1;
		for(int i = 1; i < 5; i++) basePower_[i] = base_*basePower_[i-1];
		basePower_[4] = 1e8;
		basePower_[0] = 0;
		calcArray();
		for(int column = 0; column < cols_; column++) {
			for(int row = rows_-1; row >= 0; row--) {
				int disc = field->getDisc(column,row);
				if(disc) {
					addDisc(column,disc!=playerId);
				}
			}
		}
	}
	int getScore(int curPlayerId) {
		return playerScore_[curPlayerId]-playerScore_[1-curPlayerId];
	}
	void addDisc(int column, int id) {
		int row = discsPerColumn[column];
		for(int i = 0; i < matrix_[column][row].size(); i++) {
			int tmp = matrix_[column][row][i];
			array_[id][tmp]++;

			if(array_[1-id][tmp]) { // if other player is also sharing
				if(array_[id][tmp] == 1) { // if this player first appearance
					playerScore_[1-id] -= basePower_[array_[1-id][tmp]];
				}
			} else {
				playerScore_[id] += basePower_[array_[id][tmp]] -
									basePower_[array_[id][tmp]-1];
			}
		}
		discsPerColumn[column]++;
	}
	void removeDisc(int column, int id) {
		int row = discsPerColumn[column]-1;
		for(int i = 0; i < matrix_[column][row].size(); i++) {
			int tmp = matrix_[column][row][i];
			array_[id][tmp]--;

			if(array_[1-id][tmp]) { // if other player is also sharing
				if(array_[id][tmp] == 0) {
					playerScore_[1-id] += basePower_[array_[1-id][tmp]];
				}
			} else {
				playerScore_[id] += basePower_[array_[id][tmp]] -
									basePower_[array_[id][tmp]+1];
			}
		}

		discsPerColumn[column]--;
	}
	int getNrColumns() {
		return cols_;
	}
	int getNrRows() {
		return rows_;
	}
	bool validMove(int column) {
		return discsPerColumn[column] < rows_;
	}
	bool isWon() {
		return playerScore_[0] >= basePower_[4] || 
			   playerScore_[1] >= basePower_[4];
	}
	void debugMatrix() {
		debug(cols_);
		debug(matrix_.size());
		debug(matrix_[0].size());
		debug(numOfWinningNs_);
	}
private:
	int calcMatrix() {
		int dc[4] = {1,1,0,-1};
		int dr[4] = {0,1,1, 1};
		int idx = 0;
		matrix_ = std::vector<std::vector<std::vector<int> > >
				(cols_, std::vector<std::vector<int> >(rows_));
		for(int column = 0; column < cols_; column++) {
			for(int row = 0; row < rows_; row++) {
				for(int i = 0; i < 4; i++) {
					idx += addToMatrix(idx, column, row, dc[i], dr[i]);
				}
			}
		}
		return idx;
	}
	bool addToMatrix(int idx, int column, int row, int dc, int dr) {
		int cnt = 0;
		int nc = column, nr = row;
		while(nc >= 0 && nc < cols_ && nr >= 0 && nr < rows_) {
			nr += dr;
			nc += dc;
			cnt++;
		}

		if(cnt < 4) {
			return false;
		}
		nr = row;
		nc = column;
		for(int i = 0; i < 4; i++, nr+=dr, nc+=dc) {
			matrix_[nc][nr].push_back(idx);
		}
		return true;
	}
	void calcArray() {
		array_[0] = std::vector<int> (numOfWinningNs_,0);
		array_[1] = std::vector<int> (numOfWinningNs_,0);
	}
	std::vector<std::vector<std::vector<int> > > matrix_;
	std::vector<int> array_[2];

	int cols_, rows_;
	int playerScore_[2];
	int numOfWinningNs_;
	int base_;
	int basePower_[5];
	std::vector<int> discsPerColumn;
};
#endif //MINIMAXFIELD_H