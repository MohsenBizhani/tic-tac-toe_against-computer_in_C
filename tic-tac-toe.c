#include <stdio.h>
#include <stdlib.h>
#include <time.h>

char square[10] = { 'o', '1', '2', '3', '4', '5', '6', '7', '8', '9' };

// check if wthe game is over
int checkwin();
// print game board
void board();
// make computer move
int computer(int level, char mark, char enemy);
// check if the move is a valid move
int choiceValidation(int choice);
// make the move
void drawChoice(int choice, char mark, int level, int human);
// simulate what move will lead to win
int simulateWin(int choice, char mark);
// print the winner
int winner(char _winner[]);

int main()
{
	int i, choice;

	char mark, pc_mark;

	char player[] = "player", pc[] = "computer";


	int flag = 1;

	do
	{
		// get player mark
		printf("Enter your mark (X : O): ");
		scanf("%c", &mark);
		if (mark == 'X' || mark == 'x') {
			mark = 'X';
			pc_mark = 'O';
			flag = 0;
		}
		else if (mark == 'O' || mark == 'o') {
			mark = 'O';
			pc_mark = 'X';
			flag = 0;
		}
		else {
			printf("Invalid input\n");
		}
	} while (flag == 1);


	int level;

	flag = 1;
	do
	{
		// get computer level
		printf("Enter computer level (1 or 2): ");
		scanf("%d", &level);
		if (level == 1 || level == 2) {
			flag = 0;
		}
		else {
			printf("Invalid input\n");
		}
	} while (flag == 1);


	do {
		board();

		if (level == 1) {

			// get player move
			printf("Player, enter a number: ");
			scanf("%d", &choice);

			drawChoice(choice, mark, level, 1);
			if (winner(player) == 1) {
				return 0;
			}
			drawChoice(computer(level, pc_mark, mark), pc_mark, level, 0);
			if (winner(pc) == 1) {
				return 0;
			}

		}
		else if (level == 2) {

			// get player move
			printf("Player, enter a number: ");
			scanf("%d", &choice);

			drawChoice(choice, mark, level, 1);
			if (winner(player) == 1) {
				return 0;
			}
			drawChoice(computer(level, pc_mark, mark), pc_mark, level, 0);
			if (winner(pc) == 1) {
				return 0;
			}

			i = checkwin();
		}
	} while (i == -1);


	return 0;
}


int winner(char _winner[])
{
	// check if the game is over
	int i = checkwin();
	if (i == 1) {
		board();
		printf("%s won\n", _winner);
		return 1;
	}
	else if (i == 0) {
		board();
		printf("draw\n");
		return 1;
	}
	else {
		// game is not oevr
		return -1;
	}
}

int checkwin()
{

	// check the game is over
	if (square[1] == square[2] && square[2] == square[3])
		return 1;

	else if (square[4] == square[5] && square[5] == square[6])
		return 1;

	else if (square[7] == square[8] && square[8] == square[9])
		return 1;

	else if (square[1] == square[4] && square[4] == square[7])
		return 1;

	else if (square[2] == square[5] && square[5] == square[8])
		return 1;

	else if (square[3] == square[6] && square[6] == square[9])
		return 1;

	else if (square[1] == square[5] && square[5] == square[9])
		return 1;

	else if (square[3] == square[5] && square[5] == square[7])
		return 1;

	else if (square[1] != '1' && square[2] != '2' && square[3] != '3' &&
		square[4] != '4' && square[5] != '5' && square[6] != '6' && square[7]
		!= '7' && square[8] != '8' && square[9] != '9')

		return 0;
	else
		return  -1;
		// game is not over
}


void board()
{
	// clear the screen
	system("cls");
	printf("\n\n\tTic Tac Toe\n\n");

	// print game board
	printf("     |     |     \n");
	printf("  %c  |  %c  |  %c \n", square[1], square[2], square[3]);

	printf("_____|_____|_____\n");
	printf("     |     |     \n");

	printf("  %c  |  %c  |  %c \n", square[4], square[5], square[6]);

	printf("_____|_____|_____\n");
	printf("     |     |     \n");

	printf("  %c  |  %c  |  %c \n", square[7], square[8], square[9]);

	printf("     |     |     \n\n");
}

int computer(int level, char mark, char enemy)
{
	if (level == 1) {
		srand(time(0));
		int lower = 1, upper = 9;
		// make a random number 1 : 9
		int choice = (rand() % (upper - lower + 1)) + lower;
		// check if move is valid
		if (choiceValidation(choice) == 1)
		{
			return choice;
		}
		else {
			// move was invalid so make another
			return computer(1, mark, enemy);
		}
	}
	else if (level == 2) {
		for (int i = 1; i < 10; i++) {
			// check if move us valid
			if (choiceValidation(i) == 1)
			{
				// now that move is valid, check if it make us winner
				if (simulateWin(i, mark) == 1) {
					return i;
				}
				// so that can't make us win, check if it can prevent enemy to won
				if (simulateWin(i, enemy) == 1) {
						return i;
				}
			}
		}
	}
		// no move was there to make us win or prevent enemy to won, so make a random move
		return computer(1, mark, enemy);
}


int choiceValidation(int choice)
{
	char ch;
	char* chptr = &ch;
	sprintf(chptr, "%d", choice);
	// check if the square[choice] is empty
	if (square[choice] == ch) {
		return 1;
	}
	return 0;
}

int simulateWin(int choice, char mark)
{
	// check if move is valid
	if (choiceValidation(choice) == 1) {
		drawChoice(choice, mark, 2, 0);

		// check if move happen we will win 
		if (checkwin() == 1) {
			char ch;
			char* chptr = &ch;
			sprintf(chptr, "%d", choice);
			square[choice] = ch;
			return 1;
		}
		else {
			char ch;
			char* chptr = &ch;
			sprintf(chptr, "%d", choice);
			square[choice] = ch;
			return 0;
		}
	}
	else {
		return 0;
	}
	
}

void drawChoice(int choice, char mark, int level, int human)
{
	int flag = 0;
	// meke the move happen
	do {
		if (choice == 1 && square[1] == '1') {
			square[1] = mark;
		}
		else if (choice == 2 && square[2] == '2') {
			square[2] = mark;
		}
		else if (choice == 3 && square[3] == '3') {
			square[3] = mark;
		}
		else if (choice == 4 && square[4] == '4') {
			square[4] = mark;
		}
		else if (choice == 5 && square[5] == '5') {
			square[5] = mark;
		}
		else if (choice == 6 && square[6] == '6') {
			square[6] = mark;
		}
		else if (choice == 7 && square[7] == '7') {
			square[7] = mark;
		}
		else if (choice == 8 && square[8] == '8') {
			square[8] = mark;
		}
		else if (choice == 9 && square[9] == '9') {
			square[9] = mark;
		}
		else {
			if (human) {
				printf("Invalid move\n");
				printf("Enter a number: ");
				scanf("%d", &choice);
				flag = 1;
			}
		}
	} while (flag == 1);
}
