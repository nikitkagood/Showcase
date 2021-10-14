#pragma once
#include <iostream>

using namespace std;

void showMenu();

class Calculator
{
public:
	double calculate(double a, char anOperator, double b);

//left public cause in old version I call those functions without using calculate
	double sum(double a, double b);

	double subtract(double a, double b);

	double multiply(double a, double b);

	double divide(double a, double b);

};