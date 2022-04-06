#include <iostream>
#include <string>
using namespace std;

#ifndef Equation_h
#define Equation_h
class Equation
{
private:
	char* equation;
	const int bufferDim = 30;
public:
	Equation(char* equation);
	//~Equation();
	void eliminateSpaces();
	bool isValid();
	char* calculateAndPrint();
	static char* printValue(double result);
	static void persistVariable(char* sir, char var);
	void replaceCharacters();
};
#endif

