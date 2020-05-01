#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#define BOARD_SIZE 8	// size of chessboard
#define QUEEN 1			// const the queen value
#define NOT_QUEEN 0		// const the not queen value


/* The function check for all options */
void queens(int board[][BOARD_SIZE], int solution_num);
/* puting the queens on the board */
int mark_queens(int board[][BOARD_SIZE], int solution_num, int col);
/* the function check the current place */
int check_place(int board[][BOARD_SIZE], int row, int col);
/* the function check if there is a queen in the direction */
int check_direction(int board[][BOARD_SIZE], int row, int col, int direction_row, int direction_col);
/* the function print the table of the queens */
void print_board(int board[][BOARD_SIZE], int row, int col);

/* Main function */
int main()
{
	int solution_num=0;
	int board[BOARD_SIZE][BOARD_SIZE] = { 0 };
	
	printf("Enter the number of the requested solution: ");
	scanf("%d", &solution_num);

	queens(board, solution_num);
	return 0;
}






void queens(int board[][BOARD_SIZE], int solution_num)
{
	if (solution_num > 92 || solution_num < 1)	// 92 options
		print_board(board, 0, 0);	// print empty board

	else			// find the requested solution
		mark_queens(board, solution_num, 0);
}





int mark_queens(int board[][BOARD_SIZE], int solution_num, int col) 
{
	int row=0;

	if (col >= BOARD_SIZE)
	{	// We finished the table - solution found!
		if (solution_num < 2)	// it's the requested solution
			print_board(board, 0, 0);

		return (solution_num - 1);
	}
	
	if (solution_num <= 0)
		return solution_num;

	for (row = 0; row < BOARD_SIZE; row++)
	{	// For each column, find a cell to place a queen 
		if (check_place(board, row, col) == 1)
		{	// if the current cell is not threaten by any queen
			board[row][col] = QUEEN;	// mark the queen and GO
			solution_num = mark_queens(board, solution_num, col + 1);
			board[row][col] = NOT_QUEEN;
		}
	}

	return solution_num;
}

int check_place(int board[][BOARD_SIZE], int row, int col)
{
	int counter = 0, direction_row=0, direction_col=0;

	direction_row = 0;	// column front
	direction_col = 1;
	counter += check_direction(board, row + direction_row, col + direction_col, direction_row, direction_col);

	direction_row = 0;	// column back
	direction_col = -1;
	counter += check_direction(board, row + direction_row, col + direction_col, direction_row, direction_col);

	direction_row = 1;	// row down
	direction_col = 0;
	counter += check_direction(board, row + direction_row, col + direction_col, direction_row, direction_col);

	direction_row = -1;	// row up
	direction_col = 0;
	counter += check_direction(board, row + direction_row, col + direction_col, direction_row, direction_col);

	direction_row = 1;	// slope front down
	direction_col = 1;
	counter += check_direction(board, row + direction_row, col + direction_col, direction_row, direction_col);

	direction_row = 1;	// slope back down
	direction_col = -1;
	counter += check_direction(board, row + direction_row, col + direction_col, direction_row, direction_col);
	
	direction_row = -1;	// slope front up
	direction_col = 1;
	counter += check_direction(board, row + direction_row, col + direction_col, direction_row, direction_col);

	direction_row = -1;	// slope back up
	direction_col = -1;
	counter += check_direction(board, row + direction_row, col + direction_col, direction_row, direction_col);

	if (counter == 0)	// if all directions are not threaten
		return 1;
	
	return 0;		// at least one direction is threaten
}


int check_direction(int board[][BOARD_SIZE], int row, int col, int direction_row, int direction_col)
{
	if ((row < 0 || row >= BOARD_SIZE) || (col < 0 || col >= BOARD_SIZE))
		return 0;	// We get to the edge

	if (board[row][col] == QUEEN)
		return 1;	// We found a queen

	return check_direction(board, row + direction_row, col + direction_col, direction_row, direction_col);
}


void print_board(int board[][BOARD_SIZE], int row, int col)
{
	if (col >= BOARD_SIZE)
	{	// We finished to print the row
		printf("\n");
		col = 0;
		row++;
	}
	if (row >= BOARD_SIZE)
		return;		// We finish the board

	if (col > 0 && col < BOARD_SIZE)
		printf(" ");

	printf("%d", board[row][col]);

	print_board(board, row, col + 1);
}