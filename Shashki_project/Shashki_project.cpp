#include "pch.h"
#include <iostream>
#include <string>
#include <string.h>
#include <vector>

using namespace std;

const int SIZE = 8;

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
	void move_checker(string new_c, string old_c, checker m[][SIZE]); // передвигает шашку из кординаты old_c в кординату new_c
};

void initialization(checker m[][SIZE]);
void draw_field(checker m[][SIZE], vector <string> *m_pos);
bool game_over(checker m[][SIZE]);
// ДЛЯ СЛЕДУЮЩИХ ФУНКЦИЙ НЕ НАПИСАНА РЕАЛИЗАЦИЯ
string preobras(checker m[][SIZE] ,string s, bool & not_posible);
void possible_turns(string coord, checker m[][SIZE], vector <string> *m_pos);
void possible_turns_eat(string coord, checker m[][SIZE], vector <string> *m_pos);
bool possible(string coord, vector <string> *m_pos);
void proverka(vector <string> *m_pos, string coord, bool error);
//КОНЕЦ------------------------------------------------
int main()
{
	setlocale(0, "Russian");
	checker massiv_iacheek[SIZE][SIZE];
	initialization(massiv_iacheek);
	draw_field(massiv_iacheek);
	string coord_choise = "", coord_new = "";
	vector <string> vector_pos(20);
	bool black_turn = false;
	while (!game_over(massiv_iacheek))
	{
		bool error = true;
		while (error)
		{
			getline(cin, coord_choise);
			preobras(massiv_iacheek, coord_choise, error);
			if ((error) || ((black_turn && (opr_color(coord_choise, massiv_iacheek) == "white") && (!black_turn && (opr_color(coord_choise, massiv_iacheek) == "black")))
				continue;
			possible_turns(coord_choice, massiv_iacheek, &vector_pos);
			possible_turns_eat(coord_choice, massiv_iacheek, &vector_pos);
			proverka(&vector_pos, coord_choise, error);
			if (error)
				cout << "Введите другие кординаты"
		};
		getline(cin, coord_new);
		for (int i = 0; i < SIZE; i++)
			for (int j = 0; j < SIZE; j++)
				if (massiv_iacheek[i][j].get_coord() == coord_choise)
					massiv_iacheek[i][j].move_checker(coord_new, coord_choise, massiv_iacheek);
		draw_field(massiv_iacheek, vector_pos);
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
			if (i >= 0 && i <= 2 && (i + j) % 2 == 1)
			{
				m[i][j].set_color("black");
				m[i][j].set_damka(false);
			}
			if (i >= 5 && i < SIZE && (i + j) % 2 == 1)
			{
				m[i][j].set_color("white");
				m[i][j].set_damka(false);
			}
			str = "";
		}
}
void draw_field(checker m[][SIZE], vector <string> *m_pos)
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
				else if (possible(m_pos, m[i][j].get_coord()))
					cout << 'p';
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
string preobras(string m[][SIZE] ,string s, bool & not_posible)
{
	string str_res = "";
	/* Функция получает на вход строку s. Задача - преоразовать ее в понятную для компа версию. Пример такой версии: A6, B5, G7, H1
	Если строка соответсвует нормам(цифры только от 1 до 8, буквы только от A до H), то возомжны два случая:
	1) поменять цифру и букву местами
	пример : из кординаты 3A нужно сделать корднату A3
	2) поменять регистр буквы
	пример 1: из кординаты a6 нужно сделать кординату A6, из b1 - B1.
	иначе параметр not_possible установить в истину. 
	3) Функция проверяет, выбрали ли пользователь пустую строку и если да, то передает значение false
	*/
	return str_res;
}
void possible_turns(string coord, checker m[][SIZE], vector <string> *m_pos)
{
	m_pos->clear();
	for (int i = 0; i < SIZE; i++)
		for (int j = 0; j < SIZE; j++)
			if (coord == m[i][j].get_coord())
			{
				if (m[i][j].get_color() == "white")
				{
					if (m[i + 1][j - 1].get_color() == "")
						m_pos->push_back(m[i + 1][j - 1].get_coord());
					if (m[i + 1][j + 1].get_color() == "")
						m_pos->push_back(m[i + 1][j + 1].get_coord());
				}
				else if (m[i][j].get_color() == "black")
				{
					if (m[i - 1][j - 1].get_color() == "")
						m_pos->push_back(m[i - 1][j - 1].get_coord());
					if (m[i - 1][j + 1].get_color() == "")
						m_pos->push_back(m[i - 1][j + 1].get_coord());
				}
			}
}
void possible_turns_eat(string coord, checker m[][SIZE], vector <string> *m_pos)
{
	for (int i = 0; i < SIZE; i++)
		for (int j = 0; j < SIZE; j++)
			if (coord == m[i][j].get_coord())
			{
				if (m[i][j].get_color() == "white")
				{
					if ((m[i - 1][j - 1].get_color() == "black") & (m[i - 2][j - 2].get_color() == ""))
					{
						m_pos->push_back(m[i - 2][j - 2].get_coord());
						possible_turns_eat(m[i - 2][j - 2].get_coord(), m, m_pos);
					}
					if ((m[i - 1][j + 1].get_color() == "black") & (m[i - 2][j + 2].get_color() == ""))
					{
						m_pos->push_back(m[i - 2][j + 2].get_coord());
						possible_turns_eat(m[i - 2][j + 2].get_coord(), m, m_pos);
					}
					if ((m[i + 1][j - 1].get_color() == "black") & (m[i + 2][j - 2].get_color() == ""))
					{
						m_pos->push_back(m[i + 2][j - 2].get_coord());
						possible_turns_eat(m[i + 2][j - 2].get_coord(), m, m_pos);
					}
					if ((m[i + 1][j + 1].get_color() == "black") & (m[i + 2][j + 2].get_color() == ""))
					{
						m_pos->push_back(m[i + 2][j + 2].get_coord());
						possible_turns_eat(m[i + 2][j + 2].get_coord(), m, m_pos);
					}
				}
				else if (m[i][j].get_color() == "black")
				{
					if ((m[i - 1][j - 1].get_color() == "white") & (m[i - 2][j - 2].get_color() == ""))
					{
						m_pos->push_back(m[i - 2][j - 2].get_coord());
						possible_turns_eat(m[i - 2][j - 2].get_coord(), m, m_pos);
					}
					if ((m[i - 1][j + 1].get_color() == "white") & (m[i - 2][j + 2].get_color() == ""))
					{
						m_pos->push_back(m[i - 2][j + 2].get_coord());
						possible_turns_eat(m[i - 2][j + 2].get_coord(), m, m_pos);
					}
					if ((m[i + 1][j - 1].get_color() == "white") & (m[i + 2][j - 2].get_color() == ""))
					{
						m_pos->push_back(m[i + 2][j - 2].get_coord());
						possible_turns_eat(m[i + 2][j - 2].get_coord(), m, m_pos);
					}
					if ((m[i + 1][j + 1].get_color() == "white") & (m[i + 2][j + 2].get_color() == ""))
					{
						m_pos->push_back(m[i + 2][j + 2].get_coord());
						possible_turns_eat(m[i + 2][j + 2].get_coord(), m, m_pos);
					}
				}
			}
}




