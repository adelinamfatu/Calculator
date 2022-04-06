#include <iostream>
#include <string>
#include "MyOperand.h"

#ifndef NumberOperand_h
#define NumberOperand_h
class NumberOperand : public MyOperand
{
public:
	NumberOperand(char* string);
	NumberOperand(double v);
	double getValue();
	bool operator==(MyOperand& op);
};
#endif