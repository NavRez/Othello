#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

enum players{ WHITE, BLACK };
const int EMPTY_SPACE = -1;
const int MAX_BOARD_SIZE = 12;
const int BOARD_SIZE = 8;
int board[BOARD_SIZE][BOARD_SIZE]; // board on which the game is played, defined as a two-dimensional array of squares

/* player types, defaulting to human versus human */
bool player1IsHuman = true;
bool player2IsHuman = true;

/* current scores of each player, initialised to zero */
int player1Score = 2;
int player2Score = 2;

/* Necessary values */
int firstcol = 0;
int secondcol = 0;
int thirdcol = 0;
int fourthcol = 0;
int position_up = 0;
int position_down = 0;
int position_left = 0;
int position_right = 0;
int position_left_up = 0;
int position_right_up = 0;
int position_left_down = 0;
int position_right_down = 0;
int flipped = 0;
int holdvalue = -1;


int validateMove(players, int, int, int board[BOARD_SIZE][BOARD_SIZE]);

void clearScreen()
{
	cout << string(50, '\n');
}


// Recall:	If we want to change the value of a function parameter so that the caller can see the change, we must "pass by reference", which is 
//			why we are using the ampersand ('&') character in the function declaration ("int splitString(string,int&,int&)").  This way the main()
//			function will be able to access the parsed x & y coordinates.
int splitString(string userInput, int &x, int &y)
{
	// Purpose:	Take user input and attempt to split it on the comma (if present).  If the split works, attempt to convert the resulting substring 
	//			into an integer.  If the conversion works, check that the integer value is valid (ie. between 1 and the size of the board).  If the 
	//			check works, mark the conversion as good and return the parsed values.
	//

	bool badVal = true;

	if (int i = userInput.find(',')){
		x = atoi(userInput.substr(0, i).c_str());
		y = atoi(userInput.substr(i + 1).c_str());
		x--;
		y--;
		if (x >= 0 && x <= BOARD_SIZE && y >= 0 && y <= BOARD_SIZE){
			badVal = false;
		}
	}

	return(badVal);
}

void getScore(players player)
{
	if (player == WHITE){
		player1Score+= flipped ;
		player2Score -= flipped;
	}
	else
	{
		player2Score += flipped ;
		player1Score -= flipped;
	}

	flipped = 0;
	// Purpose: Sets the player1Score and player1Score variables to the current score
}


void initialiseBoard()
{
	for (int x = 0; x < BOARD_SIZE; x++){
		for (int y = 0; y < BOARD_SIZE; y++){
			board[x][y] = -1;
		}
	}
	board[(BOARD_SIZE / 2) - 1][(BOARD_SIZE / 2) - 1] = 0;
	board[(BOARD_SIZE / 2) - 1][BOARD_SIZE / 2] = 1;
	board[BOARD_SIZE / 2][(BOARD_SIZE / 2) - 1] = 1;
	board[BOARD_SIZE / 2][BOARD_SIZE / 2] = 0;
	// Purpose: Initialize the board so that every spot is empty (EMPTY_SPACE), set the initial score as well as the
	//			initial placement of pieces.  Exit with an error if the defined board size is not an even number.

}


void printBoard()
{
	clearScreen();

	{
		cout << "  ";
		for (int z = 0; z < BOARD_SIZE; z++){
			cout << setw(3) << z + 1;
		}

		cout << endl;

		cout << "  ";
		for (int z = 0; z < BOARD_SIZE; z++){
			cout << setw(3) << "_";
		}

		cout << endl;

		for (int row = 0; row < BOARD_SIZE; row++){

			cout << row + 1 << ":" << setw(3);

			for (int col = 0; col < BOARD_SIZE; col++){
				if (board[row][col] == -1){
					cout << setw(3) << ".";
				}
				else if (board[row][col] == 1){
					cout << setw(3) << "*";
				}
				else if (board[row][col] == 0){
					cout << setw(3) << "0";
				}
				else
				{
					;
				}

			}
			cout << endl << endl;
		}
		cout << "Player 1 (0) score : " << player1Score << endl;
		cout << "Player 2 (*) score : " << player2Score << endl;

	}


	//for (int value = 0; value < BOARD_SIZE; value++){
	//	cout.width(3) << value + 1 << cout.width(1);
	//}



	// Purpose: Prints the current state of the board along with player scores.
}


