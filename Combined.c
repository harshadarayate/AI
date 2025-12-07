#include <stdio.h>
#include <limits.h>

char board[3][3];

void initializeBoard() // for empty initialization
{
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            board[i][j] = ' ';
}

void printBoard()
{
    printf("\n");
    for (int i = 0; i < 3; i++)
    {
        printf(" %c | %c | %c \n", board[i][0], board[i][1], board[i][2]);
        if (i < 3 - 1)
            printf("---+---+---\n");
    }
    printf("\n");
}

int isMovesLeft()
{
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (board[i][j] == ' ')
                return 1;
    return 0;
}

int evaluate()
{
    // for checking rows
    for (int i = 0; i < 3; i++)
    {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2])
        {
            if (board[i][0] == 'O')
                return 10;
            else if (board[i][0] == 'X')
                return -10;
        }
    }
    // for columns
    for (int j = 0; j < 3; j++)
    {
        if (board[0][j] == board[1][j] && board[1][j] == board[2][j])
        {
            if (board[0][j] == 'O')
                return 10;
            else if (board[0][j] == 'X')
                return -10;
        }
    }
    // for diagonals
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2])
    {
        if (board[0][0] == 'O')
            return 10;
        else if (board[0][0] == 'X')
            return -10;
    }
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0])
    {
        if (board[0][2] == 'O')
            return 10;
        else if (board[0][2] == 'X')
            return -10;
    }
    return 0;
}

int minimax(int depth, int isMax)
{
    int score = evaluate();
    if (score == 10)
        return score - depth;
    if (score == -10)
        return score + depth;
    if (!isMovesLeft())
        return 0;
    if (isMax)
    {
        int best = INT_MIN;
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (board[i][j] == ' ')
                {
                    board[i][j] = 'O';
                    best = (best > minimax(depth + 1, 0)) ? best : minimax(depth + 1, 0);
                    board[i][j] = ' ';
                }
            }
        }
        return best;
    }
    else
    {
        int best = INT_MAX; //max=2147483647
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (board[i][j] == ' ')
                {
                    board[i][j] = 'X';
                    best = (best < minimax(depth + 1, 1)) ? best : minimax(depth + 1, 1);
                    board[i][j] = ' ';
                }
            }
        }
        return best;
    }
}

//for ai best move
int findBestMove()
{
    int bestVal = INT_MIN, bestMove = -1; //-2147483648 smallest integer
    int moveIndex = 0;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (board[i][j] == ' ')
            {
                board[i][j] = 'O';
                int moveVal = minimax(0, 0);
                board[i][j] = ' ';
                if (moveVal > bestVal)
                {
                    bestMove = moveIndex;
                    bestVal = moveVal;
                }
            }
            moveIndex++;
        }
    }
    return bestMove;
}

void playerMove() //for player move
{
    int row, col;
    printf("Enter row and column (0-2): ");
    scanf("%d%d", &row, &col);
    while (row < 0 || row > 2 || col < 0 || col > 2)
    {
        printf("Invalid! Enter between 0 and 2: ");
        scanf("%d%d", &row, &col);
    }
    while (board[row][col] != ' ')
    {
        printf("Cell taken! Enter another: ");
        scanf("%d%d", &row, &col);
        while (row < 0 || row > 2 || col < 0 || col > 2)
        {
            printf("Invalid! Enter between 0 and 2: ");
            scanf("%d%d", &row, &col);
        }
    }
    board[row][col] = 'X';
}

void aiMove()
{
    int move = findBestMove();
    int row = move / 3;
    int col = move % 3;
    board[row][col] = 'O';
    printf("AI placed 'O' at row %d, col %d\n", row, col);
}

int checkWin()
{
    int score = evaluate();
    if (score == 10)
    {
        printf("AI wins!\n");
        return 1;
    }
    else if (score == -10)
    {
        printf("You win!\n");
        return 1;
    }
    else if (!isMovesLeft())
    {
        printf("It's a tie!\n");
        return 1;
    }
    return 0;
}

void playGame()
{
    initializeBoard();
    printBoard();
    while (1)
    {
        playerMove();
        printBoard();
        if (checkWin())
            break;
        aiMove();
        printBoard();
        if (checkWin())
            break;
    }
}

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

void twoPlayerGame()
{
    int iRow, iColumn;
    int iTotalMoves = 0;
    int iTurn = 1; // 1 for Player 1 (O), 2 for Player 2 (X)
    char iWinner = ' ';
    // Initialize the board with empty spaces
    initializeBoard();
    printf("Welcome to Tic-Tac-Toe! Player 1 is 'O', Player 2 is 'X'.\n");
    printf("Enter iRow and iColumn (0-2) for your move.\n");
    while (iTotalMoves < 9)
    {
        // Display the board
        DisplayMatrix(board);
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
        if (board[iRow][iColumn] != ' ')
        {
            printf("Cell already filled! Choose an empty position.\n");
            continue;
        }
        // Place the player's mark
        if (iTurn == 1)
        {
            board[iRow][iColumn] = 'O';
            iTurn = 2;
        }
        else
        {
            board[iRow][iColumn] = 'X';
            iTurn = 1;
        }
        iTotalMoves++;
        // Check for a iWinner
        iWinner = CheckiWinner(board);
       
        if (iWinner == 'O')
        {
            DisplayMatrix(board);
            printf("Player 1 Wins!\n");
            break;
        }
        else if (iWinner == 'X')
        {
            DisplayMatrix(board);
            printf("Player 2 Wins!\n");
            break;
        }
        else if (iTotalMoves == 9)
        {
            DisplayMatrix(board);
            printf("It's a Tie!\n");
            break;
        }
    }
}

int main()
{
    int choice;
    printf("Choose game mode:\n");
    printf("1. Play against AI (You as 'X', AI as 'O')\n");
    printf("2. Two-player mode (Player 1 'O', Player 2 'X')\n");
    printf("Enter your choice (1 or 2): ");
    scanf("%d", &choice);
    switch (choice)
    {
        case 1:
            printf("Tic-Tac-Toe!\n");
            printf("You are 'X', AI is 'O'. Enter row and column (0-2):\n");
            playGame();
            break;
        case 2:
            twoPlayerGame();
            break;
        default:
            printf("Invalid choice! Please run the program again.\n");
            break;
    }
    return 0;
}