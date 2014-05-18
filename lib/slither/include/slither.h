/**
 * @file	slither.h
 * @author	Jesús Ortiz
 * @version	1.0
 * @date	18-05-2014
 * @brief	Slitherlink main interface
 */

#ifndef SLITHER_H_
#define SLITHER_H_

/*
 * INCLUDES
 */

#include <iostream>
#include <string.h>


/*
 * DEFINES
 */

#define SLITHER_0		0
#define SLITHER_1		1
#define SLITHER_2		2
#define SLITHER_3		3
#define SLITHER_UNKNOWN	4

#define SLITHER_N		0
#define SLITHER_S		1
#define SLITHER_E		2
#define SLITHER_W		3

#define SLITHER_RESET	"\033[0m"
#define SLITHER_ON		"\033[1m"
#define SLITHER_OFF		"\033[2m"


/*
 * CLASS: Slither
 */

class Slither
{
private:
	int boardW;
	int boardH;
	unsigned char *board;

	int bordersVW;
	int bordersVH;
	unsigned char *bordersV;

	int bordersHW;
	int bordersHH;
	unsigned char *bordersH;

	bool allocated;

public:
	Slither();
	~Slither();

	void allocate(int w, int h);
	void deallocate();

	bool setCell(int i, int j, unsigned char value);
	bool setCells(unsigned char *values);
	bool clearCells();

	bool setBorder(int i, int j, int side, bool value);
	bool setBorders(unsigned char *horizontal, unsigned char *vertical);
	bool clearBorders();

	bool load(const std::string &filename);
	bool save(const std::string &filename);

	void print();
};

#endif	/* SLITHER_H_ */
