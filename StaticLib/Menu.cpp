#include "pch.h"
#include "Menu.h"
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include "Equation.h"
using namespace std;

void Menu::displayMenu()
{
	while (true)
	{
		system("CLS");
		cout << "Selectati una din urmatoarele optiuni: " << endl;
		cout << "1. Citirea ecuatiei din fisier." << endl;
		cout << "2. Citirea ecuatiei de la tastatura." << endl;
		cout << "3. Exit." << endl;
		char x;
		cin >> x;
		while (x != '1' && x != '2' && x != '3')
		{
			cout << "Introducere eronata." << endl;
			cin >> x;
		}
		if (x == '1')
		{
			displayFileMenu();
		}
		else if (x == '2')
		{
			displayConsoleMenu();
		}
		else
			break;
	}
}

void Menu::displayFileMenu()
{
	system("CLS");
	cout << "Introduceti numele fisierului:" << endl;
	cin >> ws;
	char* fileName = new char[100];
	cin.getline(fileName, 100);
	ifstream f(fileName);
	if (f.is_open())
	{
		displayOutputMenu(&f, fileName);
	}
	else
	{
		cout << "Nu a fost gasit fisierul. Apasati orice tasta pentru a reveni la meniul principal." << endl;
		char y;
		cin >> y;
	}
}

void Menu::displayConsoleMenu()
{
	system("CLS");
	cout << "Introduceti ecuatia: ";
	cin >> ws;
	char* eq = new char[100];
	cin.getline(eq, 100);
	Equation equation(eq);
	char* result = equation.calculateAndPrint();
	cout << eq << "=" << result << endl;
	storeResultMenu(result);
	cout << "Introduceti orice caracter pentru revenirea la meniul principal." << endl;
	char c;
	cin >> c;
}

void Menu::storeResultMenu(char* result)
{
	if (strcmp(result, "eroare") != 0)
	{
		cout << "Selectati una dintre urmatoarele optiuni: " << endl;
		cout << "1. Pastrarea rezultatului intr-o variabila pentru folosirea lui in ecuatia urmatoare." << endl;
		cout << "2. Revenire la meniul principal." << endl;
		char x;
		cin >> x;
		while (x != '1' && x != '2')
		{
			cin >> x;
		}
		if (x == '1')
		{
			cout << "Introduceti numele variabilei (un caracter, de la a la z): ";
			char var;
			cin >> var;
			while (isalpha(var) == 0)
			{
				cout << "Introducere eronata." << endl;
				cout << "Introduceti numele variabilei (un caracter, de la a la z): ";
				cin >> var;
			}
			Equation::persistVariable(result, var);
		}
	}
}

void Menu::displayOutputMenu(ifstream* f, char* fileName)
{
	cout << "Selectati una dintre urmatoarele optiuni: " << endl;
	cout << "1. Afisarea rezultatului la consola." << endl;
	cout << "2. Afisarea rezultatului in fisier." << endl;
	char x;
	cin >> x;
	while (x != '1' && x != '2')
	{
		cin >> x;
	}
	if (x == '1')
	{
		while (!(f->eof()))
		{
			string eq;
			getline(*f, eq);
			char* s = new char[100];
			strcpy_s(s, 100, eq.c_str());
			Equation equation(s);
			char* result = equation.calculateAndPrint();
			cout << eq << "=" << result << endl;
		}
	}
	else
	{
		char* outputName = generateOutputFileName(fileName);
		ofstream g(outputName);
		while (!(f->eof()))
		{
			string eq;
			getline(*f, eq);
			char* s = new char[100];
			strcpy_s(s, 100, eq.c_str());
			Equation equation(s);
			char* result = equation.calculateAndPrint();
			g << eq << "=" << result << endl;
		}
		cout << "Rezultatele au fost scrise in fisierul " << outputName << endl;
	}
	cout << "Apasati orice caracter pentru a reveni la meniul principal." << endl;
	char y;
	cin >> y;
}

char* Menu::generateOutputFileName(char* fileName)
{
	char* outputName = new char[100];
	int i;
	for (i = strlen(fileName); i >= 0; i--)
	{
		if (fileName[i] == '.')
		{
			break;
		}
	}
	strncpy_s(outputName, 100, fileName, i);
	strncat_s(outputName, 100, "_rezultate.txt", strlen("_rezultate.txt"));
	return outputName;
}
