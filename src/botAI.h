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

#ifndef BOTAI_H
#define BOTAI_H

#include "field.h"

class BotAI {
public:

	BotAI(Field *field) {
		field_ = field;
		botId_ = -1;
	}
	void setBotId(int botId) {
		botId_ = botId;
	}
	int getBotId() {
		return botId_;
	}
	int getOppId() {
		return 3-botId_;
	}
	virtual int makeTurn() {
		std::vector<int> validMoves;
		for(int column = 0; column < field_->getNrColumns(); column++) {
			if(field_->isValidMove(column)) {
				validMoves.push_back(column);
			}
		}
		return validMoves[rand()%validMoves.size()];

	};
	virtual ~BotAI() {}
protected:
	Field *field_;
	int botId_;
};
#endif //BOTAI_H