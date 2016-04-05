#include "stdafx.h"
#include "Ñontroller.h"
using std::cout;
using std::endl;

Ñontroller::Ñontroller()
{
	this->mainMenu = &this->MainMenu;
	this->singlePMenu = &this->SinglePMenu;
	this->singlePDiffMenu = &this->SinglePDiffMenu;
	this->twoPMenu = &this->TwoPMenu;
	this->drawR = &this->DrawR;
	this->board = &this->BoardR;

	this->SetMenuParam();
}
Ñontroller::~Ñontroller()
{
}

/*----------------------------- Moving arrow in the game --------------------------------------------*/
void Ñontroller::CursorGoUp()
{
	this->drawR->PaintOverCursor(this->possMovePos[curPos]);
	curPos = --curPos % possMovePos.size();
	this->drawR->DrawCursor(this->possMovePos[curPos]);
}
void Ñontroller::CursorGoDown()
{
	this->drawR->PaintOverCursor(this->possMovePos[curPos]);
	curPos = ++curPos % possMovePos.size();
	this->drawR->DrawCursor(this->possMovePos[curPos]);
}
void Ñontroller::CursorGoLeft()
{
	this->CursorGoUp();
}
void Ñontroller::CursorGoRight()
{
	this->CursorGoDown();
}

/*----------------------------- Moving arrows in main menu ------------------------------------------*/
void Ñontroller::ArrowsGoUp(Menu* menu)
{
	if (menu->curMenuStr > 0)
	{
		drawR->PaintOverArrows(menu);
		--menu->curMenuStr;
		drawR->DrawArrows(menu);
	}
}
void Ñontroller::ArrowsGoDown(Menu* menu)
{
	if (menu->curMenuStr < menu->mText.size() - 1)
	{
		drawR->PaintOverArrows(menu);
		++menu->curMenuStr;
		drawR->DrawArrows(menu);
	}
}

/*----------------------------- Set some default values ---------------------------------------------*/
void Ñontroller::SetDefaultÑontrollerParameters()
{
	this->key = 0;
	this->curPlayerColor = BLACK;
	int curGameStatus = BLACK;
	this->curPos = 0;
	this->botTime = 750;
}

/*----------------------------- Set menu text -------------------------------------------------------*/
void Ñontroller::SetMenuParam()
{
	this->MainMenu.AddMenuText("Single player");
	this->MainMenu.AddMenuText("Two player");
	this->MainMenu.AddMenuText("Spectate");
	this->MainMenu.AddMenuText("Options");
	this->MainMenu.AddMenuText("Exit");

	this->SinglePMenu.AddMenuText("Start new");
	this->SinglePMenu.AddMenuText("Load last");

	this->SinglePDiffMenu.AddMenuText("Easy");
	this->SinglePDiffMenu.AddMenuText("Medium");
	this->SinglePDiffMenu.AddMenuText("Hard");

	this->TwoPMenu.AddMenuText("Start new");
	this->TwoPMenu.AddMenuText("Load last");

}

