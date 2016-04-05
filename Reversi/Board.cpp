#include "stdafx.h"
#include "Board.h"
using std::cout;


Board::Board()
{
	this->CreateBoard();
	this->CreateBoardOfPossibleMoves();
	this->SetStartDisks();
	this->SetDisksCoords();
	this->whitePieces = 2;
	this->blackPieces = 2;
	this->turn = 0;
	this->defBPos.X = 0;
	this->defBPos.Y = 0;
	this->gameStarted = false;
}
Board::~Board()
{
	this->DeleteBoard();
	this->DeleteBoardOfPossibleMoves();
}

/*----------------------------- Creating and deleting board(matrix of Disks) --------------------------------*/
void Board::CreateBoard()
{
	this->pBoard = new Disk*[BOARD_LENGTH];
	for (int i = 0; i < BOARD_LENGTH; ++i)
	{
		this->pBoard[i] = new Disk[BOARD_LENGTH];
	}
}
void Board::DeleteBoard()
{
	for (int i = 0; i < BOARD_LENGTH; ++i)
	{
		delete[]this->pBoard[i];
	}
	delete[]this->pBoard;
}

/*----------------------------- Creating and deleting board(matrix of lists with possible moves) ------------*/
void Board::CreateBoardOfPossibleMoves()
{
	this->pPossibleMoves = new list<LineOfDisks>*[BOARD_LENGTH];
	for (int i = 0; i < BOARD_LENGTH; ++i)
	{
		this->pPossibleMoves[i] = new list<LineOfDisks>[BOARD_LENGTH];
	}
}
void Board::DeleteBoardOfPossibleMoves()
{
	for (int i = 0; i < BOARD_LENGTH; ++i)
	{
		delete[]this->pPossibleMoves[i];
	}
	delete[]this->pPossibleMoves;
}

/*----------------------------- Counting possible moves -----------------------------------------------------*/
void Board::CountPossibleMove(Disk* disk, int X, int Y, int playerColor)
{
	this->dline.en = disk->GetCoord();	
	this->dline.H = X;
	this->dline.V = Y;

	this->dline.en.X -= X;
	this->dline.en.Y -= Y;
	if (!this->IsCoordOnBoard(this->dline.en))
	{
		return;
	}

	if (pBoard[dline.en.Y][dline.en.X] == playerColor)
	{
		this->dline.st = disk->GetCoord();
		while (true)
		{
			this->dline.st.X += X;
			this->dline.st.Y += Y;
			if (!this->IsCoordOnBoard(this->dline.st))
			{
				return;
			}
			else if (pBoard[dline.st.Y][dline.st.X] == EMPTY)
			{
				this->pPossibleMoves[this->dline.st.Y][this->dline.st.X].emplace_back(this->dline);
				this->dline.clear();
				return;
			}
			else if (pBoard[dline.st.Y][dline.st.X] == *disk)
			{
				continue;
			}
			else
			{
				return;
			}
		}
	}
}
void Board::CountPossibleMovesForDisk(Disk* disk, int playerColor)
{
	// Count possible moves for all directions
	this->CountPossibleMove(disk, RIGHT, UP, playerColor);
	this->CountPossibleMove(disk, RIGHT, CENTER, playerColor);
	this->CountPossibleMove(disk, RIGHT, DOWN, playerColor);
	this->CountPossibleMove(disk, CENTER, UP, playerColor);
	this->CountPossibleMove(disk, CENTER, DOWN, playerColor);
	this->CountPossibleMove(disk, LEFT, UP, playerColor);
	this->CountPossibleMove(disk, LEFT, CENTER, playerColor);
	this->CountPossibleMove(disk, LEFT, DOWN, playerColor);
}
void Board::CountPossibleMoves(int playerColor)
{
	for (int i = 0; i < BOARD_LENGTH; i++)
	{
		for (int j = 0; j < BOARD_LENGTH; j++)
		{
			if (pBoard[i][j] == playerColor * -1)
				this->CountPossibleMovesForDisk(&pBoard[i][j], playerColor);
		}
	}
}

void Board::ClearPPossibleMoves()
{
	for (int i = 0; i < BOARD_LENGTH; i++)
	{
		for (int j = 0; j < BOARD_LENGTH; j++)
		{
			this->pPossibleMoves[i][j].clear();
		}
	}
}

