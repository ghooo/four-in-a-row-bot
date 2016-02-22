#include <iostream>
#include "botParser.h"
using namespace std;
int main(int argc, char **argv) {
	int difficulty = 47;
	if(argc > 1) {
		difficulty = atoi(argv[1]);		
	}
 	srand(time(NULL)*difficulty);
	// srand(difficulty);
	// srand(stoi(argv[2]));
	// srand(stoi(argv[2])*rand());
	BotParser botParser(difficulty);
	botParser.run();
	return 0;
}