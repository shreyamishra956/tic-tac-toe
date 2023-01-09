#include <bits/stdc++.h>
using namespace std;


static char comp_symbol = 'O';
static char user_symbol = 'X';
static int comp = 1;
static int user = 2;


void show_position()
{
    cout << endl << "choose any position from 1 to 9 to start the game : " << endl << endl;
    cout << "\t\t\t" << "1 | 2 | 3" << endl;
    cout << "\t\t\t" << "4 | 5 | 6" << endl;
    cout << "\t\t\t" << "7 | 8 | 9" << endl;
}



void showBoard(vector<vector<char>> board)
{
    cout << "\t\t\t" << board[0][0] << " | " << board[0][1] << " | " << board[0][2] << endl;
    cout << "\t\t\t" << board[1][0] << " | " << board[1][1] << " | " << board[1][2] << endl;
    cout << "\t\t\t" << board[2][0] << " | " << board[2][1] << " | " << board[2][2] << endl;
}



void decision(int turn)
{
    if (turn == comp)
        cout << "You loose :(" << endl;
    else
        cout << "You won :)"  << endl;
}



bool rowCrossed(vector<vector<char>> board)
{
    for (int i = 0; i < 3; i++)
    {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] != '*')
            return true;
    }
    return false;
}



bool columnCrossed(vector<vector<char>> board)
{
    for (int i = 0; i < 3; i++)
    {
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i] && board[0][i] != '*')
            return true;
    }
    return false;
}



bool diagonalCrossed(vector<vector<char>> board)
{
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != '*')
        return true;
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] != '*')
        return true;
    return false;
}



bool game_over(vector<vector<char>> board)
{
    return (rowCrossed(board) || columnCrossed(board) || diagonalCrossed(board));
}



int min_max_algo(vector<vector<char>> board, int depth, bool isAI)
{
    int score = 0;
    int bestScore = 0;
    if (game_over(board) == true)
    {
        if (isAI == true)
            return -10;
        if (isAI == false)
            return +10;
    }
    else
    {
        if (depth < 9)
        {
            if (isAI == true)
            {
                bestScore = -999;
                for (int i = 0; i < 3; i++)
                {
                    for (int j = 0; j < 3; j++)
                    {
                        if (board[i][j] == '*')
                        {
                            board[i][j] = comp_symbol;
                            score = min_max_algo(board, depth + 1, false);
                            board[i][j] = '*';
                            if (score > bestScore)
                            {
                                bestScore = score;
                            }
                        }
                    }
                }
                return bestScore;
            }
            else
            {
                bestScore = 999;
                for (int i = 0; i < 3; i++)
                {
                    for (int j = 0; j < 3; j++)
                    {
                        if (board[i][j] == '*')
                        {
                            board[i][j] = user_symbol;
                            score = min_max_algo(board, depth + 1, true);
                            board[i][j] = '*';
                            if (score < bestScore)
                            {
                                bestScore = score;
                            }
                        }
                    }
                }
                return bestScore;
            }
        }
        else
        {
            return 0;
        }
    }
}



int move(vector<vector<char>> board, int indexFilled)
{
    int x = -1, y = -1;
    int score = 0, bestScore = -999;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (board[i][j] == '*')
            {
                board[i][j] = comp_symbol;
                score = min_max_algo(board, indexFilled + 1, false);
                board[i][j] = '*';
                if (score > bestScore)
                {
                    bestScore = score;
                    x = i;
                    y = j;
                }
            }
        }
    }
    return x * 3 + y;
}


// A function to play Tic-Tac-Toe


void play(int turn)
{    
    vector<vector<char>> board(3, vector<char> (3, '*'));
    int indexFilled = 0, x = 0, y = 0;
    show_position();

    while (game_over(board) == false && indexFilled != 3 * 3)
    {
        int n;
        if (turn == comp)
        {
            n = move(board, indexFilled);
            x = n / 3;
            y = n % 3;
            board[x][y] = comp_symbol;
            cout << "Computer has put a " << comp_symbol << " in cell " << n+1 << endl << endl;
            showBoard(board);
            indexFilled++;
            turn = user;
        }

        else if (turn == user)
        {
            cout << "You can insert in the following positions : ";


            for (int i = 0; i < 3; i++)
                for (int j = 0; j < 3; j++)
                    if (board[i][j] == '*')
                        cout << (i * 3 + j) + 1 << " ";

            cout << endl << endl << "Enter the position = ";
            cin >> n;
            n--;

            x = n / 3;
            y = n % 3;

            if (board[x][y] == '*' && n < 9 && n >= 0)
            {
                board[x][y] = user_symbol;
                cout << endl << "User has put a " << user_symbol << " in cell " << n + 1 << endl << endl;
                showBoard(board);
                indexFilled++;
                turn = comp;
            }

            else if (board[x][y] != '*' && n < 9 && n >= 0)
            {
                cout << endl << "Position is occupied. Select any one place from the available places." << endl << endl;
            }

            else if (n < 0 || n > 8)
            {
                cout << "Invalid position" << endl;
            }
        }
    }
    if (game_over(board) == false && indexFilled == 3 * 3)
        cout << "It's a draw" << endl;
    else
    {
        if (turn == comp)
             turn = user;
        else if (turn == user)
            turn = comp;
        decision(turn);
    }
}


int main()
{
    cout << endl << "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx" << endl << endl;
    cout << "\t\t\t Tic-Tac-Toe Game" << endl;
    cout << endl << "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx" << endl << endl;



    char choose = 'y';
    do
    {
        char choice;
        cout << "Would you wish to start first? press(y/n) : ";
        cin >> choice;
        int count = 5;
        if (choice == 'n')
            play(comp);
        
        else if (choice == 'y')
        {
            tag:;
            cout << "Which character would you like to choose? (X/O) : ";
            char symbol;
            cin >> symbol;

            if(symbol == 'X' || symbol == 'O')
            {
                if(symbol == 'O')
                {
                    user_symbol = symbol;
                    comp_symbol = 'X';
                }
                play(user);
            }
            else
            {
                cout << "Invalid character pressed. \n";
                count--;
                cout << "Remaing chances- " << count << endl;
                if(count > 0)
                    goto tag;
                else
                {
                    cout << "Maximum number of choosing invalid character limit reached. \n Program Terminated\n";
                    return 0;
                }
            }
        }
        else
            cout << "Invalid key pressed" << endl;
        cout << endl << "Restart? Press(y/n) : ";
        cin >> choose;
    } while (choose == 'y');
}