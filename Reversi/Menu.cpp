#include "stdafx.h"
#include "Menu.h"


Menu::Menu()
{
	this->defMTextPos = { 40, 3 };
	this->curMenuStr = 0;
}


Menu::~Menu()
{
}

void Menu::AddMenuText(string text)
{
	this->mText.emplace_back(text);
}
