// Описание всех функций в файле main_control.h
#include "main_control.h"
#include "pch.h"

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
void move_checker(string new_c, string old_c, checker m[][SIZE])
{
	string color; int i_new, j_new;
	for (int i = 0; i < SIZE; i++)
		for (int j = 0; j < SIZE; j++)
			if (m[i][j].get_coord() == new_c)
			{
				i_new = i;
				j_new = j;
			}
	for (int i = 0; i < SIZE; i++)
		for (int j = 0; j < SIZE; j++)
			if (m[i][j].get_coord() == old_c)
			{
				color = m[i][j].get_color();
				if (i + 2 == i_new && j + 2 == j_new)
					m[i + 1][j + 1].delete_checker();
				else if (i + 2 == i_new && j - 2 == j_new)
					m[i + 1][j - 1].delete_checker();
				else if (i - 2 == i_new && j - 2 == j_new)
					m[i - 1][j - 1].delete_checker();
				else if (i - 2 == i_new && j + 2 == j_new)
					m[i - 1][j + 1].delete_checker();
				m[i][j].set_color("");
				
			}
	for (int i = 0; i < SIZE; i++)
		for (int j = 0; j < SIZE; j++)
			if (m[i][j].get_coord() == new_c)
			{
				m[i][j].set_color(color);
				for (int i1 = 0; i1 < SIZE; i1++)
					for (int j1 = 0; j1 < SIZE; j1++)
						if (m[i1][j1].get_coord() == old_c)
							if (m[i1][j1].get_damka())
							{
								m[i1][j1].set_damka(false);
								m[i][j].set_damka(true);
							}
				if ((new_c[1] == '1' && color == "white") || (new_c[1] == '8' && color == "black"))
					m[i][j].set_damka(true);
			}
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
void checker::delete_checker()
{
	color = "";
}
bool possible(string coord, vector <string> *m_pos)
{
	for (int i = 0; i < m_pos->size(); i++)
		if (coord == (*m_pos)[i])
			return true;
	return false;
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
			m[i][j].set_damka(true);
			if (i >= 0 && i <= 2 && (i + j) % 2 == 1)
				m[i][j].set_color("black");
			if (i >= 5 && i < SIZE && (i + j) % 2 == 1)
				m[i][j].set_color("white");
			str = "";
		}
}
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
bool exist(string coord, int k_i, int k_j)
{
	char bukva = coord[0], cifra = coord[1];
	if ((char(cifra + k_i) >= '1' && char(cifra + k_i) <= '8') && (char(bukva + k_j) >= 'A' && char(bukva + k_j) <= 'H'))
		return true;
	return false;
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