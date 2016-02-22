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

#include "field.h"
#include "randomAI.h"
#include "defensiveAIv01.h"
#include "defensiveAIv02.h"
#include "defensiveAIv03.h"
#include "aggressiveAIv01.h"
#include "aggressiveAIv02.h"
#include "aggressiveAIv03.h"
#include "aggressiveAIv04.h"
#include "minimaxAIv01.h"
#include "minimaxAIv02.h"
#include "minimaxAIv03.h"
#include "minimaxAIv04.h"
#include "minimaxAIv05.h"
#include "minimaxAIv06.h"
#include "minimaxAIv07.h"

#include <iostream>
#include <string>
#include <vector>

class BotParser {
public:
	BotParser(int difficulty = 1) {
		field_ = new Field(0,0);
        switch(difficulty) {
            case 11: //v1
                botAI_ = new RandomAI(field_);
                break;
            case 21: 
                botAI_ = new DefensiveAIv01(field_);
                break;
            case 22: //v2
                botAI_ = new DefensiveAIv02(field_);
                break;
            case 23: //v3
                botAI_ = new DefensiveAIv03(field_);
                break;
            case 31: //v4
                botAI_ = new AggressiveAIv01(field_);
                break;
            case 32:
                botAI_ = new AggressiveAIv02(field_);
                break;
            case 33:
                botAI_ = new AggressiveAIv03(field_);
                break;
            case 34: //v5
                botAI_ = new AggressiveAIv04(field_);
                break;
            case 41: //v6
                botAI_ = new MinimaxAIv01(field_);
                break;
            case 42: //v7
                botAI_ = new MinimaxAIv02(field_);
                break; 
            case 43: //v8
                botAI_ = new MinimaxAIv03(field_);
                break; 
            case 44: //v9
                botAI_ = new MinimaxAIv04(field_);
                break; 
            case 45: //12
                botAI_ = new MinimaxAIv05(field_);
                break; 
            case 46: //13
                botAI_ = new MinimaxAIv06(field_);
                break; 
            case 47: //14
                botAI_ = new MinimaxAIv07(field_);
                break; 
            default:
                std::cerr << "AI BOT NOT FOUND. TERMINATING..." << std::endl;
                exit(1);
        }
	}
	void run() {
		std::string line;
		while(std::getline(std::cin, line)) {
			if(line.size() == 0) {
				continue;
			}
			std::vector<std::string> parts = split(line, ' ');
            if(parts[0] == "settings") {
                if (parts[1] == "field_columns") {
                    field_->setColumns(stoi(parts[2]));
                }
                if (parts[1] == "field_rows") {
                    field_->setRows(stoi(parts[2]));
                }
                if (parts[1] == "your_botid") {
                    botAI_->setBotId(stoi(parts[2]));
                }
            } else if(parts[0] == "update") { /* new field data */
                if (parts[2] == "field") {
                    std::string data = parts[3];
                    field_->parseFromString(data); /* Parse Field with data */
                }
            } else if(parts[0] == "action") {
                if (parts[1] == "move") { /* move requested */
                    int column = botAI_->makeTurn();
                    field_->addDisc(column, botAI_->getBotId());
                    std::cout << "place_disc "  << column << std::endl;
                }
            }
            else { 
                std::cout << "unknown command" << std::endl;
            }
		}
	}
	~BotParser() {
		delete field_;
		delete botAI_;
	}
private:
	Field *field_;
	BotAI *botAI_;
};