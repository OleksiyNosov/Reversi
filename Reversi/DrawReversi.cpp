#include "stdafx.h"
#include "DrawReversi.h"
using std::cout;
using std::list;

DrawReversi::DrawReversi()
{
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	this->dCoord.X = 2;
	this->dCoord.Y = 2;
	this->cci = { 50, 0 };
	SetConsoleCursorInfo(hOut, &cci);
	this->colorAtribute = defColorAtribute;
	SetConsoleTextAttribute(hOut, colorAtribute);
}


DrawReversi::~DrawReversi()
{
}

void DrawReversi::DrawBoardHead(Board* board)
{
	this->coord = board->defBPos;
	SetConsoleCursorPosition(hOut, this->coord);
	cout << "  A  B  C  D  E  F  G  H";
	++this->coord.Y;
	SetConsoleCursorPosition(hOut, this->coord);
	cout << " " << (char)201;
	for (int i = 0; i < BOARD_LENGTH - 1; ++i)
		cout << (char)205 << (char)205 << (char)209;
	cout 
		<< (char)205 << (char)205 << (char)187;
}
void DrawReversi::DrawBoardBodyPart(int numb)
{
	++this->coord.Y;
	SetConsoleCursorPosition(hOut, this->coord);
	cout << numb << (char)186;
	for (int i = 0; i < BOARD_LENGTH - 1; ++i)
		cout << "  " << (char)179;
	cout << "  " << (char)186;

	++this->coord.Y;
	SetConsoleCursorPosition(hOut, this->coord);
	cout << " " << (char)199;
	for (int i = 0; i < BOARD_LENGTH - 1; ++i)
		cout 
		<< (char)196 << (char)196 << (char)197;
	cout 
		<< (char)196 << (char)196 << (char)182;
}
void DrawReversi::DrawBoardBody()
{
	for (int i = 0; i < BOARD_LENGTH - 1; ++i)
	{
		this->DrawBoardBodyPart(i + 1);
	}
}
void DrawReversi::DrawBoardFooter()
{
	++this->coord.Y;
	SetConsoleCursorPosition(hOut, this->coord);
	cout << "8" << (char)186;
	for (int i = 0; i < BOARD_LENGTH - 1; ++i)
		cout 
		<< "  " << (char)179;
	cout 
		<< "  " << (char)186;

	++this->coord.Y;
	SetConsoleCursorPosition(hOut, this->coord);

	cout << " " << (char)200;
	for (int i = 0; i < BOARD_LENGTH - 1; ++i)
		cout 
		<< (char)205 << (char)205 << (char)207;
	cout 
		<< (char)205 << (char)205 << (char)188;
}
void DrawReversi::DrawBoard(Board* board)
{
	this->colorAtribute = ccWhite + (ccBlack * 0x10);
	SetConsoleTextAttribute(this->hOut, this->colorAtribute);
	system("cls");

	SetConsoleTextAttribute(this->hOut, this->defColorAtribute);
	
	this->DrawBoardHead(board);
	this->DrawBoardBody();
	this->DrawBoardFooter();
}

void DrawReversi::DrawString(string text, COORD coord)
{
	coord.X -= text.length() / 2 + 1;
	SetConsoleCursorPosition(hOut, coord);
	cout << text;
}
void DrawReversi::DrawArrows(Menu* menu)
{
	coord.Y = menu->defMTextPos.Y + (menu->curMenuStr * 2);
	coord.X = menu->defMTextPos.X - menu->mText[menu->curMenuStr].length() / 2 - 5;
	SetConsoleCursorPosition(hOut, coord);
	cout << ">>>";
	coord.X += menu->mText[menu->curMenuStr].length() + 5;
	SetConsoleCursorPosition(hOut, coord);
	cout << "<<<";
}
void DrawReversi::PaintOverArrows(Menu* menu)
{
	coord.Y = menu->defMTextPos.Y + (menu->curMenuStr * 2);
	coord.X = menu->defMTextPos.X - menu->mText[menu->curMenuStr].length() / 2 - 5;
	SetConsoleCursorPosition(hOut, coord);
	cout << "   ";
	coord.X += menu->mText[menu->curMenuStr].length() + 5;
	SetConsoleCursorPosition(hOut, coord);
	cout << "   ";
}
void DrawReversi::DrawMenu(Menu* menu)
{
	SetConsoleTextAttribute(hOut, this->defColorAtribute);
	system("cls");
	
	this->coord = menu->defMTextPos;
	for (int i = 0; i < menu->mText.size(); i++)
	{
		this->DrawString(menu->mText.at(i), this->coord);
		this->coord.Y += 2;
	}
}

