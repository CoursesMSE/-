// �������� ���� ������� � ����� main_control.h
#include "pch.h"
#include "main_control.h"
#include "class.h"


void proverka(vector <string> *m_pos, string coord, bool & error)
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
void move_checker(string new_c, string old_c, checker m[][SIZE], vector <string> *player_turn, int k)
{
	string color; int i_new, j_new;
	for (int i = 0; i < SIZE; i++)
		for (int j = 0; j < SIZE; j++)
			if (m[i][j].get_coord() == new_c)
			{
				i_new = i;
				j_new = j;
			}
	int v = 0, n_main = 0;
	for (int i = 0; i < SIZE; i++)
		for (int j = 0; j < SIZE; j++)
			if (m[i][j].get_coord() == old_c)
				{
					color = m[i][j].get_color();
					for (int n = 1; n < SIZE; n++)
					{
						n_main = n;
						if (i + n == i_new && j + n == j_new)
						{
							v = 1;
							break;
						}
						if (i - n == i_new && j + n == j_new)
						{
							v = 2;
							break;
						}
						if (i + n == i_new && j - n == j_new)
						{
							v = 3;
							break;
						}
						if (i - n == i_new && j - n == j_new)
						{
							v = 4;
							break;
						}
					}
					switch (v)
					{
					case 1:
						for (int n = 1; n < n_main; n++)
							m[i + n][j + n].delete_checker();
						break;
					case 2:
						for (int n = 1; n < n_main; n++)
							m[i - n][j + n].delete_checker();
						break;
					case 3:
						for (int n = 1; n < n_main; n++)
							m[i + n][j - n].delete_checker();
						break;
					case 4:
						for (int n = 1; n < n_main; n++)
							m[i - n][j - n].delete_checker();
						break;
					}
					m[i][j].set_color("");
			};
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
	if (k != 1)
	{
		player_turn->erase(player_turn->begin());
		player_turn->pop_back();
	}
	if (player_turn->capacity() - k + 1 != 1) 
		move_checker((*player_turn)[1], (*player_turn)[0], m, player_turn, ++k);
}
void preobras(checker m[][SIZE], string s, bool & not_possible)
{
	char c = '4', n = '4', tmp;
	not_possible = true;
	char k;
	if (s.size() == 2)//������ ��� ,����� ����������� � ����������� ����, ��� � �������, �� ��� ��� �� ����� ��� ���� str_res, checker, � 3 ������ ��� ������ ������, ������� �� �� ������. 
	{//���� ����������� ���� ��� � ������ ����� � int main, �� �� ��������(�������� � codeblocks). ���� ���� ���-�� ��������� ,�� �������, � ��� ����� ������ � ascii. 
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
					cout << '�';
				else if (m[i][j].get_color() == "black")
					cout << '�';
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
void poisk(checker m[][SIZE], string coord, int & a, int & b)
{
	for (int i = 0; i < SIZE; i++)
		for (int j = 0; j < SIZE; j++)
			if (m[i][j].get_coord() == coord)
			{
				a = i; b = j;
			}
}