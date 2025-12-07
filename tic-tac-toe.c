#include <stdio.h>

// Display the Tic-Tac-Toe board
void DisplayMatrix(char iMatrix[3][3])
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            printf("%c\t", iMatrix[i][j]);
        }
        printf("\n");
    }
}

// Check for a iWinner by examining iRows, iColumns, and diagonals
char CheckiWinner(char iMatrix[3][3])
{
    // Check iRows
    for (int i = 0; i < 3; i++)
    {
        if (iMatrix[i][0] == iMatrix[i][1] && iMatrix[i][1] == iMatrix[i][2] && iMatrix[i][0] != ' ')
        {
            return iMatrix[i][0];
        }
    }
    // Check iColumns
    for (int i = 0; i < 3; i++)
    {
        if (iMatrix[0][i] == iMatrix[1][i] && iMatrix[1][i] == iMatrix[2][i] && iMatrix[0][i] != ' ')
        {
            return iMatrix[0][i];
        }
    }
    // Check diagonals
    if (iMatrix[0][0] == iMatrix[1][1] && iMatrix[1][1] == iMatrix[2][2] && iMatrix[0][0] != ' ')
    {
        return iMatrix[0][0];
    }
    if (iMatrix[0][2] == iMatrix[1][1] && iMatrix[1][1] == iMatrix[2][0] && iMatrix[0][2] != ' ')
    {
        return iMatrix[0][2];
    }
    return ' '; // No iWinner
}

int main()
{
    char iMatrix[3][3];
    int iRow, iColumn;
    int iTotalMoves = 0;
    int iTurn = 1; // 1 for Player 1 (O), 2 for Player 2 (X)
    char iWinner = ' ';

    // Initialize the board with empty spaces
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            iMatrix[i][j] = ' ';
        }
    }

    printf("Welcome to Tic-Tac-Toe! Player 1 is 'O', Player 2 is 'X'.\n");
    printf("Enter iRow and iColumn (0-2) for your move.\n");

    while (iTotalMoves < 9)
    {
        // Display the board
        DisplayMatrix(iMatrix);

        // Prompt for player's turn
        if (iTurn == 1)
        {
            printf("Player 1's Turn (O). Enter iRow and iColumn (0-2): ");
        }
        else
        {
            printf("Player 2's Turn (X). Enter iRow and iColumn (0-2): ");
        }

        // Get and validate input
        scanf("%d%d", &iRow, &iColumn);
        if (iRow < 0 || iRow > 2 || iColumn < 0 || iColumn > 2)
        {
            printf("Invalid input! iRow and iColumn must be between 0 and 2.\n");
            continue;
        }
        if (iMatrix[iRow][iColumn] != ' ')
        {
            printf("Cell already filled! Choose an empty position.\n");
            continue;
        }

        // Place the player's mark
        if (iTurn == 1)
        {
            iMatrix[iRow][iColumn] = 'O';
            iTurn = 2;
        }
        else
        {
            iMatrix[iRow][iColumn] = 'X';
            iTurn = 1;
        }

        iTotalMoves++;

        // Check for a iWinner
        iWinner = CheckiWinner(iMatrix);
        
        if (iWinner == 'O')
        {
            DisplayMatrix(iMatrix);
            printf("Player 1 Wins!\n");
            break;
        }
        else if (iWinner == 'X')
        {
            DisplayMatrix(iMatrix);
            printf("Player 2 Wins!\n");
            break;
        }
        else if (iTotalMoves == 9)
        {
            DisplayMatrix(iMatrix);
            printf("It's a Tie!\n");
            break;
        }
    }

    return 0;
}