void DrawReversi::DrawScore(Board* board)
{
	colorAtribute = ccWhite + (ccBlack * 0x10);
	SetConsoleTextAttribute(hOut, colorAtribute);
	SetConsoleCursorPosition(hOut, COORD{ 30,2});
	cout << "Score:";
	SetConsoleCursorPosition(hOut, COORD{ 30, 3 });
	cout << "                  ";
	SetConsoleCursorPosition(hOut, COORD{ 30, 3 });
	cout << "Red  pieces - " << board->GetWhitePieces();
	SetConsoleCursorPosition(hOut, COORD{ 30, 4 });
	cout << "                  ";
	SetConsoleCursorPosition(hOut, COORD{ 30, 4 });
	cout << "Blue pieces - " << board->GetBlackPieces();
}

void DrawReversi::DrawDisk(Disk* disk)
{
	this->coord.X = (disk->coord.X + 1) * 3;
	this->coord.Y = (disk->coord.Y + 1) * 2;
	this->coord.X -= 1;
	SetConsoleCursorPosition(hOut, this->coord);

	colorAtribute = disk->ConsoleColor;
	SetConsoleTextAttribute(hOut, colorAtribute);

	cout << (char)219 << (char)219;
}
void DrawReversi::DrawDisks(Board* board)
{
	for (int i = 0; i < BOARD_LENGTH; ++i)
	{
		for (int j = 0; j < BOARD_LENGTH; ++j)
		{
			this->DrawDisk(&board->pBoard[i][j]);
		}
	}
}

void DrawReversi::DrawPossibleDisk(COORD coord, char symb)
{
	this->coord.X = (coord.X + 1) * 3;
	this->coord.Y = (coord.Y + 1) * 2;
	
	SetConsoleCursorPosition(hOut, this->coord);
	cout << symb;
}
void DrawReversi::DrawPossiblePos(Board* board, int curPlayerColor)
{
	switch (curPlayerColor)
	{
	case WHITE:
		colorAtribute = ccRed + (ccBlack * 0x10);
		break;
	case BLACK:
		colorAtribute = ccBlue + (ccBlack * 0x10);
		break;
	}
	SetConsoleTextAttribute(hOut, colorAtribute);

	for (int i = 0; i < BOARD_LENGTH; i++)
	{
		for (int j = 0; j < BOARD_LENGTH; j++)
		{
			list<LineOfDisks> * possibleMoves = &board->pPossibleMoves[i][j];
			list<LineOfDisks>::iterator it;
			for (it = possibleMoves->begin(); it != possibleMoves->end(); it++)
			{
				this->DrawPossibleDisk(it->st, (char)177);
			}
		}
	}
}
void DrawReversi::PaintOverPossiblePos(Board* board)
{
	for (int i = 0; i < BOARD_LENGTH; i++)
	{
		for (int j = 0; j < BOARD_LENGTH; j++)
		{
			list<LineOfDisks> * possibleMoves = &board->pPossibleMoves[i][j];
			list<LineOfDisks>::iterator it;
			for (it = possibleMoves->begin(); it != possibleMoves->end(); it++)
			{
				this->DrawPossibleDisk(it->st, ' ');
			}
		}
	}
}

