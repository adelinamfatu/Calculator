#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Menu
{
public:
	static void displayMenu();
private:
	static void displayFileMenu();
	static void displayConsoleMenu();
	static void displayOutputMenu(ifstream* f, char* fileName);
	static char* generateOutputFileName(char* fileName);
	static void storeResultMenu(char* result);
};
