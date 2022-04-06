#include "pch.h"
#include <iostream>
#include <string>
#include <cctype>
#include <math.h>
#include <algorithm>
#include "MyOperand.h"
#include "NumberOperand.h"
#include "EquationOperand.h"
using namespace std;

EquationOperand::EquationOperand(char* string):MyOperand(string)
{
}

void EquationOperand::buildVectors()
{
	int i = 0;
	int contor = 0;
	indexVector = 0;
	operators = new char[bufferDim];
	operands = new MyOperand*[bufferDim];
	while (i < strlen(stringValue))
	{
		if (stringValue[i] == '-' || isdigit(stringValue[i]) != 0)
		{
			if (stringValue[i] == '-')
				i++;
			while (isdigit(stringValue[i]) != 0 || stringValue[i] == '.')
				i++;
			char* aux = new char[bufferDim];
			strncpy_s(aux, bufferDim, stringValue + contor, i - contor);
			MyOperand* op = new NumberOperand(aux);
			operands[indexVector] = op;
		}
		else
		{
			if (stringValue[i] == '[')
			{
				contor = i;
				while (stringValue[i] != ']')
					i++;
				char* aux = new char[bufferDim];
				strncpy_s(aux, bufferDim, stringValue + contor + 1, i - contor - 1);
				i++;
				MyOperand* op = new EquationOperand(aux);
				operands[indexVector] = op;
			}
			else
			{
				if (stringValue[i] == '(')
				{
					contor = i;
					while (stringValue[i] != ')')
						i++;
					char* aux = new char[bufferDim];
					strncpy_s(aux, bufferDim, stringValue + contor + 1, i - contor - 1);
					i++;
					MyOperand* op = new EquationOperand(aux);
					operands[indexVector] = op;
				}
			}
		}
		if (i != strlen(stringValue))
		{
			if (stringValue[i] == '*' || stringValue[i] == '/' ||
				stringValue[i] == '+' || stringValue[i] == '^' ||
				stringValue[i] == '#' || stringValue[i] == '-')
			{
				operators[indexVector++] = stringValue[i];
			}
			else
			{
				throw exception("eroare");
			}
		}
		contor = i + 1;
		i++;
	}
}

double EquationOperand::getValue()
{
	if (value == nullptr)
	{
		buildVectors();
		value = new double;
		*value = calculate();
	}
	return *value;
}

double EquationOperand::calculate()
{
	int i;
	double result;
	int j = 0;
	while (j < indexVector)
	{
		if (operators[j] == '^' || operators[j] == '#')
		{
			double result;
			if (operators[j] == '^')
			{
				result = pow(operands[j]->getValue(), operands[j + 1]->getValue());
			}
			else
			{
				result = pow(operands[j]->getValue(), 1 / operands[j + 1]->getValue());
			}
			NumberOperand* nb = new NumberOperand(result);
			delete operands[j];
			delete operands[j + 1];
			operands[j] = nb;
			int k = j + 1;
			//copy_n(operators + k - 1, indexVector - k, operators + k);
			for (k = j + 1; k < indexVector; k++)
			{
				operands[k] = operands[k + 1];
				operators[k - 1] = operators[k];
			}
			indexVector--;
		}
		else
		{
			j++;
		}
	}
	j = 0;
	while (j < indexVector)
	{
		if (operators[j] == '*' || operators[j] == '/')
		{
			double result;
			if (operators[j] == '*')
			{
				result = operands[j]->getValue() * operands[j + 1]->getValue();
			}
			else
			{
				if (operands[j + 1]->getValue() == 0)
				{
					throw exception("eroare");
				}
				result = operands[j]->getValue() / operands[j + 1]->getValue();
			}
			NumberOperand* nb = new NumberOperand(result);
			delete operands[j];
			delete operands[j + 1];
			operands[j] = nb;
			int k = j + 1;
			//copy_n(operators + k - 1, indexVector - k, operators + k);
			for (k = j + 1; k < indexVector; k++)
			{
				operands[k] = operands[k + 1];
				operators[k - 1] = operators[k];
			}
			indexVector--;
		}
		else
		{
			j++;
		}
	}
	j = 0;
	while (j < indexVector)
	{
		if (operators[j] == '+' || operators[j] == '-')
		{
			double result;
			if (operators[j] == '+')
			{
				result = operands[j]->getValue() + operands[j + 1]->getValue();
			}
			else
			{
				result = operands[j]->getValue() - operands[j + 1]->getValue();
			}
			NumberOperand* nb = new NumberOperand(result);
			delete operands[j];
			delete operands[j + 1];
			operands[j] = nb;
			int k = j + 1;
			char* copy = new char[indexVector];
			//copy_n(operators + k - 1, indexVector - k, operators + k);
			for (k = j + 1; k < indexVector; k++)
			{
				operands[k] = operands[k + 1];
				operators[k - 1] = operators[k];
			}
			indexVector--;
		}
		else
		{
			j++;
		}
	}
	result = operands[0]->getValue();
	delete[] operands;
	delete[] operators;
	return result;
}

EquationOperand::~EquationOperand()
{
	if (value != nullptr)
	{
		delete value;
		value = nullptr;
	}
}

bool EquationOperand::operator==(MyOperand& op)
{
	if (typeid(this).name() == typeid(op).name())
	{
		return strcmp(stringValue, op.getStringValue()) == 0;
	}
	else
		return false;
}