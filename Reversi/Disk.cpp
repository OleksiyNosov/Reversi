#include "stdafx.h"
#include "Disk.h"
using std::cout;


Disk::Disk()
{
	*this = 0;
}

Disk::~Disk()
{
}

void Disk::TestPrint()
{
	cout << this->status;
}

Disk &Disk::operator=(const int status)
{
	this->status = status;
	switch (this->status)
	{
	case EMPTY:
		this->ConsoleColor = ccBlack;
		break;
	case WHITE:
		this->ConsoleColor = ccRed;
		break;
	case BLACK:
		this->ConsoleColor = ccBlue;
		break;
	}
	return *this;
}

Disk &Disk::operator=(const COORD coord)
{
	this->coord = coord;
	return *this;
}

bool Disk::operator==(const int color) const
{
	return this->status == color;
}

bool operator != (const Disk &disk, const int color)
{
	return !(disk == color);
}

bool operator == (const Disk &diskLeft, const Disk &diskRight)
{
	return diskLeft.GetStatus() == diskRight.GetStatus();
}
bool operator != (const Disk &diskLeft, const Disk &diskRight)
{
	return !(diskLeft == diskRight);
}



