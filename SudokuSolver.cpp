#include <iostream>
#include <string>
#include <utility>
#include <cmath>
using namespace std;

//Prints puzzle, [9][9] is the size of the puzzle board which has 9 rows and 9 columns
void print(int puzzle[9][9])
{
    for(int i = 0; i < 9; i++)
    {
        for(int j = 0; j < 9; j++)
        {
            cout << puzzle[i][j] << " ";
        }
        cout << "\n";
    }
}

//Returns index of empty square as a pair
pair<int, int> findEmpty(int puzzle[9][9])
{
    for(int i = 0; i < 9; i++)
        for(int j = 0; j < 9; j++)
        {
            if(puzzle[i][j] == 0)
            {
                return make_pair(i, j);
            }

        }
    
    //If there are no empty squares left
    return make_pair(-1, -1);
}

//Returns true if guess value (num) works for the space in given row and column
bool isValid(int puzzle[9][9], int row, int col, int num)
{
    //If num already exists in the row, the value is invalid
    for(int c = 0; c < 9; c++)
    {
        if(puzzle[row][c] == num)
            return false;
    }
    //If num already exists in the column, the value is invalid
    for(int r = 0; r < 9; r++)
    {
        if(puzzle[r][col] == num)
            return false;
    }
    //If num already exists in the 3x3 matrix, the value is invalid 
    //Find starting row and starting column indices
    int row_start_index = floor(row / 3) * 3;
    int col_start_index = floor(col / 3) * 3;
    //Iterate through 3x3 matrix to check for guess value
    for(int r = row_start_index; r < row_start_index + 3; r++)
        for(int c = col_start_index; c < col_start_index + 3; c++)
        {
            if(puzzle[r][c] == num)
                return false;
        }
    
    //If guess value does not exist in row, column, or the 3x3 square, then this guess is valid
    return true;
}

//Returns true if puzzle is solvable, false if unsolvable 
bool solve(int puzzle[9][9])
{
    int row = findEmpty(puzzle).first;
    int col = findEmpty(puzzle).second;

    //If no spaces remain, the puzzle has been solved
    if(row == -1)
        return true;

    //Input test value to an empty square between 1-9
    //val is the guess value to be tested
    for(int val = 1; val < 10; val++)
    {
        if(isValid(puzzle, row, col, val))
        {
            //Assign this value to the space since it is valid
            puzzle[row][col] = val;

            //Recursively call function
            if(solve(puzzle))
                return true; //this value works for the puzzle!
        
            //If guess value does not work, try another value (backtrack)
            puzzle[row][col] = 0; //Reset to 0 or empty square
        }
    }
    //If no values work, this puzzle cannot be solved
    return false;
}

int main()
{
    int board[9][9] = { {0, 0, 0, 0, 0, 0, 0, 7, 9},
                        {8, 0, 5, 0, 7, 4, 1, 0, 0},
                        {4, 6, 0, 1, 0, 0, 0, 3, 8},
                        {0, 0, 0, 6, 5, 0, 9, 1, 0},
                        {0, 0, 6, 9, 1, 7, 0, 0, 4},
                        {0, 1, 9, 4, 3, 2, 0, 8, 7},
                        {0, 0, 8, 2, 0, 6, 0, 4, 0},
                        {6, 0, 2, 0, 0, 0, 0, 9, 1},
                        {0, 0, 0, 5, 0, 0, 0, 0, 6} };
    
    //If this puzzle is solvable, print the completed board with correct values filled in
    if(solve(board) == true)
        print(board);
    else
        cout << "This puzzle is unsolvable." << endl;
    
    return 0;
}
