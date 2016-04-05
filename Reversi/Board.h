#pragma once
#include "Disk.h"
using std::vector;
using std::list;

struct LineOfDisks
{
	// Line between two disks
	// start of line
	COORD st;
	// end of line
	COORD en;
	// line direction H - Horizontal and V - vertical 
	// possi values +1 and 1
	int H;
	int V;
	LineOfDisks()
	{
		this->clear();
	}
	void clear()
	{
		this->st.X = 0;
		this->st.Y = 0;
		this->en.X = 0;
		this->en.Y = 0;
		this->H = 0;
		this->V = 0;
	}
};

class Board
{
	friend class Ñontroller;
	friend class DrawReversi;

	COORD defBPos;

	//  Main board
	Disk ** pBoard;
	LineOfDisks dline;

	bool gameStarted;

	int whitePieces;
	int blackPieces;
	int turn;

	// List with possible moves from one position
	list<LineOfDisks> possibleMoves;
	// Board(Matrix) with lists of possible moves 
	list<LineOfDisks> ** pPossibleMoves;

	/*----------------------------- Creating and deleting board(matrix of Disks) --------------------------------*/
	void CreateBoard();
	void DeleteBoard();
	
	/*----------------------------- Creating and deleting board(matrix of lists with possible moves) ------------*/
	void CreateBoardOfPossibleMoves();
	void DeleteBoardOfPossibleMoves();

	/*----------------------------- Counting possible moves -----------------------------------------------------*/
	void CountPossibleMove(Disk* disk, int X, int Y, int playerColor);
	void CountPossibleMovesForDisk(Disk* disk, int playerColor);

	void ClearPPossibleMoves();

	/*----------------------------- Other -----------------------------------------------------------------------*/
	void SetStartDisks();
	void SetDisksCoords();

	bool IsCoordOnBoard(COORD coord);

public:
	Board();
	~Board();

	/*----------------------------- Making move on board forward and back ---------------------------------------*/
	void MakeAMove(int x, int y, int curPlayerColor);
	void MakeAMove(COORD coord, int curPlayerColor);
	void MakeAMove(list<LineOfDisks> possMoves, int x, int y, int curPlayerColor);
	void MakeAMove(list<LineOfDisks> possMoves, COORD coord, int curPlayerColor);
	void MakeAMoveBack(list<LineOfDisks> possMoves,int x, int y, int curPlayerColor);
	void MakeAMoveBack(list<LineOfDisks> possMoves, COORD coord, int curPlayerColor);

	/*----------------------------- Other -----------------------------------------------------------------------*/
	// Count black and white disks
	void CountDisks();

	bool IsGameOver();

	int GetWiner();
	
	void CountPossibleMoves(int playerColor);

	int GetWhitePieces() const { return this->whitePieces; }
	int GetBlackPieces() const { return this->blackPieces; }
};