void DrawReversi::DrawAMove(Board* board, int x, int y, int curPlayerColor)
{
	this->DrawDisk(&board->pBoard[y][x]);
	int i, j;
	list<LineOfDisks>::iterator it;
	for (it = board->pPossibleMoves[y][x].begin(); it != board->pPossibleMoves[y][x].end(); it++)
	{
		i = it->st.Y;
		j = it->st.X;
		while (i != it->en.Y || j != it->en.X)
		{
			this->DrawDisk(&board->pBoard[i -= it->V][j -= it->H]);
		}
	}
}
void DrawReversi::DrawAMove(Board* board, COORD coord, int curPlayerColor)
{
	this->DrawAMove(board, coord.X, coord.Y, curPlayerColor);
}
void DrawReversi::DrawAMove(list<LineOfDisks> possMoves, Board* board, int x, int y, int curPlayerColor)
{
	this->DrawDisk(&board->pBoard[y][x]);
	int i, j;
	list<LineOfDisks>::iterator it;
	for (it = possMoves.begin(); it != possMoves.end(); it++)
	{
		i = it->st.Y;
		j = it->st.X;
		while (i != it->en.Y || j != it->en.X)
		{
			this->DrawDisk(&board->pBoard[i -= it->V][j -= it->H]);
		}
	}
}
void DrawReversi::DrawAMove(list<LineOfDisks> possMoves, Board* board, COORD coord, int curPlayerColor)
{
	this->DrawAMove(possMoves, board, coord.X, coord.Y, curPlayerColor);
}
void DrawReversi::DrawAMoveBack(list<LineOfDisks> possMoves, Board* board, int x, int y, int curPlayerColor)
{
	int i, j;
	list<LineOfDisks>::iterator it;
	for (it = possMoves.begin(); it != possMoves.end(); it++)
	{
		i = it->st.Y;
		j = it->st.X;
		while (i != it->en.Y || j != it->en.X)
		{
			this->DrawDisk(&board->pBoard[i][j]);
			i -= it->V;
			j -= it->H;
		}
	}
	this->DrawDisk(&board->pBoard[y][x]);
}
void DrawReversi::DrawAMoveBack(list<LineOfDisks> possMoves, Board* board, COORD coord, int curPlayerColor)
{
	this->DrawAMoveBack(possMoves, board, coord.X, coord.Y, curPlayerColor);
}

void DrawReversi::DrawCursor(COORD coord)
{
	this->coord.X = (coord.X + 1) * 3;
	this->coord.Y = (coord.Y + 1) * 2;
	colorAtribute = ccWhite + (ccBlack * 0x10);
	SetConsoleTextAttribute(hOut, colorAtribute);
	this->coord.X -= 1;
	SetConsoleCursorPosition(hOut, this->coord);
	cout << '>';
}
void DrawReversi::PaintOverCursor(COORD coord)
{
	this->coord.X = (coord.X + 1) * 3;
	this->coord.Y = (coord.Y + 1) * 2;
	colorAtribute = ccDarkCyan + (ccBlack * 0x10);
	SetConsoleTextAttribute(hOut, colorAtribute);
	this->coord.X -= 1;
	SetConsoleCursorPosition(hOut, this->coord);
	cout << ' ';
}

void DrawReversi::GameOver(int playerColor)
{
	this->coord = { 30, 10 };
	colorAtribute = ccWhite + (ccBlack * 0x10);
	SetConsoleTextAttribute(hOut, colorAtribute);
	SetConsoleCursorPosition(hOut, this->coord);
	switch (playerColor)
	{
	case 0:
		cout << "Drawn game.";
		break;
	case WHITE:
		cout << "Red player win !!!";
		break;
	case BLACK:
		cout << "Blue player win !!!";
		break;
	}
	_getch();

	this->coord = { 30, 10 };
	colorAtribute = ccWhite + (ccBlack * 0x10);
	SetConsoleTextAttribute(hOut, colorAtribute);
	SetConsoleCursorPosition(hOut, this->coord);
	cout << "                             ";
}


