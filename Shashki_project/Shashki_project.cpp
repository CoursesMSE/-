#include "pch.h"
#include <iostream>
#include <string>
#include <string.h>

using namespace std;

const int SIZE = 8;

class checker
{
	string coord;
	string color;
	bool damka;
public:
	string get_coord();
	string get_color();
	bool get_damka();
};

void initialization(checker m[][SIZE]);
void draw_field(checker m[][SIZE]);

int main()
{
	checker massiv_iacheek[SIZE][SIZE];
	initialization(massiv_iacheek);
	draw_field(massiv_iacheek);
	cin.get();
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
void initialization(checker m[][SIZE])
{
	for (int i = 0; i < SIZE; i++)
		for (int j = 0; j < SIZE; j++)
		{
			m[i][j].get_coord() = "0";
			m[i][j].get_color() = "";

			if (i >= 0 && i <= 2 && (i + j) % 2 == 0)
			{
				m[i][j].get_coord() += char(j + 65);
				m[i][j].get_coord() += char(i + 49);
				m[i][j].get_color() = "black";
			}
			if (i >= 5 && i < SIZE && (i + j) % 2 == 0)
			{
				m[i][j].get_coord() += char(j + 65);
				m[i][j].get_coord() += char(i + 49);
				m[i][j].get_color() = "white";
			}
			//cout << m[i][j].get_coord() << endl;
		}
}
void draw_field(checker m[][SIZE])
{
	for (int i = -1; i < SIZE; i++)
	{
		for (int k = 0; k <= (SIZE + 1) * 2; k++)
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
			else if (m[i][j].get_coord() != "")
			{
				if (m[i][j].get_color() == "white")
					cout << 'Б';
				else if (m[i][j].get_color() == "black")
					cout << 'Ч';
			}
			else
				cout << ' ';
		}
		cout << '|' << endl;
	}
	for (int k = 0; k <= (SIZE + 1) * 2; k++)
		cout << '-';
	cout << endl;
};