#include "pch.h"
#include "class.h"

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