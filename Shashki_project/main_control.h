#ifndef MAIN_CONTROLS_H_
#define MAIN_CONTROLS_H_
	/*
	прототипы функций и данные, которые используются во всех файлах 
	*/
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
void move_checker(string new_c, string old_c, checker m[][SIZE]);
void preobras(checker m[][SIZE], string s, bool & not_possible);
void draw_field(checker m[][SIZE], vector <string> *m_pos);
void initialization(checker m[][SIZE]);
bool exist(string, int, int);
bool game_over(checker m[][SIZE]);
void proverka(vector <string> *m_pos, string coord, bool &error);
string opr_color(string coord, checker m[][SIZE]);
bool possible(string coord, vector <string> *m_pos);

#endif // !MAIN_CONTROLS_H
