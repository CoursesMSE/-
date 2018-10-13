#include "pch.h"
#include "player_control.h"
#include "main_control.h"
#include "class.h"


void possible_turns(string coord, checker m[][SIZE], vector <string> *m_pos)
{
	for (int i = 0; i < SIZE; i++)
		for (int j = 0; j < SIZE; j++)
			if (coord == m[i][j].get_coord())
			{
				if (m[i][j].get_color() == "white")
				{
					if (exist(m[i][j].get_coord(), -1, -1))
						if (m[i - 1][j - 1].get_color() == "")
							m_pos->push_back(m[i - 1][j - 1].get_coord());
					if (exist(m[i][j].get_coord(), -1, 1))
						if (m[i - 1][j + 1].get_color() == "")
							m_pos->push_back(m[i - 1][j + 1].get_coord());

				}
				else if (m[i][j].get_color() == "black")
				{
					if (exist(m[i][j].get_coord(), 1, -1))
						if (m[i + 1][j - 1].get_color() == "")
							m_pos->push_back(m[i + 1][j - 1].get_coord());
					if (exist(m[i][j].get_coord(), 1, 1))
						if (m[i + 1][j + 1].get_color() == "")
							m_pos->push_back(m[i + 1][j + 1].get_coord());
				}
			}
}
void possible_turns_damka(string coord, checker m[][SIZE], vector <string> *m_pos, int vector)
{
	string new_coord = "";
	for (int i = 0; i < SIZE; i++)
		for (int j = 0; j < SIZE; j++)
			if (coord == m[i][j].get_coord())
				switch (vector)
				{
				case 1:
					if (exist(m[i][j].get_coord(), 1, 1))
						if (m[i + 1][j + 1].get_color() == "")
						{
							m_pos->push_back(m[i + 1][j + 1].get_coord());
							new_coord += char(coord[0] + 1);
							new_coord += char(coord[1] + 1);
							possible_turns_damka(new_coord, m, m_pos, 1);
						}
					break;
				case 2:
					if (exist(m[i][j].get_coord(), 1, -1))
						if (m[i + 1][j - 1].get_color() == "")
						{
							m_pos->push_back(m[i + 1][j - 1].get_coord());
							new_coord += char(coord[0] - 1);
							new_coord += char(coord[1] + 1);
							possible_turns_damka(new_coord, m, m_pos, 2);
						}
					break;
				case 3:
					if (exist(m[i][j].get_coord(), -1, -1))
						if (m[i - 1][j - 1].get_color() == "")
						{
							m_pos->push_back(m[i - 1][j - 1].get_coord());
							new_coord += char(coord[0] - 1);
							new_coord += char(coord[1] - 1);
							possible_turns_damka(new_coord, m, m_pos, 3);
						}
					break;
				case 4:
					if (exist(m[i][j].get_coord(), -1, 1))
						if (m[i - 1][j + 1].get_color() == "")
						{
							m_pos->push_back(m[i - 1][j + 1].get_coord());
							new_coord = char(coord[0] + 1);
							new_coord += char(coord[1] - 1);
							possible_turns_damka(new_coord, m, m_pos, 4);
						}
					break;
				case 0:
					new_coord = coord;
					possible_turns_damka(new_coord, m, m_pos, 1);
					possible_turns_damka(new_coord, m, m_pos, 2);
					possible_turns_damka(new_coord, m, m_pos, 3);
					possible_turns_damka(new_coord, m, m_pos, 4);
					break;
				}
}
void possible_turns_damka_eat(string coord, checker m[][SIZE], vector <string> *m_pos, string color, bool v1, bool v2, bool v3, bool v4)
{
	for (int i = 0; i < SIZE; i++)
		for (int j = 0; j < SIZE; j++)
			if (coord == m[i][j].get_coord())
			{
				if (color == "white")
				{
					for (int k = 0; k < SIZE; k++)
					{
							if (exist(m[i][j].get_coord(), -2 - k, -2 - k) && v1)
								if (m[i - 1 - k][j - 1 - k].get_color() == "black")
								{
									for (int n = k; n < SIZE; n++)
										if (exist(m[i][j].get_coord(), -2 - n, -2 - n))
											if (m[i - 2 - n][j - 2 - n].get_color() == "")
											{
												m_pos->push_back(m[i - 2 - n][j - 2 - n].get_coord());
												v4 = false;
												possible_turns_damka_eat(m[i - 2 - n][j - 2 - n].get_coord(), m, m_pos, color, v1, v2, v3, v4);
											}
											else
												break;
								}
							if (exist(m[i][j].get_coord(), -2 - k, 2 + k) && v2)
								if (m[i - 1 - k][j + 1 + k].get_color() == "black")
								{
									for (int n = k; n < SIZE; n++)
										if (exist(m[i][j].get_coord(), -2 - n, 2 + n))
											if (m[i - 2 - n][j + 2 + n].get_color() == "")
											{
												m_pos->push_back(m[i - 2 - n][j + 2 + n].get_coord());
												v3 = false;
												possible_turns_damka_eat(m[i - 2 - n][j + 2 + n].get_coord(), m, m_pos, color, v1, v2, v3, v4);
											}
											else
												break;
								}
							if (exist(m[i][j].get_coord(), 2 + k, -2 - k) && v3)
								if (m[i + 1 + k][j - 1 - k].get_color() == "black")
								{
									for (int n = k; n < SIZE; n++)
										if (exist(m[i][j].get_coord(), 2 + n, -2 - n))
											if (m[i + 2 + n][j - 2 - n].get_color() == "")
											{
												m_pos->push_back(m[i + 2 + n][j - 2 - n].get_coord());
												v2 = false;
												possible_turns_damka_eat(m[i + 2 + n][j - 2 - n].get_coord(), m, m_pos, color, v1, v2, v3, v4);
											}
											else
												break;
								}
							if (exist(m[i][j].get_coord(), 2 + k, 2 + k) && v4)
								if (m[i + 1 + k][j + 1 + k].get_color() == "black")
								{
									for (int n = k; n < SIZE; n++)
										if (exist(m[i][j].get_coord(), 2 + n, 2 + n))
											if (m[i + 2 + n][j + 2 + n].get_color() == "")
											{
												m_pos->push_back(m[i + 2 + n][j + 2 + n].get_coord());
												v1 = false;
												possible_turns_damka_eat(m[i + 2 + n][j + 2 + n].get_coord(), m, m_pos, color, v1, v2, v3, v4);
											}
											else
												break;
								}
					}
				}
				else if (color == "black")
				{
					for (int k = 0; k < SIZE; k++)
					{
						if (exist(m[i][j].get_coord(), -2 - k, -2 - k) && v1)
							if (m[i - 1 - k][j - 1 - k].get_color() == "white")
							{
								for (int n = k; n < SIZE; n++)
									if (exist(m[i][j].get_coord(), -2 - n, -2 - n))
										if (m[i - 2 - n][j - 2 - n].get_color() == "")
										{
											m_pos->push_back(m[i - 2 - n][j - 2 - n].get_coord());
											v4 = false;
											possible_turns_damka_eat(m[i - 2 - n][j - 2 - n].get_coord(), m, m_pos, color, v1, v2, v3, v4);
										}
										else
											break;
							}
						if (exist(m[i][j].get_coord(), -2 - k, 2 + k) && v2)
							if (m[i - 1 - k][j + 1 + k].get_color() == "white")
							{
								for (int n = k; n < SIZE; n++)
									if (exist(m[i][j].get_coord(), -2 - n, 2 + n))
										if (m[i - 2 - n][j + 2 + n].get_color() == "")
										{
											m_pos->push_back(m[i - 2 - n][j + 2 + n].get_coord());
											v3 = false;
											possible_turns_damka_eat(m[i - 2 - n][j + 2 + n].get_coord(), m, m_pos, color, v1, v2, v3, v4);
										}
										else
											break;
							}
						if (exist(m[i][j].get_coord(), 2 + k, -2 - k) && v3)
							if (m[i + 1 + k][j - 1 - k].get_color() == "white")
							{
								for (int n = k; n < SIZE; n++)
									if (exist(m[i][j].get_coord(), 2 + n, -2 - n))
										if (m[i + 2 + n][j - 2 - n].get_color() == "")
										{
											m_pos->push_back(m[i + 2 + n][j - 2 - n].get_coord());
											v2 = false;
											possible_turns_damka_eat(m[i + 2 + n][j - 2 - n].get_coord(), m, m_pos, color, v1, v2, v3, v4);
										}
										else
											break;
							}
						if (exist(m[i][j].get_coord(), 2 + k, 2 + k) && v4)
							if (m[i + 1 + k][j + 1 + k].get_color() == "white")
							{
								for (int n = k; n < SIZE; n++)
									if (exist(m[i][j].get_coord(), 2 + n, 2 + n))
										if (m[i + 2 + n][j + 2 + n].get_color() == "")
										{
											m_pos->push_back(m[i + 2 + n][j + 2 + n].get_coord());
											v1 = false;
											possible_turns_damka_eat(m[i + 2 + n][j + 2 + n].get_coord(), m, m_pos, color, v1, v2, v3, v4);
										}
										else
											break;
							}
					}
				}
			}
}
void possible_turns_eat(string coord, checker m[][SIZE], vector <string> *m_pos, string color, bool v1, bool v2, bool v3, bool v4)
{
	for (int i = 0; i < SIZE; i++)
		for (int j = 0; j < SIZE; j++)
			if (coord == m[i][j].get_coord())
		{			
				if (color == "white")
				{
					if (exist(m[i][j].get_coord(), -2, -2) && v1)
						if ((m[i - 1][j - 1].get_color() == "black") && (m[i - 2][j - 2].get_color() == ""))
						{
							m_pos->push_back(m[i - 2][j - 2].get_coord());
							v4 = false; v2 = v3 = v1 = true;
							possible_turns_eat(m[i - 2][j - 2].get_coord(), m, m_pos, color, v1, v2, v3, v4);
							//v4 = v3 = v2 = v1 = true;
						}
					if (exist(m[i][j].get_coord(), -2, 2) && v2)
						if ((m[i - 1][j + 1].get_color() == "black") && (m[i - 2][j + 2].get_color() == ""))
						{
							m_pos->push_back(m[i - 2][j + 2].get_coord());
							v3 = false; v1 = v2 = v4 = true;
							possible_turns_eat(m[i - 2][j + 2].get_coord(), m, m_pos, color, v1, v2, v3, v4);
							//v4 = v3 = v2 = v1 = true;
						}
					if (exist(m[i][j].get_coord(), 2, -2) && v3)
						if ((m[i + 1][j - 1].get_color() == "black") && (m[i + 2][j - 2].get_color() == ""))
						{
							m_pos->push_back(m[i + 2][j - 2].get_coord());
							v2 = false; v1 = v3 = v4 = true;
							possible_turns_eat(m[i + 2][j - 2].get_coord(), m, m_pos, color, v1, v2, v3, v4);
							//v4 = v3 = v2 = v1 = true;
						}
					if (exist(m[i][j].get_coord(), 2, 2) && v4)
						if ((m[i + 1][j + 1].get_color() == "black") && (m[i + 2][j + 2].get_color() == ""))
						{
							m_pos->push_back(m[i + 2][j + 2].get_coord());
							v1 = false; v2 = v3 = v4 = true;
							possible_turns_eat(m[i + 2][j + 2].get_coord(), m, m_pos, color, v1, v2, v3, v4);
							//v4 = v3 = v2 = v1 = true;
						}
				}
				else if (color == "black")
				{
					if (exist(m[i][j].get_coord(), -2, -2) && v1)
						if ((m[i - 1][j - 1].get_color() == "white") && (m[i - 2][j - 2].get_color() == ""))
						{
							m_pos->push_back(m[i - 2][j - 2].get_coord());
							v4 = false; v2 = v3 = v1 = true;
							possible_turns_eat(m[i - 2][j - 2].get_coord(), m, m_pos, color, v1, v2, v3, v4);
							//v4 = v3 = v2 = v1 = true;
						}
					if (exist(m[i][j].get_coord(), -2, 2) && v2)
						if ((m[i - 1][j + 1].get_color() == "white") && (m[i - 2][j + 2].get_color() == ""))
						{
							m_pos->push_back(m[i - 2][j + 2].get_coord());
							v3 = false; v1 = v2 = v4 = true;
							possible_turns_eat(m[i - 2][j + 2].get_coord(), m, m_pos, color, v1, v2, v3, v4);
							//v4 = v3 = v2 = v1 = true;
						}
					if (exist(m[i][j].get_coord(), 2, -2) && v3)
						if ((m[i + 1][j - 1].get_color() == "white") && (m[i + 2][j - 2].get_color() == ""))
						{
							m_pos->push_back(m[i + 2][j - 2].get_coord());
							v2 = false; v1 = v3 = v4 = true;
							possible_turns_eat(m[i + 2][j - 2].get_coord(), m, m_pos, color, v1, v2, v3, v4);
							//v4 = v3 = v2 = v1 = true;
						}
					if (exist(m[i][j].get_coord(), 2, 2) && v4)
						if ((m[i + 1][j + 1].get_color() == "white") && (m[i + 2][j + 2].get_color() == ""))
						{
							m_pos->push_back(m[i + 2][j + 2].get_coord());
							v1 = false; v2 = v3 = v4 = true;
							possible_turns_eat(m[i + 2][j + 2].get_coord(), m, m_pos, color, v1, v2, v3, v4);
							//v4 = v3 = v2 = v1 = true;
						}
				}
			}
}