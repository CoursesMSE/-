#ifndef MAIN_CONTROLS_H_
#define MAIN_CONTROLS_H_
	/*
	��������� ������� � ������, ������� ������������ �� ���� ������ 
	*/
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