int bestMove(players player, int& col, int& row){
	// Purpose: Get score of move for player (human or computer) that gives the biggest score
	//			For humans, use this to prove that they have a valid move to make
	//			Simply return -1 until implemented.

	return(-1);
}


int validateMove(players player, int col, int row, int myboard[][BOARD_SIZE]){
	// Purpose:		Validate whether (x,y) is a valid move for the player.
	// Input:		Recall that (x,y) are from user input and so are based from 1..BOARD_SIZE whereas the array is indexed from 0..(BOARD_SIZE - 1)
	// Return:		Score for the move (0 for invalid)


	if (board[col][row] != EMPTY_SPACE){
		return 0;
	}
	
	holdvalue = -1;
	int position = EMPTY_SPACE;
	
	//Check to see if there are any pieces to flip on the left
	for (int r = row - 1; r >= 0 && (board[col][row - 1] != player) && (board[col][r] != EMPTY_SPACE) && position == EMPTY_SPACE; r--){
		if (board[col][r] == player){
			position = r;
			position_left = r;
			holdvalue++;
		}
	} 
	
	
	//Checks to see if there are any pieces to flip on the right
	position = EMPTY_SPACE;
	for (int r = row + 1; r < BOARD_SIZE && (board[col][row + 1] != player) && (board[col][r] != EMPTY_SPACE) && position == EMPTY_SPACE; r++){
		if (board[col][r] == player){
			position = r;
			position_right = r;
			holdvalue++;
		}
	}

	//Checks to see if there are any pieces to flip on the top
	position = EMPTY_SPACE;
	for (int c = col - 1; c >= 0 && (board[col - 1][row] != player) && (board[c][row] != EMPTY_SPACE) && position == EMPTY_SPACE; c--){
		if (board[c][row] == player){
			position = c;
			position_up = c;
			holdvalue++;
		}
	}

	//Checks to see if there are any pieces to flip on the bottom
	position = EMPTY_SPACE;
	for (int c = col + 1; c < BOARD_SIZE && (board[col + 1][row] != player) && (board[c][row] != EMPTY_SPACE) && position == EMPTY_SPACE; c++){
		if (board[c][row] == player){
			position = c;
			position_down = c;
			holdvalue++;
		}
	}
	

	//Checks to see if there are any pieces to flip diagonal on the upper left
	position = EMPTY_SPACE;
	
	firstcol = col - 1;

	for (int r = row - 1; r >= 0 && firstcol >= 0 && board[firstcol][r] != EMPTY_SPACE && position == EMPTY_SPACE; r--){
		if (board[firstcol][r] == player){
			position = r;
			position_left_up = r;
			holdvalue++;
		}
		firstcol--;

	  }
	
	position = EMPTY_SPACE;
	secondcol = col + 1;

	for (int r = row - 1; r >= 0 && secondcol < BOARD_SIZE && board[secondcol][r] != EMPTY_SPACE && position == EMPTY_SPACE; r--){
		if (board[secondcol][r] == player){
			position = r;
			position_left_down = r;
			holdvalue++;
		}
		secondcol++;

	}

	position = EMPTY_SPACE;
	thirdcol = col + 1;

	for (int r = row + 1; r < BOARD_SIZE && thirdcol < BOARD_SIZE && board[thirdcol][r] != EMPTY_SPACE && position == EMPTY_SPACE; r++){
		if (board[thirdcol][r] == player){
			position = r;
			position_right_down = r;
			holdvalue++;
		}
		thirdcol++;

	}
	position = EMPTY_SPACE;
	fourthcol = col - 1;

	for (int r = row + 1; r < BOARD_SIZE && fourthcol >= 0 && board[fourthcol][r] != EMPTY_SPACE && position == EMPTY_SPACE; r++){
		if (board[fourthcol][r] == player){
			position = r;
			position_right_up = r;
			holdvalue++;
		}
		fourthcol--;

	}
	




	//Check to see if there are any pieces to flip on the left
	//position = EMPTY_SPACE; // resets position everytime

	/*THIS PORTION IS ALSO USELESS
	for (int c = col - 1; c >= 0 && board[c][row] != EMPTY_SPACE && position == EMPTY_SPACE; c--){
		if (board[c][row] == player){
			position = c;
			position_left = c;
		}
	}

		//Check to see if there are any pieces to flip on the bottom
		position = EMPTY_SPACE;

		for (int r = row + 1; r < BOARD_SIZE && board[col][r] != EMPTY_SPACE && position == EMPTY_SPACE; r++){
			if (board[col][r] == player){
				position = r;
				position_down = r;
			}
		}

		//Check to see if there are any pieces to flip on the top
		position = EMPTY_SPACE;

		for (int r = row - 1; r >= 0 && board[col][r] != EMPTY_SPACE && position == EMPTY_SPACE; r--){
			if (board[col][r] == player){
				position = r;
				position_up = r;
			}
		}

        //Checks to see if there are any pieces to flip diagonal on the upper left
			position = EMPTY_SPACE;
			firstcol = col - 1; 

			for (int r = row - 1; firstcol >= 0 && r >= 0 && board[firstcol][r] != EMPTY_SPACE && position == EMPTY_SPACE; r--){
				if (board[firstcol][r] == player){
					position = r;
					position_left_up = r;
				}
					firstcol--;
				
			}

				// Checks to see if there are any pieces to flip diagonal on the upper right
				position = EMPTY_SPACE;
				secondcol = col + 1;

				for (int r = row - 1; secondcol < BOARD_SIZE && r >= 0 && board[secondcol][r] != EMPTY_SPACE && position == EMPTY_SPACE; r--){
					if (board[secondcol][r] == player){
						position = r;
						position_right_up = r;
					}
					secondcol++;

				}

				// Checks to see if there are any pieces to flip diagonal on lower left
				position = EMPTY_SPACE;
				thirdcol = col - 1;

				for (int r = row + 1; thirdcol >= 0 && r < BOARD_SIZE && board[thirdcol][r] != EMPTY_SPACE && position == EMPTY_SPACE; r++){
					if (board[thirdcol][r] == player){
						position = r;
						position_left_down = r;
					}
					thirdcol--;

				}

			//Checks to see if there are any pieces to flip diagonal on lower right
				position = EMPTY_SPACE;
				fourthcol = col + 1;

				for (int r = row + 1; fourthcol < BOARD_SIZE && r < BOARD_SIZE && board[fourthcol][r] != EMPTY_SPACE && position == EMPTY_SPACE; r++){
					if (board[fourthcol][r] == player){
						position = r;
						position_right_up = r;
					}
					fourthcol++;

				}	

	//
	// Suggested Algorithm:	For a move to be valid, it must flip at least one piece.  If a move results in a flip of at least one piece, one of the flipped pieces will be adjacent
	//						to the move itself, so start by validating that way.  For any given move, there are up to 8 adjacent cells:  
	//							1) some of those adjacent cells may not be on the board, ignore them
	//							2) some of those adjacent cells may contain a piece of the same color as the player, ignore them as they aren't going to be flipped
	//							3) some of those adjacent cells may be empty, ignore them.
	//						Examine all of the adjacent cells against the rules above.  If no adjacent cell can be found that doesn't violate one of the rules, the move needs to be further
	//						examined by determining in which direction it's adjacent and then looking for a terminating piece in that direction.  Only if there is a terminating piece is the 
	//						move valid.  If we find an empty space, or run "out of board", the move is invalid.
	*/
	
	return (holdvalue);
}


