#ifndef PLAYER_CONTROL_H_
#define PLAYER_CONTROL_H_

#include "pch.h"
#include "class.h"

void possible_turns(string coord, checker m[][SIZE], vector <string> *m_pos);
void possible_turns_eat(string coord, checker m[][SIZE], vector <string> *m_pos, string color);
void possible_turns_damka(string coord, checker m[][SIZE], vector <string> *m_pos, int vector = 0);
void possible_turns_damka_eat(string coord, checker m[][SIZE], vector <string> *m_pos, string color);

#endif // !

