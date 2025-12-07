#include <stdio.h>
#include <limits.h>

char board[3][3];

// void initializeBoard();
// void printBoard();
// int isMovesLeft();
// int evaluate();
// int minimax(int depth, int isMax);
// int findBestMove();
// void playerMove();
// void aiMove();
// int checkWin();
// void playGame();

void initializeBoard()  // for empty initialization
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
    int bestVal = INT_MIN, bestMove = -1;  //-2147483648  smallest integer
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

int main()
{
    printf("Tic-Tac-Toe!\n");
    printf("You are 'X', AI is 'O'. Enter row and column (0-2):\n");
    
    playGame();
    return 0;
}