int move(players player, int col, int row)
{
	// Purpose: This is the only function that should change the board array!  Take the col,row coordinates which have already been validated as a 
	//			valid move and change the array accordingly

	int check = validateMove(player, col, row, board);

	

	if (check != -1){ // Checks to see if validate move is true
		
		board[col][row] = player;
		//left
		if (position_left != 0){
			if (board[col][row - 1] == EMPTY_SPACE || board[col][row - 1] == player)
			{
				board[col][row] = EMPTY_SPACE;
			}

			if (position_left != EMPTY_SPACE && position_left < row - 1){
				for (int r = row - 1; r > position_left; r--)
				{
					board[col][r] = player;
					flipped++;
				}
				position_left = EMPTY_SPACE;
				board[col][row] = player;
			}

			
			if (position_up != EMPTY_SPACE && position_up < col - 1){
				for (int c = col - 1; c > position_up; c--)
				{
					board[c][row] = player;
					flipped++;
				}
				position_up = EMPTY_SPACE;
				board[col][row] = player;


				firstcol = col - 1;

				if (position_left_up != EMPTY_SPACE && position_left_up < row - 1){
					for (int r = row - 1; r > position_left_up && firstcol >= 0; r--)
					{
						board[firstcol][r] = player;
						flipped++;
						firstcol--;
					}
					position_left_up = EMPTY_SPACE;
					board[col][row] = player;
				}
			}



		} 



		//right
		if (position_right != 0){
			if (board[col][row + 1] == EMPTY_SPACE || board[col][row + 1] == player)
			{
				board[col][row] = EMPTY_SPACE;
				if (position_left == EMPTY_SPACE)
				{
					board[col][row] = player;
				}
			}

			if (position_right != EMPTY_SPACE && position_right > row + 1){
				board[col][row] = player;
				for (int r = row + 1; r < position_right; r++)
				{
					board[col][r] = player;
					flipped++;
				}
				position_right = EMPTY_SPACE;
			}
		}



		//up
		if (position_up != 0){
			

			if (board[col - 1][row] == EMPTY_SPACE || board[col - 1][row] == player)
			{
				board[col][row] = EMPTY_SPACE;
				if (position_left == EMPTY_SPACE || position_right == EMPTY_SPACE){

					board[col][row] = player;
				}
			}

			if (position_up != EMPTY_SPACE && position_up < col - 1){
				for (int c = col - 1; c > position_up; c--)
				{
					board[c][row] = player;
					flipped++;
				}
				position_up = EMPTY_SPACE;
				board[col][row] = player;
			}

			
		}



		//down
		if (position_down != 0){
			if (board[col + 1][row] == EMPTY_SPACE || board[col + 1][row] == player)
			{
				board[col][row] = EMPTY_SPACE;
				if (position_left == EMPTY_SPACE || position_right == EMPTY_SPACE || position_up == EMPTY_SPACE)
				{
					board[col][row] = player;
				}
			}

			if (position_down != EMPTY_SPACE && position_down > col + 1){
				board[col][row] = player;
				for (int c = col + 1; c < position_down; c++)
				{
					board[c][row] = player;
					flipped++;
				}
				position_down = EMPTY_SPACE;
			}
		}
		
		
		//left up
		if (position_left_up != 0){
			
			firstcol = col - 1;
			
			if (board[col][row - 1] == EMPTY_SPACE || board[col][row - 1] == player)
			{
				board[col][row] = EMPTY_SPACE;
				if (position_left == EMPTY_SPACE || position_right == EMPTY_SPACE || position_up == EMPTY_SPACE || position_down == EMPTY_SPACE)
				{
					board[col][row] = player;
				}
				
			}

			if (position_left_up != EMPTY_SPACE && position_left_up < row - 1){
				for (int r = row - 1; r > position_left_up && firstcol >= 0; r--)
				{
					board[firstcol][r] = player;
					flipped++;
					firstcol--;
				}
				position_left_up = EMPTY_SPACE;
				board[col][row] = player;
			}
		}


		//left down
		if (position_left_down != 0){

			secondcol = col + 1;

			if (board[col][row - 1] == EMPTY_SPACE || board[col][row - 1] == player)
			{
				board[col][row] = EMPTY_SPACE;
				if (position_left == EMPTY_SPACE || position_right == EMPTY_SPACE || position_up == EMPTY_SPACE || position_down == EMPTY_SPACE || position_left_up == EMPTY_SPACE)
				{
					board[col][row] = player;
				}

			}

			if (position_left_down != EMPTY_SPACE && position_left_down < row - 1){
				for (int r = row - 1; r > position_left_down && secondcol < BOARD_SIZE; r--)
				{
					board[secondcol][r] = player;
					flipped++;
					secondcol++;
				}
				position_left_down = EMPTY_SPACE;
				board[col][row] = player;
			}
		}

		//right  down
		if (position_right_down != 0){
			
			thirdcol = col + 1;
			
			if (board[col][row + 1] == EMPTY_SPACE || board[col][row + 1] == player)
			{
				board[col][row] = EMPTY_SPACE;
				if (position_left == EMPTY_SPACE || position_right == EMPTY_SPACE || position_up == EMPTY_SPACE || position_down == EMPTY_SPACE || position_left_up == EMPTY_SPACE || position_left_down == EMPTY_SPACE)
				{
					board[col][row] = player;
				}
			}

			if (position_right_down != EMPTY_SPACE && position_right_down > row + 1){
				board[col][row] = player;
				for (int r = row + 1; r < position_right_down && thirdcol < BOARD_SIZE; r++)
				{
					board[thirdcol][r] = player;
					flipped++;
					thirdcol++;
				}
				position_right_down = EMPTY_SPACE;
				board[col][row] = player;
			}
		}

		//right up
		if (position_right_up != 0){

			fourthcol = col - 1;

			if (board[col][row + 1] == EMPTY_SPACE || board[col][row + 1] == player)
			{
				board[col][row] = EMPTY_SPACE;
				if (position_left == EMPTY_SPACE || position_right == EMPTY_SPACE || position_up == EMPTY_SPACE || position_down == EMPTY_SPACE || position_left_up == EMPTY_SPACE || position_left_down == EMPTY_SPACE || position_right_up == EMPTY_SPACE)
				{
					board[col][row] = player;
				}
			}

			if (position_right_up != EMPTY_SPACE && position_right_up > row + 1){
				board[col][row] = player;
				for (int r = row + 1; r < position_right_up && fourthcol >= 0; r++)
				{
					board[fourthcol][r] = player;
					flipped++;
					fourthcol--;
				}
				position_right_up = EMPTY_SPACE;
				board[col][row] = player;
			}
		}

		/* THIS PORTION IS USELESS
		if (position_left != EMPTY_SPACE && position_left < col - 1){
		for (int c = col - 1; c > position_left; c--)
		{
		board[c][row] = player;
		flipped++;
		}
		}

		if (position_down != EMPTY_SPACE && position_down > row + 1){
		for (int r = row + 1; r < position_down; r++)
		{
		board[col][r] = player;
		flipped++;
		}

		}

		if (position_up != EMPTY_SPACE && position_up < row - 1){
		for (int r = row - 1; r > position_up; r--)
		{
		board[col][r] = player;
		flipped++;
		}
		}

		if (position_left_up != EMPTY_SPACE && position_left_up < row - 1){
		firstcol = col - 1;
		for (int r = row - 1; r > position_left_up; r--){
		board[firstcol][r] = player;
		flipped++;
		firstcol--;

		}
		}

		if (position_right_up != EMPTY_SPACE && position_right_up < row - 1){
		secondcol = col + 1;
		for (int r = row - 1; r > position_right_up; r--){
		board[secondcol][r] = player;
		flipped++;
		secondcol++;
		}
		}

		if (position_left_down != EMPTY_SPACE && position_left_down > row + 1){
		thirdcol = col - 1;
		for (int r = row + 1; r < position_left_down; r++){
		board[thirdcol][r] = player;
		flipped++;
		thirdcol--;
		}
		}

		if (position_right_up != EMPTY_SPACE && position_right_up > row + 1){
		fourthcol = col - 1;
		for (int r = row + 1; r < position_right_up; r++){
		board[fourthcol][r] = player;
		flipped++;
		fourthcol++;
		}
		}
		}

		*/

		/*if ((board[col - 1][row] = 1) && (board[col - 1][row] = -1))
		{
		board[col - 1][row] = 1;
		}
		*/

		int score = 1; // since we are playing a piece, we know the score will be at least 1

		return(score);
	}
}

