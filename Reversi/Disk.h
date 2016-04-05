#pragma once

class Disk
{
	friend class DrawReversi;
	// status can be BLACK, WHITE or EMPTY
	int status; 
	COORD coord;
	WORD ConsoleColor;
public:
	Disk();
	~Disk();

	int GetStatus() const { return this->status; }
	COORD GetCoord() const { return this->coord; }

	void TestPrint();

	Disk &operator = (const int status);
	Disk &operator = (const COORD coord);
				    
	bool operator == (const int color) const;
};

bool operator != (const Disk &disk, const int color);

bool operator == (const Disk &diskLeft, const Disk &diskRight);
bool operator != (const Disk &diskLeft, const Disk &diskRight);

