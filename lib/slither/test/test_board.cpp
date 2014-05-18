/**
 * @file	test_board.cpp
 * @author	Jesús Ortiz
 * @version	1.0
 * @date	18-05-2014
 * @brief	Test the Slither Link board
 */

/*
 * INCLUDES
 */

#include "slither.h"


/*
 * MAIN
 */

int main(int argc, char *argv[])
{
	Slither slither;
	slither.allocate(9, 7);
	slither.print();

	slither.setCell(2, 2, 2);
	slither.setBorder(2, 2, SLITHER_N, true);
	slither.setBorder(2, 2, SLITHER_S, true);
	slither.setBorder(2, 2, SLITHER_E, true);
	slither.setBorder(2, 2, SLITHER_W, true);
	slither.print();

	return 0;
}
