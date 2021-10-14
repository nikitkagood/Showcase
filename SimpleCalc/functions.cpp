#pragma once
#include <iostream>
#include "functions.h"

void showMenu()
{
	//cout << "������� ����" << endl;
	//cout << "1 - ������� �����" << endl << endl;

	//cout << "����������:" << endl;
	//cout << "2 - ������� ��� ����� (a + b)" << endl;
	//cout << "3 - ������� (a - b)" << endl;
	//cout << "4 - �������� (a x b)" << endl;
	//cout << "5 - �������� (a / b)" << endl;

	//cout << "menu - ������� ���� ������" << endl;
	//cout << "exit - �����" << endl;

	cout << "Main menu" << endl;
	cout << "1- Usual mode" << endl << endl;

	cout << "Outdated:" << endl;
	cout << "2 - add 2 numbers (a + b)" << endl;
	cout << "3 - subtract (a - b)" << endl;
	cout << "4 - multiply (a x b)" << endl;
	cout << "5 - divide (a / b)" << endl;

	cout << "menu - call menu again" << endl;
	cout << "exit - you guessed it" << endl;
}


//made this thing as a class, even though I realize it's not neccessary
//the same with try-catch

double Calculator::calculate(double a, char anOperator, double b)
{

	if (anOperator == '/' && b == 0)
	{
		throw exception("Can't divide by 0!");
	}

	if (cin.fail())
	{
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		//cout << "�������� ������ ������" << endl;
		cout << "Bad data format" << endl;
		a = 0.0;
		b = 0.0;
		anOperator = '\0';
	}

	switch (anOperator)
	{
	case '+':
		return sum(a, b);
	case '-':
		return subtract(a, b);
	case '*':
		return multiply(a, b);
	case '/':
		return divide(a, b);
	default:
		return 0;
	}
}


double Calculator::sum(double a, double b)
{
	return a + b;
}

double Calculator::subtract(double a, double b)
{
	return a - b;
}

double Calculator::multiply(double a, double b)
{
	return a * b;
}

double Calculator::divide(double a, double b)
{
	return a / b;
}

