#pragma once
#include "Disk.h"
#include "Board.h"
#include "Menu.h"
using std::list;
using std::string;

class DrawReversi
{
	friend class Ñontroller;

	HANDLE hOut;
	CONSOLE_CURSOR_INFO cci;
	COORD coord;
	COORD dCoord;
	WORD colorAtribute;
	const WORD defColorAtribute = ccWhite + (ccBlack * 0x10);

	void DrawBoardHead(Board* board);
	void DrawBoardBodyPart(int numb);
	void DrawBoardBody();
	void DrawBoardFooter();

public:
	DrawReversi();
	~DrawReversi();

	void DrawString(string text, COORD coord);
	void DrawArrows(Menu* menu);
	void PaintOverArrows(Menu* menu);
	void DrawMenu(Menu* menu);

	void DrawScore(Board* board);

	void DrawDisk(Disk* disk);
	void DrawDisks(Board* board);
	void DrawBoard(Board* board);

	void DrawPossibleDisk(COORD coord, char symb);
	void DrawPossiblePos(Board* board, int curPlayerColor);
	void PaintOverPossiblePos(Board* board);

	void DrawAMove(Board* board, int x, int y, int curPlayerColor);
	void DrawAMove(Board* board, COORD coord, int curPlayerColor);
	void DrawAMove(list<LineOfDisks> possMoves, Board* board, int x, int y, int curPlayerColor);
	void DrawAMove(list<LineOfDisks> possMoves, Board* board, COORD coord, int curPlayerColor);
	void DrawAMoveBack(list<LineOfDisks> possMoves, Board* board, int x, int y, int curPlayerColor);
	void DrawAMoveBack(list<LineOfDisks> possMoves, Board* board, COORD coord, int curPlayerColor);

	void DrawCursor(COORD coord);
	void PaintOverCursor(COORD coord);

	void GameOver(int playerColor);
};

