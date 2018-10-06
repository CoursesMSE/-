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
	string coord; // ��������� �� ����
	string color; // ���� �����
	bool damka; // �������� �� ����� ������
public:
	string get_coord(); // �������� �������� ���������
	bool get_damka(); //�������� �����, ��� �� ����� ������
	string get_color(); // �������� ���� �����
	void set_coord(string s);
	void set_color(string s); // ������������� ���� ����� � �������� s
	void set_damka(bool s); // ������������� �������� ����� � ����� � �������� s
	void delete_checker();
};

const int SIZE = 8;

#endif 
