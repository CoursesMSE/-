#include "pch.h"
#include <iostream>
#include <string>
#include <string.h>
#include <vector>
#include "bot_control.h"
#include "main_control.h"
#include "player_control.h"

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
void preobras(checker m[][SIZE] ,string s, bool & not_possible);
void possible_turns(string coord, checker m[][SIZE], vector <string> *m_pos);
void possible_turns_eat(string coord, checker m[][SIZE], vector <string> *m_pos);
bool possible(string coord, vector <string> *m_pos);
void proverka(vector <string> *m_pos, string coord, bool &error);
string opr_color(string coord, checker m[][SIZE]);

int main()
{
	setlocale(0, "Russian");
	cout << "Добро пожаловать в игру шашки." << endl;
	checker massiv_iacheek[SIZE][SIZE];
	initialization(massiv_iacheek);
	vector <string> vector_pos(20);
	vector_pos.clear();
	draw_field(massiv_iacheek, &vector_pos);
	string coord_choice = "", coord_new = "";
	bool black_turn = false, white_turn = true;
	bool error;
	while (!game_over(massiv_iacheek))
	{
		error = true;
		if (black_turn)
		{
			cout << "Ход переходит к чёрным." << endl;
			while (error)
			{
				getline(cin, coord_choice);
				preobras(massiv_iacheek, coord_choice, error);
				if ((error) || opr_color(coord_choice, massiv_iacheek) == "white")
				{
					cout << "Введите другие кординаты!" << endl;
					error = true;
					continue;
				};
				possible_turns(coord_choice, massiv_iacheek, &vector_pos);
				//possible_turns_eat(coord_choice, massiv_iacheek, &vector_pos); //это не работает
				if (vector_pos.empty())
				{
					cout << "Введите другие кординаты!" << endl;
					error = true;
				};
			};
			error = true;
			while (error)
			{
				getline(cin, coord_new);
				preobras(massiv_iacheek, coord_choice, error);
				if (error)
				{
					cout << "Введите другие кординаты!" << endl;
					error = true;
					continue;
				};
				proverka(&vector_pos, coord_new, error);
				if (error)
					cout << "Вы не можете так сходить. Введите другие кординаты!" << endl;
				else
					for (int i = 0; i < SIZE; i++)
						for (int j = 0; j < SIZE; j++)
							if (massiv_iacheek[i][j].get_coord() == coord_choice)
								massiv_iacheek[i][j].move_checker(coord_new, coord_choice, massiv_iacheek);
			};
			vector_pos.clear();
			draw_field(massiv_iacheek, &vector_pos);
			white_turn = true; black_turn = false;
			
		}
		else if (white_turn)
		{
			cout << "Ход переходит к белым." << endl;
			while (error)
			{
				getline(cin, coord_choice);
				preobras(massiv_iacheek, coord_choice, error);
				if ((error) || opr_color(coord_choice, massiv_iacheek) == "black")
				{
					cout << "Введите другие кординаты!" << endl;
					error = true;
					continue;
				};
				possible_turns(coord_choice, massiv_iacheek, &vector_pos);
				//possible_turns_eat(coord_choice, massiv_iacheek, &vector_pos); //это не работает
				if (vector_pos.empty())
				{
					cout << "Введите другие кординаты!" << endl;
					error = true;
				};
			};
			error = true;
			while (error)
			{
				getline(cin, coord_new);
				preobras(massiv_iacheek, coord_choice, error);
				if (error)
				{
					cout << "Введите другие кординаты!" << endl;
					error = true;
					continue;
				};
				proverka(&vector_pos, coord_new, error);
				if (error)
					cout << "Вы не можете так сходить. Введите другие кординаты!" << endl;
				else
					for (int i = 0; i < SIZE; i++)
						for (int j = 0; j < SIZE; j++)
							if (massiv_iacheek[i][j].get_coord() == coord_choice)
								massiv_iacheek[i][j].move_checker(coord_new, coord_choice, massiv_iacheek);
			};
			vector_pos.clear();
			draw_field(massiv_iacheek, &vector_pos);
			black_turn = true; white_turn = false;
		}
		
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
				else if (possible(m[i][j].get_coord(), m_pos))
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
void preobras(checker m[][SIZE], string s, bool & not_possible)
{
	char c = '4', n = '4', tmp;
	not_possible = true;
	char k;
	if (s.size() == 2)//Сделал так ,чтобы приводилось к надлежащему виду, как в примере, но так как не понял для чего str_res, checker, и 3 пример про пустую клетку, поэтому их не трогал. 
	{//Если переместить этот код в другую прогу в int main, то всё работает(проверил в codeblocks). Если надо что-то объяснить ,то скажите, а так здесь работа с ascii. 
		for (int i = 49; i < 57; i++) {
			k = i;
			if (s[0] == k)
				c = '0';
			if (s[1] == k)
				n = '0';
		}
		for (int i = 65; i < 73; i++) {
			k = i;
			if (s[0] == k)
				c = '1';
			if (s[1] == k)
				n = '1';
		}
		for (int i = 97; i < 105; i++) {
			k = i;
			if (s[0] == k)
				c = '2';
			if (s[1] == k)
				n = '2';
		}
		if (c == '1' && n == '0')
			not_possible = false;
		if (c == '0' && n == '1') {
			not_possible = false;
			tmp = s[0];
			s[0] = s[1];
			s[1] = tmp;
		}
		if (c == '2' && n == '0') {
			s[0] = s[0] - 32;
			not_possible = false;
		}
		if (c == '0' && n == '2') {
			tmp = s[0];
			s[0] = s[1];
			s[1] = tmp;
			s[0] = s[0] - 32;
			not_possible = false;
		}
	}
}
void possible_turns(string coord, checker m[][SIZE], vector <string> *m_pos)
{
	for (int i = 0; i < SIZE; i++)
		for (int j = 0; j < SIZE; j++)
			if (coord == m[i][j].get_coord())
			{
				if (m[i][j].get_color() == "white")
				{
					if (m[i - 1][j - 1].get_color() == "")
						m_pos->push_back(m[i - 1][j - 1].get_coord());
					if (m[i - 1][j + 1].get_color() == "")
						m_pos->push_back(m[i - 1][j + 1].get_coord());
					
				}
				else if (m[i][j].get_color() == "black")
				{
					if (m[i + 1][j - 1].get_color() == "")
						m_pos->push_back(m[i + 1][j - 1].get_coord());
					if (m[i + 1][j + 1].get_color() == "")
						m_pos->push_back(m[i + 1][j + 1].get_coord());
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
void proverka(vector <string> *m_pos, string coord, bool &error)
{
	error = true;
	for (int i = 0; i < m_pos->size(); i++)
		if ((*m_pos)[i] == coord)
			error = false;
}
string opr_color(string coord, checker m[][SIZE])
{
	for (int i = 0; i < SIZE; i++)
		for (int j = 0; j < SIZE; j++)
			if (m[i][j].get_coord() == coord)
				return m[i][j].get_color();
	return "";
}
bool possible(string coord, vector <string> *m_pos)
{
	for (int i = 0; i < m_pos->size(); i++)
		if (coord == (*m_pos)[i])
			return true;
	return false;
}

