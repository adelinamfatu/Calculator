#include "pch.h"
#include "Menu.h"
#include <iostream>
#include <stdlib.h>
#include <fstream>
using namespace std;

class BinaryFile
{
private:
	static const char* binaryName;
public:
	static void persist(char* sir, char var);
	static bool retrieveVariable(char var, double* result);
	static bool verifyVariable(char var);
};