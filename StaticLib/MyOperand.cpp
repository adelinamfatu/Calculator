#include <iostream>
#include <string>
#include "pch.h"
#include "MyOperand.h"

MyOperand::MyOperand(char* stringValue)
{
	this->stringValue = stringValue;
}

bool MyOperand::operator==(MyOperand& op)
{
	if (strcmp(stringValue, op.stringValue) == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

char* MyOperand::getStringValue()
{
	char* copy = new char[strlen(stringValue) + 1];
	copy = stringValue;
	return copy;
}