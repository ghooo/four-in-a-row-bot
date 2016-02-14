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
#include "botAI.h"

#include <iostream>
#include <string>
#include <vector>

class BotParser {
public:
	BotParser() {
		field_ = new Field(0,0);
		botAI_ = new BotAI(field_);
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
                    botId_ = stoi(parts[2]);
                }
            } else if(parts[0] == "update") { /* new field data */
                if (parts[2] == "field") {
                    std::string data = parts[3];
                    field_->parseFromString(data); /* Parse Field with data */
                }
            } else if(parts[0] == "action") {
                if (parts[1] == "move") { /* move requested */
                    int column = botAI_->makeTurn();
                    field_->addDisc(column, botId_);
                    std::cout << std::string(*field_) << std::endl;
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
	int botId_;
};