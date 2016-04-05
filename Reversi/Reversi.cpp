// Reversi.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Board.h"
#include "DrawReversi.h"
#include "Ñontroller.h"
#include "Menu.h"


void TestGame();

int _tmain(int argc, _TCHAR* argv[])
{
	// Run the game
	TestGame();
	return 0;
}

void TestGame()
{
	Ñontroller controller;
	controller.InitMainMenu();
}

