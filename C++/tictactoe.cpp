#include <stdio.h>
#include <stdbool.h>
typedef struct move
{
    int row;
    int column;
}move;

void PrintBoard(char board[3][3]);
struct move FindBestMove(char computer, char opponent, char board[3][3]);
int MiniMax(char computer, char opponent, char board[3][3], int depth, bool IsMaximizer);
int ScoreGame(char computer, char opponent, char board[3][3]);
void PrintBoard(char board[3][3]);
char CheckEnd(char board[3][3]);
int CheckFreeSpace(char board[3][3]);
int max(int FirstValue, int SecondValue);
int min(int FirstValue, int SecondValue);

int main()
{
    // Create a board and number it 

    char board[3][3] = {{'-', '-', '-'},
                        {'-', '-', '-'},
                        {'-', '-', '-'}};
    
 
   
    // Print the board
    PrintBoard(board);
    printf("Hello, Welcome to Tic Tac Toe \n");
    // Ask the user if they want to go first or second
    // Return an error if they provide an unexpected answer
    char order='-';
    bool ExpectedInput = false, SpaceAvailable = false;
    char computer = '-';
    char opponent = '-';
    int RowInput = -1, ColumnInput = -1;
    printf("Would you like to be X or O? (enter X or O):  ");
    scanf("%c", &order);
 
    while (ExpectedInput == false)
    {
        if (order == 'X' || order == 'x')
        {
            ExpectedInput = true;
            computer = 'O';
            opponent = 'X';
            break;
        }
        if (order == 'O' || order == 'o')
        {
            ExpectedInput = true;
            computer = 'X';
            opponent = 'O';
            break;
        }
        else
        {
            printf("Please enter X or O: ");
            scanf("%c", &order);
        }
    }
    
    while(CheckFreeSpace>0)
    {
        
        SpaceAvailable=false;
        PrintBoard(board);
        while(SpaceAvailable==false)
        {
            ExpectedInput = false;
            while(ExpectedInput == false)
            {
                printf("Enter the Row of your move (1-3):  ");
                scanf("%d", &RowInput);
                printf("\n");
                RowInput--;
                if (RowInput==0 || RowInput==1 || RowInput==2)
                {             
                    ExpectedInput = true;
                }
            }
            ExpectedInput = false;
            while(ExpectedInput == false)
            {
                printf("Enter the column of your move (1-3):  ");
                scanf("%d", &ColumnInput);
                printf("\n");
                ColumnInput--;
                if (ColumnInput==0 || ColumnInput==1 || ColumnInput==2)
                {
                    ExpectedInput = true;
                } 
            }
            if(board[RowInput][ColumnInput]=='-')
            {
                SpaceAvailable = true;
            }
            else
            {
                printf("That spot is taken. \n");
            }
        }
        board[RowInput][ColumnInput] = opponent;
        if(CheckEnd(board)==opponent)
        {
            PrintBoard(board);
            printf("You have one the Game!!");
            break;
        }
        if(CheckFreeSpace(board)==0)
        {
            PrintBoard(board);
            printf("There are no more free spaces, the game is over.");
            break;
        }
        
        struct move BestMove = FindBestMove(computer, opponent, board);

        board[BestMove.row][BestMove.column] = computer;
        if(CheckEnd(board)==computer)
        {
            PrintBoard(board);
            printf("The Computer has won the Game :(");
            break;
        }
        if(CheckFreeSpace(board)==0)
        {
            PrintBoard(board);
            printf("There are no more free spaces, the game is over.");
            break;
        }
    }

     
    return 0;
}
struct move FindBestMove(char computer, char opponent, char board[3][3])
{
    int MaxValue = -1000;
    
    struct move BestMove;
    BestMove.row = 3;
    BestMove.column = 3;

    for(int r=0; r<3; r++)
    {
        for(int c=0; c<3; c++)
        {
            if(board[r][c]=='-')
            {
                board[r][c] = computer;

                int CurrentValue = MiniMax(computer, opponent, board, 0, false);

                board[r][c] = '-';

                if(CurrentValue > MaxValue)
                {
                    BestMove.row = r;
                    BestMove.column = c;
                    MaxValue = CurrentValue;
                }
            }
        }
    }