/*----------------------------- Methods that initialize menus ---------------------------------------*/
void Ñontroller::InitMainMenu()
{
	system("cls");
	this->drawR->DrawMenu(this->mainMenu);
	this->drawR->DrawArrows(this->mainMenu);
	int key = 0;
	while (true)
	{
		key = _getch();
		switch (key)
		{
		case ARROW_UP:
			this->ArrowsGoUp(this->mainMenu);
			break;
		case ARROW_DOWN:
			this->ArrowsGoDown(this->mainMenu);
			break;
		case ENTER:
			switch (this->mainMenu->curMenuStr)
			{
			case SINGLE_PLAYER:
				this->InitSinglePDiffMenu();
				this->drawR->DrawMenu(this->mainMenu);
				this->drawR->DrawArrows(this->mainMenu);
				break;
			case TWO_PLAYERS:
				this->InitTwoPMenu();
				this->drawR->DrawMenu(this->mainMenu);
				this->drawR->DrawArrows(this->mainMenu);
				break;
			case SPECTATE:
				this->curGameStatus = NEW_GAME;
				this->board->gameStarted = true;
				this->StartGameSrectate();
				this->drawR->DrawMenu(this->mainMenu);
				this->drawR->DrawArrows(this->mainMenu);
				break;
			case OPTIONS:
				// not implemented yet
				break;
			case EXIT:
				return;
				break;
			}
			break;
		case ESC:
			return;
		}
	}
}
void Ñontroller::InitSinglePMenu()
{
	system("cls");
	this->drawR->DrawMenu(this->singlePMenu);
	this->drawR->DrawArrows(this->singlePMenu);
	int key = 0;
	while (true)
	{
		key = _getch();
		switch (key)
		{
		case ARROW_UP:
			this->ArrowsGoUp(this->singlePMenu);
			break;
		case ARROW_DOWN:
			this->ArrowsGoDown(this->singlePMenu);
			break;
		case ENTER:
			switch (this->singlePMenu->curMenuStr)
			{
			case START_NEW:
				this->InitSinglePDiffMenu();
				this->drawR->DrawMenu(this->singlePMenu);
				this->drawR->DrawArrows(this->singlePMenu);
				break;
			case EXIT:
				return;
				break;
			}
			break;
		case ESC:
			return;
		}
	}
}
void Ñontroller::InitSinglePDiffMenu()
{
	system("cls");
	this->drawR->DrawMenu(this->singlePDiffMenu);
	this->drawR->DrawArrows(this->singlePDiffMenu);
	int key = 0;
	while (true)
	{
		key = _getch();
		switch (key)
		{
		case ARROW_UP:
			this->ArrowsGoUp(this->singlePDiffMenu);
			break;
		case ARROW_DOWN:
			this->ArrowsGoDown(this->singlePDiffMenu);
			break;
		case ENTER:
			switch (this->singlePDiffMenu->curMenuStr)
			{
			case EASY:
			case MEDIUM:
			case HARD:
				this->botTime = 100;
				this->curGameStatus = NEW_GAME;
				this->board->gameStarted = true;
				this->StartGameSingle();
				this->drawR->DrawMenu(this->singlePDiffMenu);
				this->drawR->DrawArrows(this->singlePDiffMenu);
				break;
			case EXIT:
				return;
				break;
			}
			break;
		case ESC:
			return;
		}
	}
}
void Ñontroller::InitTwoPMenu()
{
	system("cls");
	this->drawR->DrawMenu(this->twoPMenu);
	this->drawR->DrawArrows(this->twoPMenu);
	int key = 0;
	//_getch();
	while (true)
	{
		key = _getch();
		switch (key)
		{
		case ARROW_UP:
			this->ArrowsGoUp(this->twoPMenu);
			break;
		case ARROW_DOWN:
			this->ArrowsGoDown(this->twoPMenu);
			break;
		case ENTER:
			switch (this->twoPMenu->curMenuStr)
			{
			case START_NEW:
				this->curGameStatus = NEW_GAME;
				this->board->gameStarted = true;
				this->StartGamePvP();

				this->drawR->DrawMenu(this->twoPMenu);
				this->drawR->DrawArrows(this->twoPMenu);
				break;
			case LOAD_LAST:
				if (this->board->gameStarted)
				{
					this->StartGamePvP();

					this->drawR->DrawMenu(this->twoPMenu);
					this->drawR->DrawArrows(this->twoPMenu);
				}
				break;
			case EXIT:
				return;
				break;
			}
			break;
		case ESC:
			return;
		}
	}
}

