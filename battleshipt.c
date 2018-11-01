#include "battleshipt.h"

char declareBoardMode(void)
{
	char mode = 'n'; // n for null
	while (mode == 'n')
	{	
		printf("Pick the size of board you'd like to play!\n");
		printf("It can be a size of %d (EASY) - Command: 'e'\n", EASY_SIZE);
		printf("or can be a size of %d (MEDIUM) - Command: 'm'\n", MEDIUM_SIZE);
		printf("or can be a size of %d (HARD) - Command: 'h'\n", HARD_SIZE);
		printf("or can be a size of %d (XTREME)- Command: 'x'\n", XTREME_SIZE);
		mode = getchar();
		switch(mode) {
			case 'e':
				mode = 'e';
				break;
			case 'm':
				mode = 'm';
				break;
			case 'h':
				mode = 'h';
				break;
			case 'x':
				mode = 'x';
				break;
			default:
				mode = 'n';
				break;
		}
	}
	return mode;
}

int getBoardSize(char mode)
{
	int size = 0;
	switch(mode) {
		case 'e':
	                size = EASY_SIZE;
			printf("Easy mode selected\n");
        	        break;
                case 'm':
	                size = MEDIUM_SIZE;
			printf("Medium mode selected\n");
                        break;
           	case 'h':
                        size = HARD_SIZE;
			printf("Hard mode selected\n");
                        break;
                case 'x':
                        size = XTREME_SIZE;
			printf("Xtreme mode selected\n");
                        break;
                default:
                        size = 0;
                        break;
	}	
	return size;
}

void titleAndRules(void)
{
	printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>><<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n");
	printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>><<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n");
	printf("BBBBB     AAA   TTTTTTT TTTTTTT LL      EEEEEEE  SSSSS  HH   HH IIIII PPPPPP  TTTTTTT\n");
	printf("BB   B   AAAAA    TTT     TTT   LL      EE      SS      HH   HH  III  PP   PP   TTT\n");
	printf("BBBBBB  AA   AA   TTT     TTT   LL      EEEEE    SSSSS  HHHHHHH  III  PPPPPP    TTT\n");
	printf("BB   BB AAAAAAA   TTT     TTT   LL      EE           SS HH   HH  III  PP        TTT\n");
	printf("BBBBBB  AA   AA   TTT     TTT   LLLLLLL EEEEEEE  SSSSS  HH   HH IIIII PP        TTT\n");
	printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>><<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n");
	printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>><<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n");
	printf("   Welcome to Battleship! Brought to you by Taylor Wilson, interviewing for Shipt!\n");   
	printf("--- How to Play:\n");
	printf("1. Player 1 is you, Player 2 is the computer\n");
	printf("2. There are 4 gamemodes, Easy, Medium, Hard, and Xtreme\n");
	printf("3. Each of the game modes are of different sized boards\n");
	printf("4. There are 5 total ships to place: Carrier (5 cells), Battleship (4), Cruiser (3),\n");
	printf("	Submarine (3), and the Destroyer (2)!\n");
	printf("5. The game randomly select who will go first.\n");
	printf("6. First player to sink the other's ships wins!!!\n");
	printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>><<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n");
	printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>><<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n");
	
}

void buildBoard (Cell board[][COLS], int size)
{
	int i = 0, j = 0;
	for (i = 0; i < size; i++) {
		for (j = 0; j < size; j++) {
			//printf("%d - %d\n", i, j);
			board[i][j].symbol	 = WATER;
			board[i][j].position.row = i;
			board[i][j].position.col = j;
		}
	}
}

void printBoard(Cell board[][COLS], Boolean showPegs, int size) {
	
	
	int i = 0, j = 0;
	printf(" ");
	for(i = 0; i < size; i++)
		printf(" %c", 'A' + i);
	printf("\n");
	printf(" ");
	for(i = 0; i < size; i++)
		printf("--");
	printf("\n");
	for(i = 0; i < size; i++) {
		printf("%c|", 'A' + i);
		
		for(j = 0; j < size; j++) {
			if (showPegs == TRUE)
				printf("%c ", board[i][j].symbol);
			else {
				switch(board[i][j].symbol) {
					case HIT:	printf("%c ", HIT); break;
					case MISS:	printf("%c ", MISS);  break;
					case WATER:	
					default: 	printf("%c ", WATER); break;
				}
			}
		}
		putchar('\n');
	}
}

void manuallyPlaceShipsOnBoard(Cell board[][COLS], Watercraft ship[], int size)
{
	char	stringPosition[11] = "";
	int 	i = 0, j = 0;

	Coordinate position[5];
	Boolean isValidPosition = FALSE;
	
	fflush(stdin);
	char row = 0, col = 0;
	int option = -1;
		printf(">>> Please enter the coordinates as seen. 'E' should be typed as 'E' not 'e'\n");
		printf(">>> Direction - '0' = Horizontal - '1' = Vertical\n");
	for (i = 0; i < NUM_OF_SHIPS; i++) {

		printBoard(board, TRUE, size);		
		isValidPosition = FALSE;	
		while(TRUE) {	
			getchar();
			printf(">>> Where do you want to place your %s (Length = %d)?\n", ship[i].name, ship[i].length);
			printf(">>> Input should be the format below.\n'COL' 'ROW' 'DIRECTION'\n");
			scanf("%c %c %d", &col, &row, &option); 
	
			if (checkPlacementOptions(board, ship[i], row, col, option, size))
			{
				isValidPosition = TRUE;
				int r = row - 'A';
				int c = col - 'A';	
				for (j = 0; j < ship[i].length; j++) {
					if (option == HORIZONTAL) {
						board[r][c + j].symbol = ship[i].symbol;
					}
					else
						board[r + j][c].symbol = ship[i].symbol;
				}
			}
			else printf(">>> Invalid coordinates!\n");

			if (isValidPosition == TRUE) break;
		}
	}
}

