/**
 * @file	slither.cpp
 * @author	Jesús Ortiz
 * @version	1.0
 * @date	18-05-2014
 * @brief	Slitherlink main interface
 */

/*
 * INCLUDES
 */

#include "slither.h"


/*
 * CLASS: Slither
 */

Slither::Slither()
{
	this->boardW = 0;
	this->boardH = 0;
	this->board = NULL;

	this->bordersVW = 0;
	this->bordersVH = 0;
	this->bordersV = NULL;

	this->bordersHW = 0;
	this->bordersHH = 0;
	this->bordersH = NULL;

	this->allocated = false;
}

Slither::~Slither()
{
	this->deallocate();
}

void Slither::allocate(int w, int h)
{
	this->deallocate();

	this->boardW = w;
	this->boardH = h;
	this->board = new unsigned char[this->boardW * this->boardH];

	this->bordersVW = w + 1;
	this->bordersVH = h;
	this->bordersV = new unsigned char[this->bordersVW * this->bordersVH];

	this->bordersHW = w;
	this->bordersHH = h + 1;
	this->bordersH = new unsigned char[this->bordersHW * this->bordersHH];

	this->allocated = true;

	this->clearBorders();
	this->clearCells();
}

void Slither::deallocate()
{
	if (this->allocated)
	{
		this->boardW = 0;
		this->boardH = 0;
		delete [] this->board;
		this->board = NULL;

		this->bordersVW = 0;
		this->bordersVH = 0;
		delete [] this->bordersV;
		this->bordersV = NULL;

		this->bordersHW = 0;
		this->bordersHH = 0;
		delete [] this->bordersH;
		this->bordersH = NULL;

		this->allocated = false;
	}
}

bool Slither::setCell(int i, int j, unsigned char value)
{
	if (!this->allocated)
		return false;

	if (i < 0 || i >= this->boardW || j < 0 || j >= this->boardH)
		return false;

	this->board[i + j * this->boardW] = value;
	return true;
}

bool Slither::setCells(unsigned char *values)
{
	if (!this->allocated)
		return false;

	memcpy(this->board, values, this->boardW * this->boardH);
	return true;
}

bool Slither::clearCells()
{
	if (!this->allocated)
		return false;

	for (int i = 0; i < this->boardW * this->boardH; i++)
		this->board[i] = SLITHER_UNKNOWN;

	return true;
}

bool Slither::setBorder(int i, int j, int side, bool value)
{
	if (!this->allocated)
		return false;

	if (i < 0 || i >= this->boardW || j < 0 || j >= this->boardH)
		return false;

	if (i == 0 && side == SLITHER_W)
		return false;

	if (i == this->boardW - 1 && side == SLITHER_E)
		return false;

	if (j == 0 && side == SLITHER_N)
		return false;

	if (j == this->boardH - 1 && side == SLITHER_S)
		return false;

	switch (side)
	{
	case SLITHER_N:
		this->bordersH[i + j * this->bordersHW] = value;
		break;
	case SLITHER_S:
		this->bordersH[i + (j + 1) * this->bordersHW] = value;
		break;
	case SLITHER_E:
		this->bordersV[(i + 1) + j * this->bordersVW] = value;
		break;
	case SLITHER_W:
		this->bordersV[i + j * this->bordersVW] = value;
		break;
	default:
		return false;
	}

	return true;
}

bool Slither::setBorders(unsigned char *horizontal, unsigned char *vertical)
{
	if (!this->allocated)
		return false;

	memcpy(this->bordersH, horizontal, this->bordersHW * this->bordersHH);
	memcpy(this->bordersV, vertical, this->bordersVW * this->bordersVH);
	return true;
}

bool Slither::clearBorders()
{
	if (!this->allocated)
		return false;

	for (int i = 0; i < this->bordersHW * this->bordersHH; i++)
		this->bordersH[i] = 0;

	for (int i = 0; i < this->bordersVW * this->bordersVH; i++)
		this->bordersV[i] = 0;

	return true;
}

void Slither::print()
{
	if (!this->allocated)
		return;

	std::cout << std::endl;

	// Print first horizontal borders
	for (int i = 0; i < this->boardW; i++)
	{
		std::cout << " ";

		if (this->bordersH[i])
			std::cout << SLITHER_ON;
		else
			std::cout << SLITHER_OFF;

		std::cout << "___";
	}
	std::cout << std::endl;

	for (int j = 0; j < this->boardH; j++)
	{
		// Print vertical borders and numbers
		for (int i = 0; i < this->boardW; i++)
		{
			// Print vertical border
			if (this->bordersV[i + j * this->bordersVW])
				std::cout << SLITHER_ON;
			else
				std::cout << SLITHER_OFF;
			std::cout << "|";

			// Print number
			std::cout << SLITHER_RESET;
			std::cout << " ";

			if (this->board[i + j * this->boardW] != SLITHER_UNKNOWN)
				std::cout << (int)this->board[i + j * this->boardW];
			else
				std::cout << " ";

			std::cout << " ";
		}

		// Print last vertical border
		if (this->bordersV[this->bordersVW - 1 + j * this->bordersVW])
			std::cout << SLITHER_ON;
		else
			std::cout << SLITHER_OFF;
		std::cout << "|";

		std::cout << std::endl;

		// Print vertical borders and horizontal border
		for (int i = 0; i < this->boardW; i++)
		{
			// Print vertical border
			if (this->bordersV[i + j * this->bordersVW])
				std::cout << SLITHER_ON;
			else
				std::cout << SLITHER_OFF;
			std::cout << "|";

			// Print horizontal border
			if (this->bordersH[i + (j + 1) * this->bordersHW])
				std::cout << SLITHER_ON;
			else
				std::cout << SLITHER_OFF;
			std::cout << "___";
		}

		// Print last vertical border
		if (this->bordersV[this->bordersVW - 1 + j * this->bordersVW])
			std::cout << SLITHER_ON;
		else
			std::cout << SLITHER_OFF;
		std::cout << "|";

		std::cout << std::endl;
	}

	std::cout << SLITHER_RESET;
	std::cout << std::endl;
}
