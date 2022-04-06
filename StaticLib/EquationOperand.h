#include <iostream>
#include <string>
#include <cctype>
#include "MyOperand.h"
#include "NumberOperand.h"
using namespace std;

#ifndef EquationOperand_h
#define EquationOperand_h
class EquationOperand : public MyOperand
{
private:
	double* value;
	char* operators;
	int indexVector;
	MyOperand** operands;
	const int bufferDim = 100;
	void buildVectors();
	double calculate();
public:
	EquationOperand(char* string);
	double getValue();
	~EquationOperand();
	bool operator==(MyOperand& op);
};
#endif