#include <iostream>
#include "../src/field.h"
#include "../src/minimaxAI.h"
using namespace std;
void testIsWinning1() {
	Field *field = new Field(7,6);
	field->parseFromString("0,0,1,2,1,0,0,0,0,1,1,1,2,0,0,0,2,1,2,1,0,0,0,1,1,2,2,0,0,2,1,2,1,2,0,0,2,2,1,2,1,2");
	MinimaxAI *botAI = new MinimaxAI(field);
	if(botAI->isWinning(field,1)) cout << "testIsWinning Failed" << endl;
	else cout << "testIsWinning Passed" << endl;
}
void testIsWinning2() {
	Field *field = new Field(7,6);
	field->parseFromString("0,0,0,0,0,0,0;0,0,0,1,0,0,0;0,0,0,2,0,0,0;0,0,0,1,2,0,0;0,1,2,2,1,2,0;0,2,1,1,1,2,2");
	MinimaxAI *botAI = new MinimaxAI(field);
	if(botAI->isWinning(field,1)) cout << "testIsWinning Failed" << endl;
	else cout << "testIsWinning Passed" << endl;
}
void testIsWinning3() {
	Field *field = new Field(7,6);
	field->parseFromString("0,0,0,0,0,0,0;0,0,0,1,0,0,0;0,0,0,2,0,0,0;0,0,1,1,2,0,0;0,1,2,2,1,2,0;0,2,1,1,1,2,2");
	MinimaxAI *botAI = new MinimaxAI(field);
	if(botAI->isWinning(field,2)) cout << "testIsWinning Passed" << endl;
	else cout << "testIsWinning Failed" << endl;
}
void testMakeTurn1() {
	Field *field = new Field(7,6);
	field->parseFromString("0,0,0,0,0,0,0;0,0,0,1,0,0,0;0,0,0,2,0,0,0;0,0,0,1,2,0,0;0,1,2,2,1,2,0;0,2,1,1,1,2,0");
	MinimaxAI *botAI = new MinimaxAI(field);
	botAI->setBotId(1);
	if(botAI->makeTurn()==6) cout << "testMakeTurn1 Passed" << endl;
	else cout << "testMakeTurn1 Failed" << endl;
}
void testEvaluate() {
	Field *field = new Field(7,6);
	field->parseFromString("0,0,0,0,0,0,0;0,0,0,1,0,0,0;0,0,0,2,0,0,0;0,0,0,1,2,0,0;0,1,2,2,1,2,0;0,2,1,1,1,2,2");
	MinimaxAI *botAI = new MinimaxAI(field);
	botAI->setBotId(1);
	field->addDisc(2,1);
	if(botAI->evaluate(field)==-1000000) cout << "testEvaluate Passed" << endl;
	else cout << "testEvaluate Failed" << endl;
}
int main() {
	testIsWinning1();
	testIsWinning2();
	testIsWinning3();
	testMakeTurn1();
	testEvaluate();
	return 0;
}