/*----------------------------- Making move on board forward and back ---------------------------------------*/
void Board::MakeAMove(int x, int y, int curPlayerColor)
{
	this->pBoard[y][x] = curPlayerColor;
	int i, j;
	list<LineOfDisks>::iterator it;
	for (it = this->pPossibleMoves[y][x].begin(); it != this->pPossibleMoves[y][x].end(); it++)
	{
		i = it->st.Y;
		j = it->st.X;
		while (i != it->en.Y || j != it->en.X)
		{
			this->pBoard[i -= it->V][j -= it->H] = curPlayerColor;
		}
	}
}
void Board::MakeAMove(COORD coord, int curPlayerColor)
{
	this->MakeAMove(coord.X, coord.Y, curPlayerColor);
}
void Board::MakeAMove(list<LineOfDisks> possMoves, int x, int y, int curPlayerColor)
{
	this->pBoard[y][x] = curPlayerColor;
	int i, j;
	list<LineOfDisks>::iterator it;
	for (it = possMoves.begin(); it != possMoves.end(); it++)
	{
		i = it->st.Y;
		j = it->st.X;
		while (i != it->en.Y || j != it->en.X)
		{
			this->pBoard[i -= it->V][j -= it->H] = curPlayerColor;
		}
	}
}
void Board::MakeAMove(list<LineOfDisks> possMoves, COORD coord, int curPlayerColor)
{
	this->MakeAMove(possMoves, coord.X, coord.Y, curPlayerColor);
}
void Board::MakeAMoveBack(list<LineOfDisks> possMoves, int x, int y, int curPlayerColor)
{
	int i, j;
	list<LineOfDisks>::iterator it;
	for (it = possMoves.begin(); it != possMoves.end(); it++)
	{
		i = it->st.Y;
		j = it->st.X;
		while (i != it->en.Y || j != it->en.X)
		{
			this->pBoard[i][j] = curPlayerColor * -1;
			i -= it->V;
			j -= it->H;
		}
	}
	this->pBoard[y][x] = EMPTY;
}
void Board::MakeAMoveBack(list<LineOfDisks> possMoves, COORD coord, int curPlayerColor)
{
	this->MakeAMoveBack(possMoves, coord.X, coord.Y, curPlayerColor);
}

/*----------------------------- Other -----------------------------------------------------------------------*/
int Board::GetWiner()
{
	int winner = 0;
	for (int i = 0; i < BOARD_LENGTH; i++)
	{
		for (int j = 0; j < BOARD_LENGTH; j++)
		{
			winner += this->pBoard[i][j].GetStatus();
		}
	}
	if (winner > 0)
	{
		return WHITE;
	}
	else if (winner < 0)
	{
		return BLACK;
	}
	else
	{
		return DRAWN_GAME;
	}
}

void Board::SetStartDisks()
{
	for (int i = 0; i < BOARD_LENGTH; i++)
	{
		for (int j = 0; j < BOARD_LENGTH; j++)
		{
			this->pBoard[i][j] = EMPTY;
		}
	}

	pBoard[3][3] = WHITE;
	pBoard[3][4] = BLACK;
	pBoard[4][3] = BLACK;
	pBoard[4][4] = WHITE;

	this->blackPieces = 2;
	this->whitePieces = 2;
}

void Board::SetDisksCoords()
{
	for (int i = 0; i < BOARD_LENGTH; ++i)
	{
		for (int j = 0; j < BOARD_LENGTH; ++j)
		{
			pBoard[i][j] = COORD{ (SHORT)j, (SHORT)i };
		}
	}
}

bool Board::IsCoordOnBoard(COORD coord)
{
	return (coord.X >= 0 && coord.X <= 7) && (coord.Y >= 0 && coord.Y <= 7);
}

void Board::CountDisks()
{
	this->whitePieces = 0;
	this->blackPieces = 0;
	for (int i = 0; i < BOARD_LENGTH; i++)
	{
		for (int j = 0; j < BOARD_LENGTH; j++)
		{
			if (this->pBoard[i][j] == WHITE)
			{
				++this->whitePieces;
				continue;
			}
			if (this->pBoard[i][j] == BLACK)
			{
				++this->blackPieces;
				continue;
			}
		}
	}
}

bool Board::IsGameOver()
{
	if (this->blackPieces == 0)
	{
		return true;
	}
	else if (this->whitePieces == 0)
	{
		return true;
	}
	else if (this->whitePieces + this->blackPieces == 64)
	{
		return true;
	}
	else
	{
		return false;
	}
}

