/*
Author: Rishi Latchmepersad
Date: 24/03/2023

Description:
A basic console-based Tic Tac Toe game in C. Coded just to learn the basics.
Final project for 'C Programming Full Course' by Bro Code at https://www.youtube.com/watch?v=87SH2Cn0s9A
*/
// library includes
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

// global variables
char board[3][3];
const char PLAYER = 'X';
const char COMPUTER = 'O';

// function declarations
void resetBoard(char board[3][3]);
void printBoard();
int checkFreeSpaces();
void playerMove();
void computerMove();
char checkWinner();
void printWinner(char);

// main function to run code
int main()
{
    char response;
    char winner = ' ';
    do
    {
        printf("Welcome to Tic Tac Toe!\n");
        winner = ' ';
        response = ' ';
        // initialize the board
        resetBoard(board);
        // play the game
        while (winner == ' ' && checkFreeSpaces() > 0)
        {
            printBoard();
            playerMove();
            winner = checkWinner();
            if (winner == ' ')
            {
                computerMove();
                winner = checkWinner();
            }
        }
        // print the winner and the board
        printBoard();
        printWinner(winner);
        // ask the player if they want to play again
        printf("Play again? (y/n):");
        while ((response = getchar()) == '\n')
            ; // Clear the input buffer from the previous inputs (for rows and columns)
        response = tolower(response);
    } while (response != 'n');
    // end the program, since the player doesn't want to play anymore
    printf("Thanks for playing!\n");
    return 0;
}

// function definitions
void resetBoard(char board[3][3])
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            board[i][j] = ' ';
        }
    }
};
void printBoard()
{
    printf(" %c | %c | %c \n", board[0][0], board[0][1], board[0][2]);
    printf("---+---+---\n");
    printf(" %c | %c | %c \n", board[1][0], board[1][1], board[1][2]);
    printf("---+---+---\n");
    printf(" %c | %c | %c \n", board[2][0], board[2][1], board[2][2]);
    printf("\n");
};

int checkFreeSpaces()
{
    int freeSpaces = 9;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (board[i][j] != ' ')
            {
                freeSpaces--;
            }
        }
    }
    return freeSpaces;
};
void playerMove()
{
    int row, col;
    do
    {
        printf("Enter a row to place your move #(1-3): ");
        scanf("%d", &row);
        row--;
        printf("Enter a column to place your move #(1-3): ");
        scanf("%d", &col);
        col--;
        if (board[row][col] != ' ')
        {
            printf("Invalid move. Try again.\n");
            row = -1;
            col = -1;
        }
        else
        {
            board[row][col] = PLAYER;
            printf("You moved at row %d, column %d.\n", row + 1, col + 1);
            break;
        }

    } while (board[row][col] != ' ');
};

void computerMove()
{
    // create a seed based on current time
    srand(time(0));
    int row, col;
    // if there are free spaces
    if (checkFreeSpaces() > 0)
    {
        // generate a random row and column until we find an empty space
        do
        {
            row = rand() % 3; // generate a random number between 0 and 2
            col = rand() % 3;
        } while (board[row][col] != ' ');
        // then place the computer's move
        board[row][col] = COMPUTER;
        printf("Computer moved at row %d, column %d.\n", row + 1, col + 1);
    }
};

char checkWinner()
{
    char winner = ' ';
    // check each row and column for 3 matching elements along either axis
    for (int i = 0; i < 3; i++)
    {
        // if all elements in row are the same and the row is not empty
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] != ' ')
        {
            return board[i][0];
        }
        // else if all elements in column are the same and the column is not empty
        else if (board[0][i] == board[1][i] && board[1][i] == board[2][i] && board[0][i] != ' ')
        {
            return board[0][i];
        }
    }
    // check if all elements of the main diagonal are the same and the main diagonal is not empty
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != ' ')
    {
        return board[0][0];
    }
    // else if all elements of the off-diagonal are the same and the off-diagonal is not empty
    else if (board[2][0] == board[1][1] && board[1][1] == board[0][2] && board[2][0] != ' ')
    {
        return board[2][0];
    }
    // else if there are no more free spaces, and no winners, then it is a tie
    else if (checkFreeSpaces() == 0)
    {
        return 'T';
    }
    // else there is no winner yet
    else
    {
        return ' ';
    }
};

void printWinner(char winner)
{
    if (winner == PLAYER)
    {
        printf("You win!\n");
    }
    else if (winner == COMPUTER)
    {
        printf("Computer wins!\n");
    }
    else
    {
        printf("It's a tie!\n");
    }
};