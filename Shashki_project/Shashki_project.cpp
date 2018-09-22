#include "pch.h"
#include <iostream>
#include <string>
#include <string.h>

using namespace std;

const int SIZE = 8;

class checker
{
	string coord; // кордината на поле
	string color; // цвет шашки
	bool damka; // является ли шашка дамкой
	bool possible_turn;
public:
	string get_coord(); // получает значение кординаты
	bool get_damka(); //получает ответ, явл ли шашка дамкой
	string get_color(); // получает цвет шашки
	bool get_possible_turn();
	void set_coord(string s);
	void set_color(string s); // устанавливает цвет шашки в значение s
	void set_damka(bool s); // устанавливает свойство дамка у шашки в значение s
	void set_possible_turn(bool s);
	void move_checker(string new_c, string old_c, checker m[][SIZE]); // передвигает шашку из кординаты old_c в кординату new_c
};

void initialization(checker m[][SIZE]);
void draw_field(checker m[][SIZE]);
bool game_over(checker m[][SIZE]);
// ДЛЯ СЛЕДУЮЩИХ ФУНКЦИЙ НЕ НАПИСАНА РЕАЛИЗАЦИЯ
string preobras(string s, bool & not_posible);
bool possible_turns_checker(string coord, checker m[][SIZE]);
bool possible_turns_eat(string coord, checker m[][SIZE]);
//КОНЕЦ------------------------------------------------
int main()
{
	setlocale(0, "Russian");
	checker massiv_iacheek[SIZE][SIZE];
	initialization(massiv_iacheek);
	draw_field(massiv_iacheek);
	string coord_choise = "", coord_new = "";
	while (!game_over(massiv_iacheek))
	{
		getline(cin, coord_choise);
		getline(cin, coord_new);
		for (int i = 0; i < SIZE; i++)
			for (int j = 0; j < SIZE; j++)
				if (massiv_iacheek[i][j].get_coord() == coord_choise)
					massiv_iacheek[i][j].move_checker(coord_new, coord_choise, massiv_iacheek);
		draw_field(massiv_iacheek);
	}
	return 0;
};
string checker::get_color()
{
	return color;
}
string checker::get_coord()
{
	return coord;
}
bool checker::get_damka()
{
	return damka;
}
bool checker::get_possible_turn()
{
	return possible_turn;
}
void checker::set_coord(string s)
{
	coord = s;
}
void checker::set_color(string s)
{
	color = s;
}
void checker::set_damka(bool s)
{
	damka = s;
}
void checker::set_possible_turn(bool s)
{
	possible_turn = s;
}
void initialization(checker m[][SIZE])
{
	string str = "";
	for (int i = 0; i < SIZE; i++)
		for (int j = 0; j < SIZE; j++)
		{
			str += char(j + 65);
			str += char(i + 49);
			m[i][j].set_coord(str);
			m[i][j].set_color("");
			m[i][j].set_damka(false);
			m[i][j].set_possible_turn(false);
			if (i >= 0 && i <= 2 && (i + j) % 2 == 1)
				m[i][j].set_color("black");
			if (i >= 5 && i < SIZE && (i + j) % 2 == 1)
				m[i][j].set_color("white");
			str = "";
		}
}
void draw_field(checker m[][SIZE])
{
	for (int i = -1; i < SIZE; i++)
	{
		for (int k = 0; k <= (SIZE + 1) * 2 + 1; k++)
			cout << '-';
		cout << endl;
		for (int j = -1; j < SIZE; j++)
		{
			cout << '|';
			if (j == -1)
			{
				if (i != -1)
					cout << char(i + 49) << '|';
				else
					cout << ' ' << '|';
			}
			else if (i == -1)
			{
				if (j != -1)
					cout << char(j + 65);
				else
					cout << ' ';
			}
			else
			{
				if (m[i][j].get_color() == "white")
					cout << 'Б';
				else if (m[i][j].get_color() == "black")
					cout << 'Ч';
				else
					cout << ' ';
			}
		}
		cout << '|' << endl;
		if (i == -1)
		{
			for (int k = 0; k <= (SIZE + 1) * 2 + 1; k++)
				cout << '-';
			cout << endl;
		};
	}
	for (int k = 0; k <= (SIZE + 1) * 2 + 1; k++)
		cout << '-';
	cout << endl;
};
bool game_over(checker m[][SIZE])
{
	int k_black = 0, k_white = 0;
	for (int i = 0; i < SIZE; i++)
		for (int j = 0; j < SIZE; j++)
			if (m[i][j].get_color() == "black")
				k_black++;
			else if (m[i][j].get_color() == "white")
				k_white++;
	if (k_white == 0 || k_black == 0)
		return true;
	return false;
}
void checker::move_checker(string new_c, string old_c, checker m[][SIZE])
{
	string color;
	for (int i = 0; i < SIZE; i++)
		for (int j = 0; j < SIZE; j++)
			if (m[i][j].get_coord() == old_c)
			{
				color = m[i][j].get_color();
				m[i][j].set_color("");
			}
	for (int i = 0; i < SIZE; i++)
		for (int j = 0; j < SIZE; j++)
			if (m[i][j].get_coord() == new_c)
				m[i][j].set_color(color);
}
string preobras(string s, bool & not_posible)
{
	string str_res = "";
	/* Функция получает на вход строку s. Задача - преоразовать ее в понятную для компа версию. Пример такой версии: A6, B5, G7, H1
	Если строка соответсвует нормам(цифры только от 1 до 8, буквы только от A до H), то возомжны два случая:
	1) поменять цифру и букву местами
	пример : из кординаты 3A нужно сделать корднату A3
	2) поменять регистр буквы
	пример 1: из кординаты a6 нужно сделать кординату A6, из b1 - B1.
	иначе параметр not_possible установить в истину. 
	*/
	return str_res;
}
bool possible_turns(string coord, checker m[][SIZE])
{
	bool flag = false;
	/* Функия должна возвращать true, если есть возможные ходы по полю(без поедания).
	Ходы осуществляются по направлениям: С-В, С-З, Ю-В, Ю-З на расстояние 1 клетки. Если по одному из направлений в кординате стоит любая шашка, 
	то ход в ту кординату невозможен, иначе - возможен.
	Если ход возможен, то установливает значение true в possible_turn для обьекта с кординатой, в которую этот ход возможен.
	*/
	//НЕ ХВАТАЕТ ВХОДНЫХ ДАННЫХ, НУЖНЫ КООРДИНАТЫ ТОЧКИ, А ЕСЛИ ОНИ И ПРЕДАЮТСЯ(В COORD), ТО КАК-ТО НЕ ТАК 
	/*
	for (int i = 0; i < SIZE; i++)
		for (int j = 0; j < SIZE; j++)
			if (coord = m[i][j].get_coord)
			{
				if (m[i][j].get_color() = "white")
				{
					if ((m[i + 1][j - 1].get_color() = "") || (m[i + 1][j + 1].get_color() = ""))
						flag = true;
				}
				else
				{
					if ((m[i - 1][j - 1].get_color() = "") || (m[i - 1][j + 1].get_color() = ""))
						flag = true;
				}
			}
			*/
	return flag;
}
bool possible_turns_eat(string coord, checker m[][SIZE])
{
	bool flag = true;
	/* Функия должна возвращать true, если есть возможные ходы по полю(с поеданием) 
	Если по направлениям С-В, С-З, Ю-В, Ю-З на расстояни 1 клетки есть вражеская шашка, то ход возможен, иначе - невозможен.
	Если ход возможен, то установливает значение true в possible_turn для обьекта с кординатой, в которую этот ход возможен.
	*/
	return flag;
}