/*----------------------------- Methods that initialize start of game -------------------------------*/
void Ñontroller::StartGameSingle()
{
	this->SetDefaultÑontrollerParameters();

	switch (this->curGameStatus)
	{
	case BLACK:
		break;
	case WHITE:
		break;
	case ESC:
		this->curGameStatus = this->curPlayerColor;
		return;
	case GAME_OVER:
		this->board->SetStartDisks();
		this->board->gameStarted = false;
		break;
	case NEW_GAME:
		this->board->SetStartDisks();
		this->curGameStatus = BLACK;
		this->board->ClearPPossibleMoves();
		this->possMovePos.clear();
		this->curPlayerColor = BLACK;
		this->curPos = 0;
		break;
	}

	this->drawR->DrawBoard(this->board);
	this->drawR->DrawDisks(this->board);
	this->drawR->DrawScore(this->board);

	while (true)
	{
		switch (this->curGameStatus)
		{
		case BLACK:
			this->PlayerMove();
			break;
		case WHITE:
			this->BotRandomMove();
			break;
		case GAME_OVER:
			this->drawR->GameOver(board->GetWiner());
			this->board->gameStarted = false;
			return;
		case ESC:
			return;
		}
	}
}
void Ñontroller::StartGamePvP()
{
	this->SetDefaultÑontrollerParameters();

	switch (this->curGameStatus)
	{
	case BLACK:
		break;
	case WHITE:
		break;
	case ESC:
		this->curGameStatus = this->curPlayerColor;
		return;
	case GAME_OVER:
		this->board->SetStartDisks();
		this->board->gameStarted = false;
		break;
	case NEW_GAME:
		this->board->SetStartDisks();
		this->curGameStatus = BLACK;
		this->board->ClearPPossibleMoves();
		this->possMovePos.clear();
		this->curPlayerColor = BLACK;
		this->curPos = 0;
		break;
	}

	this->drawR->DrawBoard(this->board);
	this->drawR->DrawDisks(this->board);
	this->drawR->DrawScore(this->board);
	
	while (true)
	{
		switch (this->curGameStatus)
		{
		case BLACK:
			this->PlayerMove();
			break;
		case WHITE:
			this->PlayerMove();
			break;
		case GAME_OVER:
			this->drawR->GameOver(board->GetWiner());
			this->board->gameStarted = false;
			return;
		case ESC:
			return;
		}
	}
}
void Ñontroller::StartGameSrectate()
{
	this->SetDefaultÑontrollerParameters();

	switch (this->curGameStatus)
	{
	case BLACK:
		break;
	case WHITE:
		break;
	case ESC:
		this->curGameStatus = this->curPlayerColor;
		return;
	case GAME_OVER:
		this->board->SetStartDisks();
		this->board->gameStarted = false;
		break;
	case NEW_GAME:
		this->botTime = 800;
		this->board->SetStartDisks();
		this->curGameStatus = BLACK;
		this->board->ClearPPossibleMoves();
		this->possMovePos.clear();
		this->curPlayerColor = BLACK;
		this->curPos = 0;
		break;
	}

	this->drawR->DrawBoard(this->board);
	this->drawR->DrawDisks(this->board);
	this->drawR->DrawScore(this->board);

	while (true)
	{
		switch (this->curGameStatus)
		{
		case BLACK:
			this->BotRandomMove();
			break;
		case WHITE:
			this->BotRandomMove();
			break;
		case GAME_OVER:
			this->drawR->GameOver(board->GetWiner());
			this->board->gameStarted = false;
			return;
		case ESC:
			return;
		}
	}
}

/*----------------------------- Moving into the game ------------------------------------------------*/
void Ñontroller::PlayerMove()
{
	while (true)
	{
		if (this->board->IsGameOver())
		{
			this->curGameStatus = GAME_OVER;
			this->board->gameStarted = false;
			return;
		}
		this->board->CountPossibleMoves(curPlayerColor);
		this->board->CountDisks();
		
		this->drawR->DrawScore(this->board);
		this->drawR->DrawPossiblePos(this->board, this->curPlayerColor);

		this->FillPossMovePos();
		if (this->possMovePos.empty())
		{
			this->curPlayerColor *= -1;
			this->curGameStatus = this->curPlayerColor;
			return;
		}
		
		this->drawR->DrawCursor(this->possMovePos[curPos]);
		switch (this->PlayerChoose())
		{
		case ENTER:
			this->drawR->PaintOverPossiblePos(this->board);
			this->board->MakeAMove(possMovePos[curPos], curPlayerColor);
			this->drawR->DrawAMove(this->board, possMovePos[curPos], curPlayerColor);
			this->board->ClearPPossibleMoves();
			this->possMovePos.clear();

			this->curPlayerColor *= -1;
			this->curGameStatus = this->curPlayerColor;
			this->curPos = 0;
			return;
		case ESC:
			this->board->ClearPPossibleMoves();
			this->possMovePos.clear();
			this->curGameStatus = ESC;
			return;
		}
	}
}

