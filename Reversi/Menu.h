#pragma once
using std::string;
using std::vector;
class Menu
{
	friend class �ontroller;
	friend class DrawReversi;
	vector<string> mText;
	
	int curMenuStr;

	COORD defMTextPos;

public:
	Menu();
	~Menu();

	void AddMenuText(string text);

};

