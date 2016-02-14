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

#ifndef DEFENSIVEAI_H
#define DEFENSIVEAI_H

#include "botAI.h"

class DefensiveAI: public BotAI {
public:
	DefensiveAI(Field* field) : BotAI(field) {}

	int makeTurn() {
		std::vector<int> validMoves;
		for(int column = 0; column < field_->getNrColumns(); column++) {
			int priority = getColumnPriority(column);
			if(priority >= (1<<3)) {
				return column;
			}
			for(int i = 0; i < priority; i++) {
				validMoves.push_back(column);
			}
		}
		return validMoves[rand()%validMoves.size()];
	}
private:
	int getColumnPriority(int column) {
		int row = field_->getMoveRow(column);
		if(row == -1) {
			return 0;
		}
		int dc[] = {0,1,1,1};
		int dr[] = {1,0,1,-1};
		int ret = 0;
		for(int i = 0; i < 4; i++) {
			int count = countCells(column, row,dc[i],dr[i], getOppId()) + 
					countCells(column, row,-dc[i],-dr[i],getOppId());
			ret = std::max(ret,1<<count);
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
#endif //DEFENSIVEAI_H