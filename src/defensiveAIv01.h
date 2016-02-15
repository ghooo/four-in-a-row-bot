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

#ifndef DEFENSIVEAIV01_H
#define DEFENSIVEAIV01_H

#include "botAI.h"

class DefensiveAIv01: public BotAI {
public:
	DefensiveAIv01(Field* field) : BotAI(field) {}

	int makeTurn() {
		for(int column = 0; column < field_->getNrColumns(); column++) {
			if(isLosingColumn(column)) {
				return column;
			}
		}
		return BotAI::makeTurn();
	}
private:
	bool isLosingColumn(int column) {
		int row = field_->getMoveRow(column);
		if(row == -1) {
			return false;
		}
		return isLosingCell(column, row);
	}
	bool isLosingCell(int column, int row) {
		int dc[] = {0,1,1,1};
		int dr[] = {1,0,1,-1};
		for(int i = 0; i < 4; i++) {
			if(countCells(column, row,dc[i],dr[i], getOppId()) + 
					countCells(column, row,-dc[i],-dr[i],getOppId()) >= 3) {
				return true;
			}
		}
		return false;
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
#endif //DEFENSIVEAIV01_H