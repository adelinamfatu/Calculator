#include "pch.h"
#include "CppUnitTest.h"
#define private public
#include "../StaticLib/EquationOperand.h"
#undef private
#include "../StaticLib/MyOperand.h"
#include "../StaticLib/NumberOperand.h"
#include "../StaticLib/Equation.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{
	TEST_CLASS(UnitTest)
	{
	public:
		/*TEST_METHOD(build_vectors_1)
		{
			EquationOperand eo("3*(1+2)+4");
			eo.buildVectors();
			NumberOperand* op1;
			op1 = (NumberOperand*)eo.operands[0];
			NumberOperand nb = NumberOperand("3");
			Assert::IsTrue(*op1==nb);

			EquationOperand* op2;
			op2 = (EquationOperand*)eo.operands[1];
			EquationOperand nb2 = EquationOperand("1+2");
			Assert::IsTrue(*op2 == nb2);

			NumberOperand* op3;
			op3 = (NumberOperand*)eo.operands[2];
			NumberOperand nb3 = NumberOperand("4");
			Assert::IsTrue(*op3 == nb3);

			Assert::AreEqual(eo.operators[0], '*');
			Assert::AreEqual(eo.operators[1], '+');
		}*/

		/*TEST_METHOD(build_vectors_2)
		{
			EquationOperand eo("3*(1+2)");
			eo.getValue();
			NumberOperand* op1;
			op1 = (NumberOperand*)eo.operands[0];
			NumberOperand nb = NumberOperand("3");
			Assert::IsTrue(*op1 == nb);

			EquationOperand* op2;
			op2 = (EquationOperand*)eo.operands[1];
			EquationOperand nb2 = EquationOperand("1+2");
			Assert::IsTrue(*op2 == nb2);

			Assert::AreEqual(eo.operators[0], '*');
		}*/

		/*TEST_METHOD(build_vectors_3)
		{
			EquationOperand eo("[3*(1+2)]+5");
			eo.getValue();
			EquationOperand* op1;
			op1 = (EquationOperand*)eo.operands[0];
			EquationOperand nb = EquationOperand("3*(1+2)");
			Assert::IsTrue(*op1 == nb);

			NumberOperand* op2;
			op2 = (NumberOperand*)eo.operands[1];
			NumberOperand nb2 = NumberOperand("5");
			Assert::IsTrue(*op2 == nb2);
			Assert::AreEqual(eo.operators[0], '+');
		}*/

		/*TEST_METHOD(number_operand_constructor_double)
		{
			double d = 5.4;
			NumberOperand nb(d);
			NumberOperand op("5.4000");
			Assert::IsTrue(nb==op);
			Assert::IsTrue(nb.getValue() == d);
		}*/

		TEST_METHOD(test_ecuatie_complexa_1)
		{
			EquationOperand eo("[40+(5-1)]*2");
			double d = eo.getValue();
			Assert::IsTrue(abs(d - 88.0) < 0.00001);
		}

		TEST_METHOD(test_ecuatie_complexa_2)
		{
			EquationOperand eo("[(2*3)^2]/4-(6+2)#3");
			double d = eo.getValue();
			Assert::IsTrue(abs(d - 7.0) < 0.00001);
		}

		TEST_METHOD(test_ecuatie_complexa_3)
		{
			EquationOperand eo("2*3.2");
			double d = eo.getValue();
			Assert::IsTrue(abs(d - 6.4) < 0.00001);
		}

		TEST_METHOD(test_ecuatie_complexa_4)
		{
			EquationOperand eo("24342343.0002-3");
			double d = eo.getValue();
			Assert::IsTrue(abs(d - 24342340.0002) < 0.00001);
		}

		TEST_METHOD(test_ecuatie_complexa_5)
		{
			EquationOperand eo("(-3*2)*4");
			double d = eo.getValue();
			Assert::IsTrue(abs(d + 24) < 0.00001);
		}

		TEST_METHOD(test_ecuatie_complexa_6)
		{
			EquationOperand eo("-3*2");
			double d = eo.getValue();
			Assert::IsTrue(abs(d + 6) < 0.00001);
		}

		TEST_METHOD(test_ecuatie_complexa_7)
		{
			EquationOperand eo("2*(-3)");
			double d = eo.getValue();
			Assert::IsTrue(abs(d + 6) < 0.00001);
		}

		TEST_METHOD(test_ecuatie_complexa_8)
		{
			char* sir = "2 *    3 - 8";
			Equation eq(sir);
			char* d = eq.calculateAndPrint();
			Assert::IsTrue(strcmp(d, "-2") == 0);
		}

		TEST_METHOD(test_ecuatie_complexa_9)
		{
			char* sir = "  2 *    3 - 8  ";
			Equation eq(sir);
			char* d = eq.calculateAndPrint();
			Assert::IsTrue(strcmp(d, "-2") == 0);
		}

		TEST_METHOD(test_eroare_1)
		{
			char* sir = "5++";
			Equation eq(sir);
			char* d = eq.calculateAndPrint();
			Assert::IsTrue(strcmp(d, "eroare") == 0);
		}

		TEST_METHOD(test_eroare_2)
		{
			char* sir = "7+   - 4";
			Equation eq(sir);
			char* d = eq.calculateAndPrint();
			Assert::IsTrue(strcmp(d, "eroare") == 0);
		}

		TEST_METHOD(test_eroare_3)
		{
			char* sir = "5ABC";
			Equation eq(sir);
			char* d = eq.calculateAndPrint();
			Assert::IsTrue(strcmp(d, "eroare") == 0);
		}

		TEST_METHOD(test_eroare_4)
		{
			char* sir = "(1+2+7";
			Equation eq(sir);
			char* d = eq.calculateAndPrint();
			Assert::IsTrue(strcmp(d, "eroare") == 0);
		}

		TEST_METHOD(test_eroare_5)
		{
			char* sir = "1+2]+7";
			Equation eq(sir);
			char* d = eq.calculateAndPrint();
			Assert::IsTrue(strcmp(d, "eroare") == 0);
		}

		TEST_METHOD(test_eroare_6)
		{
			char* sir = "(1+2(+7";
			Equation eq(sir);
			char* d = eq.calculateAndPrint();
			Assert::IsTrue(strcmp(d, "eroare") == 0);
		}

		TEST_METHOD(test_eroare_7)
		{
			Assert::IsTrue(strcmp(getResult("4*5+(2+10])"), "eroare") == 0);
			Assert::IsTrue(strcmp(getResult("4*5+[2+10)"), "eroare") == 0);
			Assert::IsTrue(strcmp(getResult("4*5+([2+10])"), "eroare") == 0);
			Assert::IsTrue(strcmp(getResult("[4*5+[2+10]]"), "eroare") == 0);
			Assert::IsTrue(strcmp(getResult("4*5+[2+10]]"), "eroare") == 0);
			Assert::IsTrue(strcmp(getResult("[4*5+(2+10]]"), "eroare") == 0);
		}

		char* getResult(char* input)
		{
			Equation eq(input);
			char* d1 = eq.calculateAndPrint();
			return d1;
		}
	};
}
