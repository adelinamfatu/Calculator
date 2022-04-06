#include <iostream>
#include <string>

#ifndef Operand_h
#define Operand_h
class MyOperand
{
protected:
	MyOperand* op;
	char* stringValue;
	double* value = nullptr;
public:
	MyOperand(char* stringValue);
	virtual double getValue() = 0;
	virtual bool operator==(MyOperand& op);
	char* getStringValue();
};
#endif
