#ifndef MAIN_CONTROLS_H_
#define MAIN_CONTROLS_H_
	/*
	прототипы функций и данные, которые используются во всех файлах 
	*/
#include "pch.h"
#include "class.h"

void move_checker(string new_c, string old_c, checker m[][SIZE]);
void preobras(checker m[][SIZE], string s, bool & not_possible);
void draw_field(checker m[][SIZE], vector <string> *m_pos);
void initialization(checker m[][SIZE]);
bool exist(string, int, int);
bool game_over(checker m[][SIZE]);
void proverka(vector <string> *m_pos, string coord, bool & error);
string opr_color(string coord, checker m[][SIZE]);
bool possible(string coord, vector <string> *m_pos);
void poisk(checker m[][SIZE], string coord, int & a, int & b);

#endif // !MAIN_CONTROLS_H