void Ñontroller::BotSmartMove()
{
	int key;

	if (this->board->IsGameOver())
	{
		this->curGameStatus = GAME_OVER;
		this->board->gameStarted = false;
		return;
	}
	this->board->CountPossibleMoves(curPlayerColor);
	this->board->CountDisks();

	this->drawR->DrawScore(this->board);

	this->FillPossMovePos();
	if (this->possMovePos.empty())
	{
		this->curPlayerColor *= -1;
		this->curGameStatus = this->curPlayerColor;
		return;
	}

	Sleep(this->botTime);
	if (_kbhit())
	{
		key = _getch();
		if (key == ESC)
		{
			this->curGameStatus = ESC;
			return;
		}
	}

	srand(time(NULL));
	curPos = rand() % possMovePos.size();

	this->board->MakeAMove(possMovePos[curPos], curPlayerColor);
	this->drawR->DrawAMove(this->board, possMovePos[curPos], curPlayerColor);
	this->board->ClearPPossibleMoves();
	this->possMovePos.clear();

	this->curPlayerColor *= -1;
	this->curGameStatus = this->curPlayerColor;
	this->curPos = 0;
}

void Ñontroller::BotMoveOnEasyDifficulty()
{

}
void Ñontroller::BotMoveOnMediumDifficulty()
{

}
void Ñontroller::BotMoveOnHardDifficulty()
{

}

void Ñontroller::BotRandomMove()
{
	int key;

	if (this->board->IsGameOver())
	{
		this->curGameStatus = GAME_OVER;
		this->board->gameStarted = false;
		return;
	}
	this->board->CountPossibleMoves(curPlayerColor);
	this->board->CountDisks();

	this->drawR->DrawScore(this->board);

	this->FillPossMovePos();
	if (this->possMovePos.empty())
	{
		this->curPlayerColor *= -1;
		this->curGameStatus = this->curPlayerColor;
		return;
	}

	Sleep(this->botTime);
	if (_kbhit())
	{
		key = _getch();
		if (key == ESC)
		{
			this->curGameStatus = ESC;
			return;
		}
		
	}

	srand(time(NULL));
	curPos = rand() % possMovePos.size();

	this->board->MakeAMove(possMovePos[curPos], curPlayerColor);
	this->drawR->DrawAMove(this->board, possMovePos[curPos], curPlayerColor);
	this->board->ClearPPossibleMoves();
	this->possMovePos.clear();

	this->curPlayerColor *= -1;
	this->curGameStatus = this->curPlayerColor;
	this->curPos = 0;
}

/*----------------------------- Other ---------------------------------------------------------------*/

// Filling the array with possible moves from the matrix of lists
void Ñontroller::FillPossMovePos()
{
	for (int i = 0; i < BOARD_LENGTH; i++)
	{
		for (int j = 0; j < BOARD_LENGTH; j++)
		{
			list<LineOfDisks> * possibleMoves = &board->pPossibleMoves[i][j];
			list<LineOfDisks>::iterator it;
			for (it = possibleMoves->begin(); it != possibleMoves->end(); it++)
			{
				this->possMovePos.emplace_back(COORD{ it->st.X, it->st.Y });
				break;
			}
		}
	}
}

// Getting code of pushed button
int Ñontroller::PlayerChoose()
{
	int key;
	while (true)
	{
		key = _getch();
		switch (key)
		{
		case ARROW_UP:
			this->CursorGoUp();
			break;
		case ARROW_DOWN:
			this->CursorGoDown();
			break;
		case ARROW_LEFT:
			this->CursorGoLeft();
			break;
		case ARROW_RIGHT:
			this->CursorGoRight();
			break;
		case ESC:
			return ESC;
		case ENTER:
			return ENTER;
		}
	}
}