    return BestMove;
}
int MiniMax(char computer, char opponent, char board[3][3], int depth, bool IsMaximizer)
{
    
    // if the board is filled return the value of the board
    int score = ScoreGame(computer, opponent, board);
    if(score == 10) return score-depth;
    if(score == -10) return score+depth;
    if(CheckFreeSpace(board) == 0) return 0;
    // if the player is the maximizing player find the board state with the largest value and return that value
    if(IsMaximizer)
    {
        int BestValue = -1000;
        for(int r=0; r<3; r++)
        {
            for(int c=0; c<3; c++)
            {
                if(board[r][c]=='-')
                {
                    board[r][c] = computer;

                    BestValue = max(BestValue, MiniMax(computer, opponent, board, depth+1, !IsMaximizer));

                    board[r][c] = '-';
                }
            }
        }
        return BestValue;
    }
    // if the player is the minimizing player find the board state withe the smallest value and return that value
    else
    {
        int BestValue = 1000;
        for(int r=0; r<3; r++)
        {
            for(int c=0; c<3; c++)
            {
                if(board[r][c]=='-')
                {
                    board[r][c] = opponent;

                    BestValue = min(BestValue, MiniMax(computer, opponent, board, depth+1, !IsMaximizer));

                    board[r][c] = '-';
                }
            }
        }
        return BestValue;

    }
   
}
int ScoreGame(char computer, char opponent, char board[3][3])
{
    if(CheckEnd(board)==computer)
    {
        return 10;
    }
    if(CheckEnd(board)==opponent)
    {
        return -10;
    }
    else
    {
        return 0;
    }
}

void PrintBoard(char board[3][3])
{
    for (int r = 0; r <=2; r++)
    {
        for (int c = 0;c <=2; c++) printf(" %c ", board[r][c]);
        printf("\n");
    }
}
char CheckEnd(char board[3][3])
{
    int r = 0, c = 0;
    int X_repeat = 0, O_repeat = 0;
    // check each horizontal to see if 3 in a row
    for (r = 0; r <= 2; r++)
    {
        for (c = 0; c<=2; c++)
        {
            if (board[r][c] == 'X') X_repeat++;
            if (board[r][c] == 'O') O_repeat++;
        }
        if (X_repeat == 3) return 'X'; 
        if (O_repeat == 3) return 'O'; 
        X_repeat = 0;
        O_repeat = 0;
    }
    //check each vertical to see if player has 2
    for (c = 0; c <= 2; c++)
    {
        for (r = 0; r<=2; r++)
        {
            if (board[r][c] == 'X') X_repeat++;
            if (board[r][c] == 'O') O_repeat++;
        }
        if (X_repeat == 3) return 'X'; 
        if (O_repeat == 3) return 'O'; 
        X_repeat = 0;
        O_repeat = 0;
    }
     
    // check each diagonal to see if player has 2
    for (r = 0; r<=2; r++)
    {
        if (board[r][r] == 'X') X_repeat++;
        if (board[r][r] == 'O') O_repeat++;
    }
    if (X_repeat == 3) return 'X'; 
    if (O_repeat == 3) return 'O'; 
    X_repeat = 0;
    O_repeat = 0;
    c = 2;
    for (r = 0; r<=2; r++)
    {
        if (board[r][c] == 'X') X_repeat++;
        if (board[r][c] == 'O') O_repeat++;
        c--;
    }
    if (X_repeat == 3) return 'X'; 
    if (O_repeat == 3) return 'O'; 
    X_repeat = 0;
    O_repeat = 0;
         
    // if no win return n for no
    return 'N';

}

int CheckFreeSpace(char board[3][3])
{
    int r = 0, c = 0;
    int FreeSpace = 0;
    
    for (r = 0; r<=2; r++)
    {
        for (c=0;c<=2;c++)
        {
            if (board[r][c] == '-') FreeSpace++;
        }
    }
    return FreeSpace;    
}
// Create a function to return the maximum value between two integer values
int max(int FirstValue, int SecondValue)
{
    // if first paramater is greater than the second parameter then return the first parameter, 
    if(FirstValue > SecondValue)
    {
        return FirstValue;
    }
    // if the second paramter is greater than the first parameter return the second parameter. if both are equal you can return either but I chose the second to reduce lines of code
    else
    {
        return SecondValue;
    }
}
// create a function to return the minimum value, logic is opposite of the max function
int min(int FirstValue, int SecondValue)
{
    if(FirstValue < SecondValue)
    {
        return FirstValue;
    }
    else
    {
        return SecondValue;
    }
}
