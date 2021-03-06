#pragma once
#include "Menu.h"
#include "Board.h"
#include "DrawReversi.h"

//#define TEST_DRAW




using std::vector;

class Ņontroller
{
	Menu MainMenu;
	Menu SinglePMenu;
	Menu SinglePDiffMenu;
	Menu TwoPMenu;
	Board BoardR;
	DrawReversi DrawR;

	// Pointers to the objects in Controller
	Menu* mainMenu;
	Menu* singlePMenu;
	Menu* singlePDiffMenu;
	Menu* twoPMenu;
	Board* board;
	DrawReversi* drawR;

	vector<COORD> possMovePos;
	int pMovPosInx;
	int curPos;
	int curPlayerColor;
	int curGameStatus;
	int key;
	int botTime;

	/*----------------------------- Moving arrow in the game --------------------------------------------*/
	void CursorGoUp();
	void CursorGoDown();
	void CursorGoLeft();
	void CursorGoRight();

	/*----------------------------- Moving arrows in main menu ------------------------------------------*/
	void ArrowsGoUp(Menu* menu);
	void ArrowsGoDown(Menu* menu);

	/*----------------------------- Set some default values ---------------------------------------------*/
	void SetDefaultŅontrollerParameters();

	/*----------------------------- Set menu text -------------------------------------------------------*/
	void SetMenuParam();

public:
	Ņontroller();
	~Ņontroller();

	/*----------------------------- Methods that initialize menus ---------------------------------------*/
	void InitMainMenu();
	void InitSinglePMenu();
	void InitSinglePDiffMenu();
	void InitTwoPMenu();

	/*----------------------------- Methods that initialize start of game -------------------------------*/
	void StartGameSingle();
	void StartGamePvP();
	void StartGameSrectate();


	/*----------------------------- Moving into the game ------------------------------------------------*/
	void PlayerMove();

	void BotSmartMove();
	
	void BotMoveOnEasyDifficulty();
	void BotMoveOnMediumDifficulty();
	void BotMoveOnHardDifficulty();

	void BotRandomMove();

	/*----------------------------- Other ---------------------------------------------------------------*/

	// Filling the array with possible moves from the matrix of lists
	int PlayerChoose();

	// Getting code of pushed button
	void FillPossMovePos();
};

