#include <iostream>
#include <map>
#include <string>
#include <windows.h>
//#include <thread>
//#include <fstream>

#include "functions.h"

using namespace std;

string command;
double a = 0.0;
double b = 0.0;
double result = 0.0;
char anOperator;

//menu is made this way to make switch construction handle string commands
map<string, int> MenuCommands{  
	{"exit", 100},
	{"1", 1},
	{"2", 2},
	{"3", 3},
	{"4", 4},
	{"5", 5},
	{"back", 98},
	{"menu", 99} 
};

int main()
{
	SetConsoleTitle(L"Simple Calc"); 

	//setlocale(LC_ALL,"Russian");
	
	showMenu();
	Calculator calc;

	while (true)
	{
		a = 0.0;
		b = 0.0;
		command.clear();
		cout << endl;

		cin >> command;
		cout << endl;

		//Обработка ошибок cin
		//Handling cin errors
		if (cin.fail()) 
		{
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			//cout << "Неверный формат данных" << endl;
			cout << "Bad data format" << endl;
		}
		else

		switch (MenuCommands[command]) {
		case 0:
			//cout << "Неверный пункт меню" << endl;
			cout << "Wrong menu item" << endl;
			break;
		case 100:
			exit(0);

		case 1:
			//cout << "Нормальный режим:" << endl;
			cout << "Standard mode:" << endl;

			while (true)
			{
				cin >> a >> anOperator >> b;

				try //handles division by 0 in such a bit overengineered way
				{
					cout << calc.calculate(a, anOperator, b) << endl;
				}
				catch (const exception& ex)
				{
					cout << "Error: " << ex.what() << endl;
				}
			}
			break;

		case 2:
			//cout << "Cложение:" << endl;
			//cout << "Введите число 1: ";
			cout << "Addition:" << endl;
			cout << "Input number 1: ";
			cin >> a;
			//cout << "Введите число 2: ";
			cout << "Input number 2: ";
			cin >> b;

			cout << calc.sum(a, b) << endl;
			break;

		case 3:
			//cout << "Вычитание:" << endl;
			cout << "Subtraction:" << endl;
			cout << "Input number 1: ";
			cin >> a;
			cout << "Input number 2: ";
			cin >> b;

			cout << calc.subtract(a, b) << endl;
			break;

		case 4:
			//cout << "Умножение:" << endl;
			cout << "Multiplication:" << endl;
			cout << "Input number 1: ";
			cin >> a;
			cout << "Input number 2: ";
			cin >> b;

			cout  << calc.multiply(a, b) << endl;
			break;

		case 5:
			//cout << "Деление:" << endl;
			cout << "Division:" << endl;
			cout << "Input number 1: ";
			cin >> a;
			cout << "Input number 2: ";
			cin >> b;

			cout << calc.divide(a, b) << endl;
			break;

		case 99:
			showMenu();
			break;
	
		/*default: 
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			cout << "Неверный пункт меню" << endl;
			break;*/
		}
	}
	
	return 0;
}