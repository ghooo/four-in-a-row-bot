// Copyright 2026 ghooo (https://github.com/ghooo)

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

// v7 in aigames.com

#ifndef MINIMAXAIV02_H
#define MINIMAXAIV02_H

#include "botAI.h"

class MinimaxAIv02: public BotAI {
public:
	MinimaxAIv02(Field* field) : BotAI(field) {
		dirc[0] = 0, dirc[1] = 1, dirc[2] = 1, dirc[3] = 1; 
		dirr[0] = 1, dirr[1] = 1, dirr[2] = 0, dirr[3] = -1;
		eta = 2.0;
	}
	int makeTurn() {
		if(getBotId() == 1) eta = 0.0;
		eta*=0.8;
		minimax mm = max(field_,2);
		return mm.move;
	}
private:
	int evaluate(Field* field) {
		int largeValue = 1e6;
		// std::cout << 1 << std::endl;		
		// won.
		if(isWinning(field,getBotId())) {
			return largeValue;
		}
		// std::cout << 2 << std::endl;		
		// Lost.
		if(isWinning(field,getOppId())) {
			return -largeValue;
		}
		// vector<vector<vector<int> > > count;
		// std::cout << 3 << std::endl;		

		int count[2][6][4] = {};
		for(int column = 0; column < field->getNrColumns(); column++) {
			int row = field->getNrRows()-1;
			while(field->getDisc(column,row) && row >= 0) {
				row--;
			}
			for(int order = 0; row >= 0; row--, order++) {
				count[0][order][maxNeighbors(field, column, row, getBotId())]++;
				count[1][order][maxNeighbors(field, column, row, getOppId())]++;
			}
		}
		// std::cout << 4 << std::endl;
		if(count[0][0][3] >= 1) return largeValue;
		// std::cout << 5 << std::endl;		
		if(count[1][0][3] > 1) return -largeValue;
		// std::cout << 6 << std::endl;		
		int ret = 0;
		for(int order = 0; order < 6; order++) {
			for(int neighbors = 0; neighbors < 4; neighbors++) {
				ret += (6-1-order)*neighbors*count[0][order][neighbors];
				ret -= (6-1-order)*neighbors*count[1][order][neighbors];
			}
		}
		int mod = abs(ret)*eta*2;
		if(mod) {
			ret += rand()%mod-mod/2;
		}

		// std::cout << 7 << std::endl;		
		return ret;
	}
	minimax max(Field* field, int remDepth) {
		if(remDepth == 0) {
			return minimax(evaluate(field),-1);
		}
		if(isWinning(field,getOppId())) {
			return minimax(-1e6,-1);
		}
		minimax ret(-INF,-1);
		for(int column = 0; column < field->getNrColumns(); column++) {
			if(field->isValidMove(column)) {
				field->addDisc(column,getBotId());
				minimax tmp = min(field,remDepth);
				tmp.move = column;
				if(ret < tmp) {
					ret = tmp;
				}
				field->removeDisc(column);
			}
		}
		return ret;
	}
	minimax min(Field* field, int remDepth) {
		if(isWinning(field,getBotId())) {
			return minimax(1e6,-1);
		}
		minimax ret(INF,-1);
		for(int column = 0; column < field->getNrColumns(); column++) {
			if(field->isValidMove(column)) {
				field->addDisc(column,getOppId());
				minimax tmp = max(field,remDepth-1);
				tmp.move = column;
				if(tmp < ret) {
					ret = tmp;
				}
				field->removeDisc(column);
			}
		}
		return ret;
	}
	bool isWinning(Field* field, int playerId) {
		for(int column = 0; column < field->getNrColumns(); column++) {
			for(int row = 0; row < field->getNrRows(); row++) {
				for(int i = 0; i < 4; i++) {
					if(field->getDisc(column,row) == playerId){
						int tmp = 1 + count(field, column, row, playerId, 
								dirc[i], dirr[i]);
						if(tmp >= 4) {
							return true;
						} 
					}
				}
			}
		}
		return false;
	}
	int maxNeighbors(Field* field, int column, int row, int playerId) {
		int ret = 0;
		for(int i = 0; i < 4; i++) {
			int tmp = count(field, column, row, playerId, dirc[i], dirr[i])
					+ count(field, column, row, playerId, -dirc[i], -dirr[i]);
			if(tmp > ret) ret = tmp;
		}
		if(ret > 3) ret = 3;
		return ret;
	}
	int count(Field* field, int column, int row, int playerId, int dc, int dr) {
		int ret = 0;
		int nc = column+dc, nr = row+dr;
		while(nc >= 0 && nc < field->getNrColumns() && nr >= 0 && 
				nr < field->getNrRows()
				 && playerId == field->getDisc(nc,nr)) {
			nc += dc;
			nr += dr;
			ret++;
		}
		if(ret > 3) ret = 3;
		return ret;
	}
	int dirc[4], dirr[4];
	double eta;

};
#endif //MINIMAXAIV02_H