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

/* 
int *CheckWin(GameBoard TicBoard, char player)
{
    
    int r = 0, c = 0;
    int repeat = 0;
    int position[2] = {3,3};
    // create a variable that stores the marker opposite that of the inputed player's
    char opponent;
    if (player == 'X') opponent = 'O';
    if (player == 'O') opponent = 'X';
    // check the each horizontal to see if player has 2 
    for (r = 0; r <= 2; r++)
    {
        for (c = 0; c<=2; c++)
        {
            if (board[r][c] == player) repeat++;
        }
        if (repeat == 2)
        {
            for (c = 0; c<=2; c++)
            {
                if (board[r][c] != player && board[r][c] != opponent)
                {
                    position[0] = r;
                    position[1] = c;
                    return position;
                }
            }         
        }
        repeat = 0;
    }
    //check each vertical to see if player has 2
    for (c = 0; c <= 2; c++)
    {
        for (r = 0; r<=2; r++)
        {
            if (board[r][c] == player) repeat++;
        }
        if (repeat == 2)
        {
            for (r= 0; r<=2; r++)
            {
                if (board[r][c] != player && board[r][c] != opponent)
                {
                    position[0] = r;
                    position[1] = c;
                    return position;
                }
            }         
        }
        repeat = 0;
    }
    
    // check each diagonal to see if player has 2
    for (r = 0; r<=2; r++)
    {
        if (board[r][r] == player) repeat++;
    }
    if (repeat == 2)
    {
        for (r = 0; r<=2; r++)
        {
            if (board[r][r] != player && board[r][r] != opponent)
            {
                position[0] = r;
                position[1] = r;
                return position;
            }
        }         
    }
    repeat = 0;
    c = 2;
    for (r = 0; r<=2; r++)
    {
        if (board[r][c] == player) repeat++;
        c--;
    }
    if (repeat == 2)
    {
        c =2;
        for (r = 0; r<=2; r++)
        {
            if (TicBoard.board[r][c] != player && TicBoard.board[r][r] != opponent)
            {
                position[0] = r;
                position[1] = c;
                return position;
            }
            c--;
        }         
    }
    repeat = 0;
         
    // if no potentional win is found return impossible position
    return position;
}


int *check_fork(char board[][3], char player)
{
    int r = 0, c = 0, i = 0, j=0;
    int repeat = 0;
    int position[2] = {3,3};
    char save_space;
    // create a variable that stores the marker opposite that of the inputed player's
    char opponent;
    if (player == 'X') opponent = 'O';
    if (player == 'O') opponent = 'X';
    
    //check to see if its the first or second turn, if it is return a no result.
    if (check_free_space <= 4) return position;

    // create a test board to try out different combinations to find a fork
    char test_board[3][3];
    
    for (r = 0; r <= 2; r++)
    {
        for (c = 0; c<=2; c++)
        {
            test_board[r][c] = board[r][c];
        }
    }
    
    // Populate all the empty spaces
    for (r=0; r<=2; r++)
    {
        for(c=0; c<=2; c++)
        {
            if (test_board[r][c] != 'X' && test_board[r][c] != 'O')
            {
                test_board[r][c] = player;
            }
        }
    }
    // check if multiple wins

    int repeat = 0,h_win = 0, v_win = 0, d_win =0;
    // check each horizontal to see if 3 in a row
    for (r = 0; r <= 2; r++)
    {
        for (c = 0; c<=2; c++)
        {
            if (test_board[r][c] == player) repeat++;
        }
        
        // if there is a 3 check for a second one
        if (repeat == 3)
        {
            repeat = 0;
            // check veritcals
            for (j=0; j<= 2;j++)
            {
                for (i=0;i<=2;i++)
                {
                    if (test_board[i][j] == player) repeat++;
                }
                // if a the second 3 in a row is a vertical return the point of intersection
                if (repeat == 3) return {r,j};
                repeat = 0;
            }
            // Check diagonals
            if (r == 0 || r ==2)
            {
                // check first diagonal
                for (i = 0; i<=2; i++)
                {
                    if (board[i][i] == player) repeat++;
                }
                // if yes return intersection
                if (repeat == 3) return {r,r}; 
                repeat = 0;
                // check second diagonal
                j = 2;
                for (i= 0; i<=2; i++)
                {
                    if (board[i][j] == player) repeat++;
                    j--;
                }
                //if yes return intersection
                if (repeat == 3 && r== 0) return {r,r+2};
                if (repeat == 3 && r==2) return {r,r-2};
                repeat = 0;   
            }
        }
        repeat = 0;
    }
    //check each vertical to see if player has 3 in a row
    for (c = 0; c <= 2; c++)
    {
        for (r = 0; r<=2; r++)
        {
            if (board[r][c] == player) repeat++;
        }
        if (repeat == 3)
        {
            repeat = 0;
            for (i=0; i<= 2;i++)
            {
                for (j=0;j<=2;j++)
                {
                    if (test_board[i][j] == player) repeat++;
                }
                if (repeat == 3) return {i,c};
                repeat = 0;
            }
            if (c == 0 || c ==2)
            {
                for (i = 0; i<=2; i++)
                {
                    if (board[i][i] == player) repeat++;
                }
                if (repeat == 3) return {c,c}; 
                repeat = 0;
                j = 2;
                for (i= 0; i<=2; i++)
                {
                    if (board[i][j] == player) repeat++;
                    j--;
                }
                if (repeat == 3 && c== 0) return {c+2,c};
                if (repeat == 3 && c==2) return {c-2,c};
                repeat = 0;   
            }
        }
        repeat = 0;
    }
    return position;
}
int check_block_fork(char board[][3], char player)
{
    // create a variable that stores the marker opposite that of the inputed player's
    char opponent;
    if (player == 'X') opponent = 'O';
    if (player == 'O') opponent = 'X';
    int *position;

    position = check_fork(board, opponent);

    return position;

}
int check_center(char board[][3], char player)
{



}
int check_op_corner(char board[][3], char player)
{



}
int check_empty_corner(char board[][3], char player)
{



}
int check_empty_side(char board[][3], char player)
{



}
int MiniMax(char computer, char opponent, GameBoard TicBoard, int depth, bool IsMaximizer)
{
    
    
    // if the board is filled return the value of the board
    int score = ScoreGame(computer, opponent, TicBoard);
    if(score == 10) return score;
    if(score == -10) return score;
    if(CheckFreeSpace == 0) return 0;
    // if the player is the maximizing player find the board state with the largest value and return that value
    if(IsMaximizer)
    {
        int BestValue = -1000;
        for(int r=0; r<3; r++)
        {
            for(int c=0; c<3; c++)
            {
                if(TicBoard.board[r][c]=='-')
                {
                    TicBoard.board[r][c] = computer;char computer, char opponent, GameBoard TicBoard

                    BestValue = max(BestValue, MiniMax(computer, opponent, TicBoard, depth+1, !IsMaximizer));

                    TicBoard.board[r][c] = '-';
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
                if(TicBoard.board[r][c]=='-')
                {
                    TicBoard.board[r][c] = opponent;

                    BestValue = max(BestValue, MiniMax(computer, opponent, TicBoard, depth+1, !IsMaximizer));

                    TicBoard.board[r][c] = '-';
                }
            }
        }
        return BestValue;

    }
   
    
    
    
    
    
    
    
    
    //int move[2] = {3, 3};
    
    // Create a test board which is a copy of the original board to trial and error different moves
    GameBoard TestBoard;
    TestBoard = CopyBoard(TicBoard);
    
    if(CheckEnd(TicBoard)== 'O' || CheckEnd 'X')
    {
        return value;
    }
    // Check the number of free spaces
    int FreeSpace = 0;
    FreeSpace = CheckFreeSpace(TicBoard);

    // get an array of all possible free moves
    IntArray AvailableMoves;
    AvailableMoves = CheckAvailable(TicBoard);

    // Create a computer token and oppenent token to innumerate strongest possible moves
    int ComputerToken[FreeSpace], OpponentToken[FreeSpace];
    for(int i=0; i<FreeSpace; i++)
    {
        ComputerToken[i]=0;
        OpponentToken[i]=0;
    }

    if()
    // Trial and error all possible moves
    for(int r=0; r<=FreeSpace; r=r+2)
    {
        
        if(CheckEnd(TestBoard) == computer)
        {
            ComputerToken[r] = 10;
            OpponentToken[r] = 0;
        }
        

    }

    
}
int *CheckAvailable(GameBoard TicBoard)
{
    // Check how many Free spaces there are left on the board and use the number of free spaces to set number of rows of the available moves array
    int FreeSpace = 0;
    FreeSpace = CheckFreeSpace(board);

    // Create a 2D array whos were each row of the arraw lists the position of the free space
    int AvailableMoves[FreeSpace][2];
    
    
    int ArrayRow=0;
    // Check where the free spaces are and store their location in the 2D array
    for(int r=0; r<=2; r++)
    {
        for(int c=0; c<=2; c++)
        {   
            // Logical check for free space meaning any space that does not contain either an x or o
            if(board[r][c] != 'X' && board[r][c] != 'O')
            {
                // fail safe to check that the number of free spaces matches the checkfreespace function return value
                if(ArrayRow < Freespace)
                {
                    AvailableMoves[ArrayRow][0] = r;
                    AvailableMoves[ArrayRow][1] = c;
                    ArrayRow++;
                }
                else
                {
                    return NULL;
                }
            }
        }
    }
    return AvailableMoves;
}
struct GameBoard CopyBoard(GameBoard TicBoard)
{
    GameBoard TestBoard;

    TestBoard.rows = TicBoard.rows;
    TestBoard.columns = TicBoard.columns;

    for(int r=0; r<3; r++)
    {
        for(int c=0; c<3; c++)
        {
            TestBoard.board[r][c] = TicBoard.board[r][c];
        }
    }

    return TestBoard;
}
int main()
{
    // Create a board and number it 

    char board[3][3] = {{'-', '-', '-'},
                        {'-', '-', '-'},
                        {'-', '-', '-'}};
    
    
    GameBoard TicBoard;
    for(int r=0; r<3; r++)
    {
        for(int c=0; c<3; c++)
        {
            TicBoard.board[r][c] = '-';
        }
    }
    
   
    // Print the board
    PrintBoard(board);
    printf("Hello, Welcome to Tic Tac Toe \n");
    // Ask the user if they want to go first or second
    // Return an error if they provide an unexpected answer
    char order;
    bool expectedinput = false;
    char computer;
    char opponent;
    printf("Would you like to be X or O?: ");
    scanf("%s", order);
    while (expectedinput == false)
    {
        if (order == "X" || order == "x")
        {
            expectedinput = true;
            computer = 'O';
            opponent = 'X';
            break;
        }
        if (order == "O" || order == "o")
        {
            expectedinput = true;
            computer = 'X';
            opponent = 'O';
            break;
        }
        else
        {
            printf("Please enter X or O: ");
            scanf("%s", order);
        }
    }
    
    Computer shall make moves in order of priority:
    1. Win: If the player has two in a row, they can place a third to get three in a row.
    2. Block: If the opponent has two in a row, the player must play the third themselves to block the opponent. 
       Note: Block algorithm is the same as the win algorithm just for the opponent
    3. Fork: Create an opportunity where the player has two ways to win (two non-blocked lines of 2).
    4. Blocking an opponent's fork: If there is only one possible fork for the opponent, the player should block it. 
       Otherwise, the player should block all forks in any way that simultaneously allows them to create two in a row. 
       Otherwise, the player should create a two in a row to force the opponent into defending, as long as it doesn't result in them creating a fork. 
       For example, if "X" has two opposite corners and "O" has the center, "O" must not play a corner move in order to win. 
       (Playing a corner move in this scenario creates a fork for "X" to win.)
    5. Center: A player marks the center.
    6. Opposite corner: If the opponent is in the corner, the player plays the opposite corner.
    7. Empty corner: The player plays in a corner square.
    8. Empty side: The player plays in a middle square on any of the 4 sides.
    
     
    return 0;
}
*/