int getHumanMove(players player, int& col, int& row){

	int x;

	int y;

	int chooseplayer;

	string mymove;

	bool Valmov = false;

	cout << "Which player is this?(Enter number only)" << endl;

	cin >> chooseplayer;

	if (chooseplayer == 1){
	thelabel:
		cout << "Enter x and y coordinates (seperate with commas):" << endl;
		cin >> mymove;
		if (mymove == "p")
		{
			return 0;
		}
		Valmov = splitString(mymove, x, y);
		move(WHITE, x, y);
		getScore(WHITE);
		while (!Valmov){
			if (mymove == "p")
			{
				Valmov = true;
				return 0;
			}
			else if (mymove == "q"){
				Valmov = true;
				return(-1);
			}
			else
			{
				
				return 0;

			}
		}
	}
	else
	{
		cout << "Enter x and y coordinates (seperate with commas):" << endl;
		cin >> mymove;
		if (mymove == "p"){
			return 0;
		}
		Valmov = splitString(mymove, x, y);
		move(BLACK, x, y);
		getScore(BLACK);

		while (!Valmov){
			if (mymove == "p")
			{
				Valmov = true;
				return 0;
			}
			else if (mymove == "q"){
				Valmov = true;
				return(-1);
			}
			else
			{
				
				return 0;

			}
		}
	}




	// Purpose: prompt human player for their turn (x,y), pass, or quit
	// Return: Score from the move (-1 for quit, 0 for pass).  i.e. if the player flips two pieces by playing, his score goes up by three (2 flips + 1 piece newly played)

	int score = -1;

	return(score);
}



