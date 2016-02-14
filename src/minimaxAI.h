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

#ifndef MINIMAXAI_H
#define MINIMAXAI_H

#include "botAI.h"

class MinimaxAI: public BotAI {
public:
	MinimaxAI(Field* field) : BotAI(field) {}
	int makeTurn() {
		return rand()%field_->getNrColumns();
	}
};
#endif //MINIMAXAI_H