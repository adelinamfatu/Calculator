#include "pch.h"
#include "BinaryFile.h"
using namespace std;

const char* BinaryFile::binaryName = "FisierBinar.bin";

void BinaryFile::persist(char* sir, char var)
{
	if (verifyVariable(var) == true)
	{
		ofstream h(BinaryFile::binaryName, ios::binary | ios::app);
		if (!h)
		{
			cout << "Fisierul nu a putut fi deschis." << endl;
		}
		else
		{
			double d;
			sscanf_s(sir, "%lf", &d);
			h.write((char*)&d, sizeof(double));
			h.write((char*)&var, sizeof(char));
			h.close();
		}
	}
	else
	{
		cout << "Introducere eronata. Variabila utilizata anterior." << endl;
	}
}

bool BinaryFile::verifyVariable(char var)
{
	ifstream f(binaryName, ios::binary);
	if (!f)
	{
		cout << "Fisierul nu a putut fi deschis.";
	}
	else
	{
		while (!f.eof())
		{
			double copy;
			char v;
			f.read((char*)&copy, sizeof(double));
			f.read((char*)&v, sizeof(char));
			if (v == var)
			{
				f.close();
				return false;
			}
		}
		f.close();
		return true;
	}
	return false;
}

bool BinaryFile::retrieveVariable(char var, double* result)
{
	ifstream f(binaryName, ios::binary);
	if (!f)
	{
		cout << "Fisierul nu a putut fi deschis.";
	}
	else
	{
		while (!f.eof())
		{
			double copy;
			char v;
			f.read((char*)&copy, sizeof(double));
			f.read((char*)&v, sizeof(char));
			if (v == var)
			{
				*result = copy;
				f.close();
				return true;
			}
		}
		f.close();
	}
	return false;
}