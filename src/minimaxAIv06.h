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

// v13 in aigames.com

#ifndef MINIMAXAIV06
#define MINIMAXAIV06

#include "botAI.h"
#include "minimaxField.h"
class MinimaxAIv06: public BotAI {
public:
	MinimaxAIv06(Field* field) : BotAI(field) {
		infinity_ = 1e9;
		winningWeight_ = infinity_;
		depth_ = 10;
	}
	int makeTurn() {
		int move = -1;
		MinimaxField mField(field_,getBotId(),4);
		max(mField,move,depth_,-infinity_-1,infinity_+1);
		return move;
	}
	int max(MinimaxField &mField, int& bestMove, int depth, int alpha, int beta) {
		if(mField.isWon()) return -winningWeight_;
		if(depth == 0) {
			return mField.getScore(0);
		}
		int ret = -infinity_;
		int best = -1;
		for(int column = 0; column < mField.getNrColumns(); column++) {
			if(!mField.validMove(column)) continue;
			mField.addDisc(column,0);
			int weight = min(mField, bestMove, depth-1,alpha,beta);
			if(weight > ret || best == -1) {
				ret = weight;
				best = column;
			}
			mField.removeDisc(column,0);
			if(ret >= beta) {
				break;
			}
			alpha = std::max(alpha,ret);
		}
		bestMove = best;
		return ret;
	}
	int min(MinimaxField &mField, int& bestMove, int depth,int alpha, int beta) {
		if(mField.isWon()) return winningWeight_;
		if(depth == 0) {
			return mField.getScore(1);
		}
		int ret = infinity_;
		int best = -1;
		for(int column = 0; column < mField.getNrColumns(); column++) {
			if(!mField.validMove(column)) continue;
			mField.addDisc(column,1);
			int weight = max(mField, bestMove, depth-1, alpha, beta);
			if(weight < ret || best == -1) {
				ret = weight;
				best = column;
			}
			mField.removeDisc(column,1);
			if(ret <= alpha) {
				break;
			}
			beta = std::min(beta,ret);
		}
		bestMove = best;
		return ret;
	}
private:
	int winningWeight_;
	int infinity_;
	int depth_;
};
#endif //MINIMAXAIV06