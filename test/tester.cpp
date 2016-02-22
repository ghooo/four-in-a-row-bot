#include <iostream>
#include "../src/field.h"
#include "../src/minimaxAIv01.h"
#include "../src/minimaxAIv02.h"
#include "../src/minimaxAIv05.h"
#include "../src/minimaxAIv07.h"
using namespace std;
// void testIsWinning1() {
// 	Field *field = new Field(7,6);
// 	field->parseFromString("0,0,1,2,1,0,0,0,0,1,1,1,2,0,0,0,2,1,2,1,0,0,0,1,1,2,2,0,0,2,1,2,1,2,0,0,2,2,1,2,1,2");
// 	MinimaxAIv02 *botAI = new MinimaxAIv02(field);
// 	if(botAI->isWinning(field,1)) cout << "testIsWinning Failed" << endl;
// 	else cout << "testIsWinning Passed" << endl;
// }
// void testIsWinning2() {
// 	Field *field = new Field(7,6);
// 	field->parseFromString("0,0,0,0,0,0,0;0,0,0,1,0,0,0;0,0,0,2,0,0,0;0,0,0,1,2,0,0;0,1,2,2,1,2,0;0,2,1,1,1,2,2");
// 	MinimaxAIv02 *botAI = new MinimaxAIv02(field);
// 	if(botAI->isWinning(field,1)) cout << "testIsWinning Failed" << endl;
// 	else cout << "testIsWinning Passed" << endl;
// }
// void testIsWinning3() {
// 	Field *field = new Field(7,6);
// 	field->parseFromString("0,0,0,0,0,0,0;0,0,0,1,0,0,0;0,0,0,2,0,0,0;0,0,1,1,2,0,0;0,1,2,2,1,2,0;0,2,1,1,1,2,2");
// 	MinimaxAIv02 *botAI = new MinimaxAIv02(field);
// 	if(botAI->isWinning(field,2)) cout << "testIsWinning Passed" << endl;
// 	else cout << "testIsWinning Failed" << endl;
// }
// void testMakeTurn1() {
// 	Field *field = new Field(7,6);
// 	field->parseFromString("0,0,0,0,0,0,0;0,0,0,1,0,0,0;0,0,0,2,0,0,0;0,0,0,1,2,0,0;0,1,2,2,1,2,0;0,2,1,1,1,2,0");
// 	MinimaxAIv02 *botAI = new MinimaxAIv02(field);
// 	botAI->setBotId(1);
// 	if(botAI->makeTurn()==6) cout << "testMakeTurn1 Passed" << endl;
// 	else cout << "testMakeTurn1 Failed" << endl;
// }
// void testMakeTurn2() {
// 	Field *field = new Field(7,6);
// 	field->parseFromString("0,0,2,2,2,0,0;0,0,1,1,1,0,0;0,0,2,1,2,0,0;0,2,1,2,2,1,0;0,2,1,1,1,2,1;1,1,2,1,2,1,2");
// 	MinimaxAIv02 *botAI = new MinimaxAIv02(field);
// 	botAI->setBotId(2);
// 	cout << botAI->makeTurn() << endl;
// 	// if(botAI->makeTurn()!=1 && botAI->makeTurn() !=5) cout << "testMakeTurn2 Passed" << endl;
// 	// else cout << "testMakeTurn2 Failed" << endl;
// }
// void testMin() {
// 	Field *field = new Field(7,6);
// 	field->parseFromString("0,0,2,2,2,0,0;0,0,1,1,1,0,0;0,0,2,1,2,0,0;0,2,1,2,2,1,0;0,2,1,1,1,2,1;1,1,2,1,2,1,2");
// 	field->addDisc(0,2);
// 	field->addDisc(0,1);
// 	MinimaxAIv02 *botAI = new MinimaxAIv02(field);
// 	botAI->setBotId(2);
// 	cout << botAI->max(field,1).value << endl;
// 	// if(botAI->makeTurn()!=1 && botAI->makeTurn() !=5) cout << "testMakeTurn2 Passed" << endl;
// 	// else cout << "testMakeTurn2 Failed" << endl;
// }
// void testEvaluate() {
// 	Field *field = new Field(7,6);
// 	field->parseFromString("0,0,0,0,0,0,0;0,0,0,1,0,0,0;0,0,0,2,0,0,0;0,0,0,1,2,0,0;0,1,2,2,1,2,0;0,2,1,1,1,2,2");
// 	MinimaxAIv02 *botAI = new MinimaxAIv02(field);
// 	botAI->setBotId(1);
// 	field->addDisc(2,1);
// 	if(botAI->evaluate(field)==-1000000) cout << "testEvaluate Passed" << endl;
// 	else cout << "testEvaluate Failed" << endl;
// }
// 
// 
void testMinimaxAIv05() {
	Field *field = new Field(7,6);
	field->parseFromString(
	"0,0,0,0,0,0,0;"
	"0,0,0,0,0,0,0;"
	"0,0,0,0,0,0,0;"
	"0,0,0,0,0,0,0;"
	"0,0,0,0,0,0,0;"
	"2,0,1,2,0,0,0");
	MinimaxAIv05 *botAI = new MinimaxAIv05(field);
	botAI->setBotId(1);


	MinimaxField mField(field,1);

	// mField.debugMatrix();
	cout << mField.getScore(1) << endl;
}
void testMakeTurn() {
	Field *field = new Field(7,6);
	field->parseFromString(
	"2,2,1,2,0,1,0;"
	"1,2,2,1,0,2,0;"
	"2,1,1,2,0,1,1;"
	"1,2,2,1,0,2,2;"
	"1,1,1,2,0,1,2;"
	"2,1,2,1,0,1,2");
	MinimaxAIv07 *botAI = new MinimaxAIv07(field);
	botAI->setBotId(1);

	cout << botAI->makeTurn() << endl;
}
int main() {
	// testIsWinning1();
	// testIsWinning2();
	// testIsWinning3();
	// testMakeTurn1();
	// testMakeTurn2();
	// testEvaluate();
	// testMin();
	// testMinimaxAIv05();
	testMakeTurn();
	return 0;
}