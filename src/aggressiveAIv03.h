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

#ifndef AGGRESSIVEAIV03_H
#define AGGRESSIVEAIV03_H

#include "botAI.h"

class AggressiveAIv03: public BotAI {
public:
	AggressiveAIv03(Field* field) : BotAI(field) { }
	int makeTurn() {
		std::vector<int> validMoves;
		int highestPriorityColumn = 0, highestPriority = 0;
		for(int column = 0; column < field_->getNrColumns(); column++) {
			int row = field_->getMoveRow(column);
			if(row == -1) {
				continue;
			}
			int priority = getCellPriority(column, row);
			if(priority > highestPriority) {
				highestPriority = priority;
				highestPriorityColumn = column;
			}
			int eta = 0;
			if(column < field_->getNrColumns()/2) {
				eta += column;
			} else {
				eta += field_->getNrColumns()-column-1;
			}
			if(row < field_->getNrRows()/2) {
				eta += row;
			} else {
				eta += field_->getNrRows()-row-1;
			}
			for(int i = 0; priority && i < priority+eta; i++) {
				validMoves.push_back(column);
			}
		}

		if(highestPriority >= (1<<3)) {
			return highestPriorityColumn;
		}
		return validMoves[rand()%validMoves.size()];
	}

private:
	int getCellPriority(int column, int row) {
		if(row == -1) {
			return 0;
		}
		int dc[] = {0,1,1,1};
		int dr[] = {1,0,1,-1};
		int ret = 0;
		for(int i = 0; i < 4; i++) {
			int count = countCells(column, row,dc[i],dr[i], getBotId()) + 
					countCells(column, row,-dc[i],-dr[i],getBotId());
			if(count >= 3) {
				return (1<<10);
			}
			ret = std::max(ret,(1<<count)+1);
		}
		for(int i = 0; i < 4; i++) {
			int count = countCells(column, row,dc[i],dr[i], getOppId()) + 
					countCells(column, row,-dc[i],-dr[i],getOppId());
			ret = std::max(ret,1<<count);
		}

		if(field_->is2DiscsPossible(column)) {
			for(int i = 0; i < 4; i++) {
				int count = countCells(column, row-1,dc[i],dr[i], getOppId()) + 
						countCells(column, row-1,-dc[i],-dr[i],getOppId());
				if(count >= 3) {
					return 0;
				}
			}
		}
		return ret;
	}
	int countCells(int column, int row, int dc, int dr, int id) {
		int ret = 0;
		int nc = column+dc, nr = row+dr;
		while(nc >= 0 && nc < field_->getNrColumns() && nr >= 0 && 
				nr < field_->getNrRows() && field_->getDisc(nc,nr)==id) {
			nc += dc;
			nr += dr;
			ret++;
		}
		return ret;
	}
};
#endif //AGGRESSIVEAIV03_H