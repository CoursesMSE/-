#include "pch.h"
#include <iostream>

using namespace std;
const int SIZE = 8;

class checker
{
	string coord;
	string color;
public:
	void move_checker(string new_x, string new_y);
	void delete_checker();
};

class field
{
	bool checker_is;
	string coord;
	checker bot;
public:
	void create_field(field);
};

int main()
{
	cout << "hello";
	field pole[SIZE][SIZE];
	cout << "zdarooooova";
	create_field(pole);
	cout << "xml";
	return 0;
}

void checker::delete_checker()
{

}
void checker::move_checker(string new_x, string new_y)
{
	
}
void field::create_field(field p[][8])
{

}