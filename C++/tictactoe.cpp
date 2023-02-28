#include <iostream>
#include <stdbool.h>
void print_board(char board[][3]);

int main()
{
    // Create a board and number it 
    char board[3][3];
    board[0][0] = '1';
    board[0][1] = '2';
    board[0][2] = '3';
    board[1][0] = '4';
    board[1][1] = '5';
    board[1][2] = '6';
    board[2][0] = '7';
    board[2][1] = '8';
    board[2][2] = '9';
    // Print the board
    print_board(board);
    std::cout << "Hello, Welcome to Tic Tac Toe" << std::endl;
    // Ask the user if they want to go first or second
    // Return an error if they provide an unexpected answer
    char order[8];
    bool expectedinput = false;
    char computer;
    char opponent;
    std::cout << "Would you like to be X or O?: ";
    std::cin >> order;
    std::cout << std::endl;
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
            std::cout << "Would you like to be X or O?: ";
            std::cin >> order;
            std::cout << std::endl;
        }
    }
    /*
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
    */
     
    return 0;
}

void print_board(char board[][3])
{
    int r = 0, c = 0;
    for (r = 0; r <=2; r++)
    {
        for (c = 0;c <=2; c++) std::cout << " " << board[r][c] << " ";
        std::cout << std::endl;
    }
}

char check_end(char board[][3])
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
int *check_win(char board[][3], char player)
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
            if (board[r][c] != player && board[r][r] != opponent)
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

int check_free_space(char board[][3])
{
    int r = 0, c = 0;
    int free_space = 0;
    
    for (r = 0; r<=2; r++)
    {
        for (c=0;c<=2;c++)
        {
            if (board[r][c] != 'X' || board[r][c] != 'O') free_space++;
        }
    }
    return free_space;    
}