Boolean checkPlacementOptions(Cell board[][COLS], Watercraft ship, char row, char col, int option, int size)
{
	Boolean isValidPlacement = TRUE;
	int i = 0;

	int r = row - 'A';
	int c = col - 'A';
	if (r < 0 || r > size)
		return FALSE;
	if (c < 0 || c > size)
		return FALSE;
	if (option != VERTICAL && option != HORIZONTAL)
		return FALSE;
	printf("BCS\n");
	if (option == HORIZONTAL)
	{
		if (ship.length + c > size) return FALSE;
		else
		{
			for (i = 0; i < ship.length; i++)
			{
				if (board[r][c + i].symbol != WATER)
					isValidPlacement = FALSE;	
			}
		}
	}
	else
	{
		if (ship.length + r > size) return FALSE;
		else
		{
			for (i = 0; i < ship.length; i++)
			{
				if (board[r + i][c].symbol != WATER)
					isValidPlacement = FALSE;
			}
		}
	}	
	return isValidPlacement;
}

void randomlyPlaceShipsOnBoard(Cell board[][COLS], Watercraft ship[], int size)
{
	Coordinate position;
	int direction = -1;
	int i = 0;
	
	for (i = 0; i < NUM_OF_SHIPS; i++) {
		while(TRUE) {
			direction = getRandomNumber(0, 1);
			position = generatePosition(direction, ship[i].length, size);
			if (isValidLocation(board, position, direction, ship[i].length, size))
				break;	
		}
			putShipOnBoard(board, ship[i], position, direction);
	}
}

Coordinate getTarget (void) {
	Coordinate target;
	char rC = 0, cC= 0;
	fflush(stdin);
	getchar();
	printf(">>> Enter a target (in the format below)\n");
	printf("'COL' 'ROW'\n");
	
	scanf("%c %c", &cC, &rC);
	int r =	rC - 'A';
	int c = cC - 'A';
	target.row = r;
	target.col = c;
	return target;
}

void updateBoard (Cell board[][COLS], Coordinate target) {
	switch (board[target.row][target.col].symbol) 
	{
		case WATER: 
			board[target.row][target.col].symbol = MISS;
			break;
		case CARRIER: 
		case BATTLESHIP:
		case CRUISER:
		case SUBMARINE:
		case DESTROYER:
			board[target.row][target.col].symbol = HIT;
			break;

		case HIT:
		case MISS:
		default:
			break;
	}	
}

int checkShot (Cell board[][COLS], Coordinate target)
{
	int hit = -2;
	switch (board[target.row][target.col].symbol) {
		case WATER:
			hit = 0;
			break;
		case CARRIER:
		case BATTLESHIP:
		case CRUISER:
		case SUBMARINE:
		case DESTROYER:
			hit = 1;
			break;
		case HIT:
		case MISS:
		default:
			hit = -1;
			break;
	}
	return hit;
}

Coordinate generatePosition (int direction, int length, int size) {
	Coordinate position;
	
	if (direction == HORIZONTAL) {
		position.row	= getRandomNumber (0, size);
		position.col = getRandomNumber (0, size - length);
	} else {
		position.row	= getRandomNumber (0, size - length);
		position.col = getRandomNumber (0, size); 
	}
	
	return position;
}

Boolean checkSunkShip (int sunkShip[][NUM_OF_SHIPS], int player, char shipSymbol)
{
	Boolean sunk = FALSE;
	
	switch (shipSymbol) {
	case CARRIER:    
			if (--sunkShip[player][0] == 0) {
				printf ("> Player %d's Carrier sunked!\n", player + 1);
				sunk = TRUE;
			}
			break;

		case BATTLESHIP: 
			if (--sunkShip[player][1] == 0) {
				printf ("> Player %d's Battleship sunked!\n", player + 1);
				sunk = TRUE;
			}
			break;

		case CRUISER:    
			if (--sunkShip[player][2] == 0) {
				printf ("> Player %d's Cruiser sunked!\n", player + 1);
				sunk = TRUE;
			}
			break;

		case SUBMARINE:  
			if (--sunkShip[player][3] == 0) {
				printf ("> Player %d's Submarine sunked!\n", player + 1);
				sunk = TRUE;
			}
			break;

		case DESTROYER:  
			if (--sunkShip[player][4] == 0) {
				printf ("> Player %d's Destroyer sunked!\n", player + 1);
				sunk = TRUE;
			}
			break;
	}

	return sunk;
}

Boolean isValidLocation (Cell board[][COLS], Coordinate position, int direction, int length, int size) 
{
	int i = length - 1;
	Boolean isValid = TRUE; //Assume true
	
	for (i = 0; isValid && i < length; i++) {
		if (direction == HORIZONTAL) {
			if (board[position.row][position.col + i].symbol != WATER &&
				(position.col + i) < size) {
					isValid = FALSE;
				}
			} 
			else {
				if (board[position.row + i][position.col].symbol != WATER && 
				(position.row + i) < size) {
					isValid = FALSE;
				}
			}
	}	
	return isValid;
}

void putShipOnBoard (Cell board[][COLS], Watercraft ship, Coordinate position, int direction)
{
	int i = ship.length - 1;
	for (i = 0; i < ship.length; i++) {
		if (direction == HORIZONTAL)
			board[position.row][position.col + i].symbol = ship.symbol;
		else
			board[position.row + i][position.col].symbol = ship.symbol;
	}
}

int getRandomNumber(int min, int max)
{
	if (max - min == 1) max += 1;
	int wow = (rand() % (max - min)) + min;
	return wow;
}
