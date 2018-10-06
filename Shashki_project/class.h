#ifndef CLASS_H
#define CLASS_H

#include "pch.h"
#include <iostream>
#include <string>
#include <string.h>
#include <vector>
using namespace std;

class checker
{
	string coord; // кордината на поле
	string color; // цвет шашки
	bool damka; // является ли шашка дамкой
public:
	string get_coord(); // получает значение кординаты
	bool get_damka(); //получает ответ, явл ли шашка дамкой
	string get_color(); // получает цвет шашки
	void set_coord(string s);
	void set_color(string s); // устанавливает цвет шашки в значение s
	void set_damka(bool s); // устанавливает свойство дамка у шашки в значение s
	void delete_checker();
};

const int SIZE = 8;

#endif 
