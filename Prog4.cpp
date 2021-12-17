#include "..\Table\Table.h"
#include "..\StaticLib1\Student.h"
#include <iostream>
#include <string>
using namespace Students;
using namespace Prog7b;

const std::string Names[] = { "Unknown", "Junior", "Senior","Graduete" };
const std::string Menu[] = { "1. Add Student", "2. Find Student",
"3. Delete Student", "4. Change Student data",
"5. Show all", "6. Use an Iterator",
"7. Check the constant object", "0. Quit" },

Choice = "Make your choice",
Msg = "You are wrong; repeate please";
int Answer(const std::string alt[], int n);
int Add(Table &), Find(Table &), Remove(Table &), Replace(Table &), ShowAll(Table &), Iter(Table &),
ConstObj(Table &);
int(*Funcs[])(Table &) = { nullptr, Add, Find, Remove, Replace, ShowAll, Iter, ConstObj };
const int Num = sizeof(Menu) / sizeof(Menu[0]);
int main()
{
	Table ar;
	int ind;
	try {
		while (ind = Answer(Menu, Num))
			Funcs[ind](ar);
		std::cout << "That's all. Buy!" << std::endl;
	}
	catch (const std::exception &er)
	{
		std::cout << er.what() << std::endl;
	}
	return 0;
}
int Answer(const std::string alt[], int n)
{
	int answer;
	std::string prompt = Choice;
	std::cout << "\nWhat do you want to do:" << std::endl;
	for (int i = 0; i < n; i++)
		std::cout << alt[i].c_str() << std::endl;
	do {
		std::cout << prompt.c_str() << ": -> ";
		prompt = Msg;
		std::cin >> answer;
		if (!std::cin.good()) {
			std::cout << "Error when number of choice was entered; \nRepeat, please." << std::endl;
			std::cin.ignore(80, '\n');
			std::cin.clear();
		}
	} while (answer < 0 || answer >= n);
	std::cin.ignore(80, '\n');
	return answer;
}
const std::string Sh[] = { "1. Junior", "2. Senior","3. Graduete", "0. Quit" };
const int NumSh = sizeof(Sh) / sizeof(Sh[0]);
int Add(Table &a)
{
	Student *ptr = nullptr;
	Junior c;
	Senior p;
	Graduete d;
	int ans, code;
	while (ans = Answer(Sh, NumSh)) {
		std::cout << "Enter a student code: --> " << std::endl;
		std::cin >> code;
		if (!std::cin.good())
			throw std::exception("Error when a student code was entered");
		switch (ans) {
		case 1:
			std::cout << "Enter information about Junior: --> " << std::endl;
			ptr = &c;
			break;
		case 2:
			std::cout << "Enter information about Senior: --> " << std::endl;
			ptr = &p;
			break;
		case 3:
			std::cout << "Enter information about Graduete: --> " << std::endl;
			ptr = &d;
			break;
		}
		std::cin >> (*ptr);
		if (!std::cin.good())
			throw std::exception("Error when shape values were entered");
		std::cin.ignore(80, '\n');
		if (a.insert(code, ptr))
			std::cout << "Ok" << std::endl;
		else
			std::cout << "Duplicate code" << std::endl;
	}
	return 0;
}
int Find(Table &a)
{
	int code;
	Table::Const_Iterator it;
	const Student *ptr = nullptr;
	std::cout << "Enter a student code: --> ";
	std::cin >> code;
	if (!std::cin.good())
		throw std::exception("Error when a student code was entered");
	it = a.find(code);
	if (it == a.end()) {
		std::cout << "The Student with Code \"" << code << "\" is absent in container"
			<< std::endl;
		return -1;
	}
	ptr = (*it).second;
	std::cout << "The Student with Code \"" << (*it).first
		<< "\" is a " << Names[ptr->iAm()]
		<< std::endl;
	std::cout << (*ptr) << std::endl;
	//std::cout << "It's perimeter is equal to " << ptr->perimeter()
		//<< " and it's area is equal to " << ptr->area() << std::endl;
	return 0;
}
int Remove(Table &a)
{
	int code;
	const Student *ptr = nullptr;
	std::cout << "Enter a student code: --> ";
	std::cin >> code;
	if (!std::cin.good())
		throw std::exception("Error when a student code was entered");
	if (a.remove(code))
		std::cout << "Ok" << std::endl;
	else
		std::cout << "The Student with code \"" << code << "\" is absent in container"
		<< std::endl;
	return 0;
}
int Replace(Table &a)
{
	Student *ptr = nullptr;
	Junior c;
	Senior p;
	Graduete d;
	std::string name;
	int code;
	std::cout << "Enter a student code: --> ";
	std::cin >> code;
	if (!std::cin.good())
		throw std::exception("Error when a student code was entered");
	int ans;
	ans = Answer(Sh, NumSh);
	switch (ans) {
	case 1:
		std::cout << "Enter information about Junior: --> ";
		ptr = &c;
		break;
	case 2:
		std::cout << "Enter information about Senior: --> ";
		ptr = &p;
		break;
	case 3:
		std::cout << "Enter information about Graduete: --> ";
		ptr = &d;
		break;
	}
	std::cin >> (*ptr);
	if (!std::cin.good())
		throw std::exception("Error when student values were entered");
	std::cin.ignore(80, '\n');
	if (a.replace(code, ptr))
		std::cout << "Ok" << std::endl;
	else
		std::cout << "The Student with Code \"" << code << "\" is absent in container"
		<< std::endl;
	return 0;
}
int ShowAll(Table &a)
{
	Table::Const_Iterator it;
	for (it = a.begin(); it != a.end(); ++it)
		std::cout << (*it) << std::endl;
	return 0;
}
int Iter(Table &a)
{
	std::cout << "Output of all ratings in the container" << std::endl;
	Table::Const_Iterator it;
	std::pair<int, Student*> p;
	const Student *pSh = nullptr;
	int *ptr = new int[6],n;
	for (it = a.begin(); it != a.end(); ++it) {
		p = *it;
		pSh = p.second;
		n=pSh->Estim(ptr);
		std::cout << Names[pSh->iAm()] << " \"" << p.first;
		if (n == 3)
			std::cout << "\": evaluations of the supervisor, reviewer and the GEC: ";
		else
			std::cout << "\": Estimates:";
			for (int i = 0; i < n; ++i) {
				if(i==4&&n==6)
					std::cout << "; evaluations of the supervisor, reviewer and the GEC: ";
				std::cout << ptr[i] << " ";
		}

			std::cout << std::endl;
	}
	return 0;
}
int ConstObj(Table &par)
{
	const Table a(par);
	int code;
	Table::Const_Iterator res;
	std::cout << "Enter a student code: --> ";
	std::cin >> code;
	if (!std::cin.good())
		throw std::exception("Error when a student code was entered");
	res = a.find(code);
	if (res != a.end()) {
		std::cout << "The Shape with Name \"" << res->first << "\" is a "
			<< Names[res->second->iAm()]
			<< std::endl;
		std::cout << *(res->second) << std::endl;
			//hstd::cout << "Its perimeter is equal to " << res->second << std::endl;
	}
	else
		std::cout << "The Shape with Name \"" << code << "\" is absent in container"
		<< std::endl;
	return 0;
}
