#include <iostream>
#include "botParser.h"
using namespace std;
int main(int argc, char **argv) {
	int difficulty = 2;
	if(argc > 1) {
		difficulty = atoi(argv[1]);		
	}
	srand(time(NULL)*difficulty);
	BotParser botParser(difficulty);
	botParser.run();
	return 0;
}