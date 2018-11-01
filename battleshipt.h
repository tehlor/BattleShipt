// Taylor Wilson
// Take Home Assignment - Shipt
// Due - November 1st, 2018

#ifndef BATTLESHIPT_H
#define BATTLESHIPT_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>

#define ROWS 14
#define COLS 14

#define EASY_SIZE 8
#define MEDIUM_SIZE 10
#define HARD_SIZE 12
#define XTREME_SIZE 14

#define NUM_OF_SHIPS 5
#define HORIZONTAL 0
#define VERTICAL 1

#define PLAYER_ONE 0
#define PLAYER_TWO 1

#define WATER	'~'
#define HIT	'X'
#define MISS 	'o'

#define CARRIER 'C'
#define BATTLESHIP 'B'
#define CRUISER	'R'
#define SUBMARINE 'S'
#define DESTROYER 'D'

typedef enum {
	FALSE, TRUE
} Boolean;

typedef enum {
	CARRIER_LENGTH = 5,
	BATTLESHIP_LENGTH = 4,
	CRUISER_LENGTH = 3,
	SUBMARINE_LENGTH = 3,
	DESTROYER_LENGTH = 2
} ShipType;

typedef struct watercraft {
	char symbol;
	short length;
	char *name;
} Watercraft;

typedef struct stats {
	int numHits;
	int numMisses;
	int totalShots;
	double hitMissRatio;
} Stats;

typedef struct coordinate {
	int row;
	int col;
} Coordinate;

typedef struct cell {
	char symbol;
	Coordinate position;
} Cell;

char 		declareBoardMode		(void);
void 		buildBoard			(Cell board[][COLS], int);
void 		manuallyPlaceShipsOnBoard	(Cell board[][COLS], Watercraft ship[], int);
void 		randomlyPlaceShipsOnBoard	(Cell board[][COLS], Watercraft ship[], int);
void 		printBoard			(Cell board[][COLS], Boolean, int);
void		updateBoard			(Cell board[][COLS], Coordinate);
Coordinate	generatePosition		(int, int, int);
Coordinate	getTarget			(void);
Boolean 	checkSunkShip			(int sunkShip[][NUM_OF_SHIPS], int, char);
Boolean		isValidLocation			(Cell board[][COLS], Coordinate, int, int, int);
Boolean		checkPlacementOptions		(Cell board[][COLS], Watercraft, char, char, int, int);
int		checkShot			(Cell board[][COLS], Coordinate);
void 		putShipOnBoard			(Cell board[][COLS], Watercraft, Coordinate, int);
int 		getBoardSize			(char);
void 		titleAndRules			(void);
int		getRandomNumber			(int, int);
#endif
