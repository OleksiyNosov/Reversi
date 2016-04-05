// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

// Possible statuses of disk
#define EMPTY			0
#define WHITE			1
#define BLACK			-1

#define BOARD_LENGTH	8
#define DRAWN_GAME		0

// Items in main menu
#define SINGLE_PLAYER	0
#define TWO_PLAYERS		1
#define SPECTATE		2
#define OPTIONS			3
#define EXIT			4

// Items in single player menu
#define START_NEW		0
#define LOAD_LAST		1

// Difficulties in single player menu
#define EASY			0
#define MEDIUM			1
#define HARD			2
#define RANDOM			3

#define NEW_GAME		8
#define GAME_OVER		9

// Codes of keys
#define ENTER			13
#define ESC				27
#define ARROW_UP		72
#define ARROW_LEFT		75
#define ARROW_RIGHT		77
#define ARROW_DOWN		80

// Directions for  function that search posible moves
#define UP				-1		
#define DOWN			1		
#define RIGHT			1	
#define LEFT			-1	
#define CENTER			0

#define WHITE_STR "Red"
#define BLACK_STR "Blue"

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>
#include <Windows.h>
#include <iostream>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <vector>
#include <string>
#include <list>

enum {
	ccBlack,
	ccDarkBlue,
	ccDarkGreen,
	ccDarkCyan,
	ccDarkRed,
	ccDarkMagneta,
	ccDarkYellow,

	ccGrey,
	ccDarkGrey,
	ccBlue,
	ccGreen,
	ccCyan,
	ccRed,
	ccMagneta,
	ccYellow,
	ccWhite
};



// TODO: reference additional headers your program requires here
