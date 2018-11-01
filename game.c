#include "battleshipt.h"


void mypause ( void ) 
{ 
  	printf ( ">>> Press <ENTER> to continue..." );
	fflush(stdin);
	while((getchar()) != '\n') { getchar(); }
} 

int main (void)
{
	srand ((unsigned int) time (NULL));
	
	Stats players[2] = {{0, 0, 0, 0.0}, {0, 0, 0, 0.0}};
	
	Coordinate target;
	Coordinate targetTemp;
	Coordinate targetOrigin;
	Coordinate targetAI;
	
	Watercraft ship[NUM_OF_SHIPS] = {{'C', 5, "Carrier"},
					 {'B', 4, "Battleship"}, 
	                                 {'R', 3, "Cruiser"}, 
	                                 {'S', 3, "Submarine"}, 
	                                 {'D', 2, "Destroyer"}
					};

	Boolean	hunting 	= TRUE;
	Boolean targetMode 	= FALSE;
	Boolean toggler		= TRUE;
	Boolean cardinals[4]	= {TRUE, TRUE, TRUE, TRUE}; // N, E, S, W
	Boolean sunk		= FALSE;

	int sunkShip[2][NUM_OF_SHIPS] = {{5, 4, 3, 3, 2},
					   {5, 4, 3, 3, 2}
					  };

	int 	player 	= 0;
	int	shot	= 0;
	char 	option;
	int 	north 	= 0,
		east	= 0,
		south	= 0,
		west	= 0;
	int 	i	= 0,
		counter = 1;

	char	shipSymbol = '\0';
	
	titleAndRules();
	mypause();

	option = declareBoardMode();
	int size = getBoardSize(option);
	
	Cell playerOneBoard[ROWS][COLS];
	Cell playerTwoBoard[ROWS][COLS];
	buildBoard(playerOneBoard, size);
	buildBoard(playerTwoBoard, size);
	
	//printBoard(playerOneBoard, FALSE, size);
	
	printf(">>> Would you like to place your ships randomly or manually?\n");
	printf(">>> Manually - Command 'm'\n");
	printf(">>> Randomly - Command 'r'\n");
	
	Boolean done = FALSE;
	while (!done) {
		option = getchar();
		switch(option) {
			case 'm':
				manuallyPlaceShipsOnBoard(playerOneBoard, ship, size);
				done = TRUE;	
				break;
			case 'r':
				randomlyPlaceShipsOnBoard(playerOneBoard, ship, size);
				done = TRUE;
				break;
			default:
				break;
		}
	}
	
	randomlyPlaceShipsOnBoard(playerTwoBoard, ship, size);
	
	player = getRandomNumber(0, 1);

	switch(player) {
		case 0:
			printf(">>> You will go first!\n");
			break;
		case 1:
			printf(">>> The computer will go first!\n");
			break;
	}
		
	while(TRUE) //Game loop
	{
		switch (player) {

			case PLAYER_ONE:
				printf(">>> HERE IS THE COMPUTER'S BOARD <<<\n");
				printBoard(playerTwoBoard, FALSE, size);
				printf(">>>>>>>>>>>>>YOUR TURN<<<<<<<<<<<<<<\n"); 
				do {
					target = getTarget();
					shot = checkShot(playerTwoBoard, target);
					if (shot == -1)	
						printf(">>> Try entering another target, please!\n");
				} while (shot == -1);
				shipSymbol = playerTwoBoard[target.row][target.col].symbol;
				break;

			case PLAYER_TWO:
				printf(">>> HERE IS THE YOUR BOARD <<<\n");
				printBoard(playerOneBoard, TRUE, size);
				do {
					target.row = rand() % (size - 1);
					target.col = rand() % (size - 1);
					shot = checkShot(playerOneBoard, target);	
				} while (shot == -1);
				shipSymbol = playerOneBoard[target.row][target.col].symbol;
				printf("Computer attacks at [%c][%c]\n", (char)target.col + 'A', (char)target.row + 'A');
				break;
		}
		
		if (shot == 1) {
			printf(">>> It's a HIT!\n");
			players[player].numHits++;
			if (player == 1)
				sunk = checkSunkShip (sunkShip, !player, shipSymbol);
			else
				checkSunkShip (sunkShip, !player, shipSymbol);
		}
		else {	
			printf(">>> It's a MISS!\n");
			players[player].numMisses++;
		}
	
		if (player == 0)
			updateBoard(playerTwoBoard, target);
		else
			updateBoard(playerOneBoard, target);
		if (players[player].numHits == 17)
		{
			printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
			printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
			printf("!!! PLAYER %d IS THE WINNER !!!!\n", player + 1);
			printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
			printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
			return 0;
		}
		player = !player;
	}
	return 0;
	
}
