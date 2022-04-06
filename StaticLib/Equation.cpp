#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <iostream>
#include <stdlib.h>
#include "pch.h"
#include "Equation.h"
#include "BinaryFile.h"
#include "EquationOperand.h"
using namespace std;

Equation::Equation(char* equation)
{
	if (equation != nullptr)
	{
		this->equation = new char[strlen(equation) + 1];
		strcpy_s(this->equation, strlen(equation) + 1, equation);
	}
}

void Equation::eliminateSpaces()
{
	int size = strlen(equation);
	for (int i = 0; i < size; i++)
	{
		if (equation[i] == ' ')
		{
			strncpy_s(equation + i, size, equation + i + 1, size - i);
			size--;
			i--;
		}
	}
}

bool Equation::isValid()
{
	eliminateSpaces();
	int size = strlen(equation);
	int nr_r = 0;
	int nr_p = 0;
	for (int i = 0; i < size; i++)
	{
		if (equation[i] == '*' || equation[i] == '/' || equation[i] == '#'
			|| equation[i] == '^' || equation[i] == '+' || equation[i] == '-') 
		{
			int j = i + 1;
			while (equation[j] == ' ')
			{
				j++;
			}
			if (equation[j] == '*' || equation[j] == '/' || equation[j] == '#'
				|| equation[j] == '^' || equation[j] == '+' || equation[j] == '-')
			{
				return false;
			}
		}
	}
	for (int i = 0; i < size; i++)
	{
		if (isdigit(equation[i]) == 0)
		{
			if (equation[i] == '[')
			{
				nr_p++;
				if (nr_p >= 2)
					return false;
				if (nr_r == 1)
					return false;
			}
			else if (equation[i] == ']')
			{
				nr_p--;
				if (nr_p < 0)
					return false;
			}
			else if (equation[i] == '(')
			{
				nr_r++;
				if (nr_r >= 2)
					return false;
			}
			else if (equation[i] == ')')
			{
				nr_r--;
				if (nr_r < 0)
					return false;
			}
			else if (equation[i] != '*' && equation[i] != '/' && equation[i] != '#'
				&& equation[i] != '+' && equation[i] != '-' && equation[i] != '^'
				&& equation[i] != ' ' && equation[i] != '.') 
			{
				return false;
			}
		}
	}
	if (nr_p != 0 || nr_r != 0)
	{
		return false;
	}
	return true;
}

char* Equation::calculateAndPrint()
{
	try
	{
		replaceCharacters();
	}
	catch (exception& e)
	{
		char* string = new char[bufferDim];
		strcpy_s(string, bufferDim, "eroare");
		return string;
	}
	if (isValid() == true)
	{
		try
		{
			EquationOperand eo(equation);
			double result = eo.getValue();
			return Equation::printValue(result);
		}
		catch (exception& e)
		{
			char* string = new char[bufferDim];
			strcpy_s(string, bufferDim, "eroare");
			return string;
		}
	}
	else
	{
		char* string = new char[bufferDim];
		strcpy_s(string, bufferDim, "eroare");
		return string;
	}
}

char* Equation::printValue(double result)
{
	char* string = new char[30];
	int decimals = result;
	if (result - decimals != 0)
	{
		sprintf_s(string, 30, "%.4lf", result);
	}
	else
	{
		sprintf_s(string, 30, "%.0lf", result);
	}
	return string;
}

void Equation::persistVariable(char* sir, char var)
{
	BinaryFile::persist(sir, var);
}

void Equation::replaceCharacters()
{
	int i;
	for (i = 0; i < strlen(equation); i++)
	{
		if (isalpha(equation[i]) != 0)
		{
			double result;
			if (BinaryFile::retrieveVariable(equation[i], &result) == true)
			{
				char* copy = new char[bufferDim];
				*copy = 0;
				strncat_s(copy, bufferDim, equation, i);
				char* convert = new char[bufferDim];
				sprintf_s(convert, bufferDim, "%.4lf", result);
				strncat_s(copy, bufferDim, convert, strlen(convert));
				strncat_s(copy, bufferDim, equation + i + 1, strlen(equation) - i);
				delete[] equation;
				equation = copy;
			}
			else
			{
				throw exception("eroare");
			}
		}
	}
}