void main(){
	int score1 = 1, score2 = 1;
	initialiseBoard();
	printBoard();

	// Start game
	while (true){
		int checkscore;
		int chosenx, choseny;

		score1 = bestMove(WHITE, chosenx, choseny);  // pass by reference
		printBoard();
		if (score1 == 0){ // Player 1 has no valid moves
			if (score2 == 0){ // finish game if player 2 also couldn’t move last time either
				break;
			}
		}
		else{
			if (player1IsHuman){
				score1 = getHumanMove(WHITE, chosenx, choseny);
				if (score1 == -1){
					break;
				}
			}
			// if player 1 is the computer, check that bestMove() is implemented
			else if (score1 == -1){ /* illegal score */
				cout << "Computer generated move (bestMove()) not implemented\n";
				exit(-1);
			}


			if (score1 == 0){	// check for pass by human player
				cout << "Player 1 has passed\n";
			}
			else{
				checkscore = move(WHITE, chosenx, choseny); // make move on the board
				if (score1 != checkscore){
					cerr << "inconsistent scores " << score1 << " " << checkscore << " for player 1 move" << endl;
					exit(-1);
				}
				printBoard();
			}
		}

		/* get score of move for player 2 that gives the biggest score */
		score2 = bestMove(BLACK, chosenx, choseny);
		printBoard();

		if (score2 == 0){ // Player 2 can’t go
			if (score1 == 0){ // finish game if player 1 couldn’t move last time either
				break;
			}
		}
		else{
			if (player2IsHuman){
				/* prompt human player 2 for their turn */
				score2 = getHumanMove(BLACK, chosenx, choseny);
				/* check for game termination */
				if (score2 == -1){
					break;
				}
			}
			else if (score2 == -1){ // illegal score
				cerr << "Computer generated move (bestMove()) not implemented" << endl;
				exit(-1);
			}
			/* check for pass by human player */
			if (score2 == 0){ // Player 2 has passed
			}
			else{
				// make move on the board
				checkscore = move(BLACK, chosenx, choseny);
				if (score2 != checkscore){
					printf("inconsistent scores %d %d for player 2 move\n", score2, checkscore);
					exit(-1);
				}
			}
			printBoard();
		}
	}

	cout << endl << endl << endl;

	system("pause");
	// game is over
}