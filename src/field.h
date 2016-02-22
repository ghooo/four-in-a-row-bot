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

#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

#ifndef FIELD_H
#define FIELD_H


std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems) {
	std::stringstream ss(s);
	std::string item;
	while (std::getline(ss, item, delim)) {
	    elems.push_back(item);
	}
	return elems;
}


std::vector<std::string> split(const std::string &s, char delim) {
	std::vector<std::string> elems;
	split(s, delim, elems);
	return elems;
}
class Field {
public:
	Field() {

	}
	Field(int cols, int rows) {
		cols_ = cols;
		rows_ = rows;
		lastColumn_ = -1;
		initBoard();
	}
	void setColumns(int cols) {
		cols_ = cols;
		initBoard();
	}
	void setRows(int rows) {
		rows_ = rows;
		initBoard();
	}
	void clearBoard() {
		for(int i = 0; i < cols_; i++) {
			for(int j = 0; j < rows_; j++) {
				board_[i][j] = 0;
			}
		}
	}
	bool addDisc(int col, int disc) {
		lastError_ = "";
		if(col < cols_) {
			for(int j = rows_-1; j >= 0; j--) {
				if(board_[col][j] == 0) {
					board_[col][j] = disc;
					lastColumn_ = col;
					return true;
				}
			}
			lastError_ = "Column is full.";
		} else {
			lastError_ = "Move out of bounds.";
		}
		return false;
	}
	bool removeDisc(int col) {
		if(col < cols_) {
			for(int j = 0; j < rows_; j++) {
				if(board_[col][j]) {
					board_[col][j] = 0;
					return true;
				}
			}
		}
		return false;
	}
	void parseFromString(std::string s) {
		std::replace(s.begin(), s.end(), ';', ',');
		std::vector<std::string> r = split(s,',');
		int counter = 0;
		for(int j = 0; j < rows_; j++) {
			for(int i = 0; i < cols_; i++) {
				if(board_[i][j] != stoi(r[counter])) {
					lastColumn_ = i;
				}
				board_[i][j] = stoi(r[counter]);
				counter++;
			}
		}
	}
	int getDisc(int col, int row) {
		return board_[col][row];
	}
	bool isValidMove(int col) {
		return board_[col][0] == 0;
	}
	bool is2DiscsPossible(int col) {
		return board_[col][1] == 0;
	}
	std::string getLastError() {
		return lastError_;
	}
    operator std::string() const
    {
    	std::string r = "";
    	for(int j = 0; j < rows_; j++) {
    		for(int i = 0; i < cols_; i++) {
    			if(board_[i][j] == 0) r += "...  ";
    			if(board_[i][j] == 1) r += "111  ";
    			if(board_[i][j] == 2) r += "222  ";
    		}
    		r += '\n';
    	}
    	r += '\n';
    	r += '\n';
    	return r;
    }
    bool isFull() {
    	for(int i = 0; i < cols_; i++) {
    		for(int j = 0; j < rows_; j++) {
    			if(board_[i][j] == 0) {
    				return false;
    			}
    		}
    	}
    	return true;
    }
    bool isColumnFull(int col) {
    	return board_[col][0] != 0;
    }
    int getNrColumns() {
    	return cols_;
    }
    int getNrRows() {
    	return rows_;
    }
    int getMoveRow(int col) {
		if(col < cols_) {
			for(int j = rows_-1; j >= 0; j--) {
				if(board_[col][j] == 0) {
					return j;
				}
			}
		}
		return -1;
    }
	int getLastColumn() {
		return lastColumn_;
	}
private:
	void initBoard() {
		board_ = std::vector<std::vector<int> > (cols_,std::vector<int>(rows_,0));
	}
	std::vector<std::vector<int> > board_;
	int cols_, rows_;
	std::string lastError_;
	int lastColumn_;
};


#endif //FIELD_H