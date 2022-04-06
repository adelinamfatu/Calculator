#include <iostream>
#include <string>
#include "MyOperand.h"
#include "pch.h"
#include "NumberOperand.h"
using namespace std;

NumberOperand::NumberOperand(char* string):MyOperand(string)
{
}

double NumberOperand::getValue()
{
	if (value == nullptr)
	{
		value = new double;
		sscanf_s(stringValue, "%lf", value);
	}
	return *value;
}

NumberOperand::NumberOperand(double v):MyOperand(nullptr)
{
	value = new double;
	*value = v;
	stringValue = new char[100];
	sprintf_s(stringValue, 100, "%.4lf", *value);
}

bool NumberOperand::operator==(MyOperand& op)
{
	if (typeid(this).name() == typeid(op).name())
	{
		return *value == op.getValue();
	}
	else
		return false;
}