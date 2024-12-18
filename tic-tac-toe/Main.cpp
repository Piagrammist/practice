#include <cstdlib>
#include <iostream>
#include <limits>

using std::cin;
using std::cout;
using std::endl;

void clear();
bool hasWinner(const int board[3][3]);
void printBoard(const int board[3][3]);
void getInput(const char turn, int &number);

int main()
{
    int board[3][3] = {
        { 0, 0, 0 },
        { 0, 0, 0 },
        { 0, 0, 0 },
    };

    char turn;
    int x, y, cell;
    bool draw = true;
    for (int i = 0; i < 9; ++i) {
        turn = i % 2 == 0 ? 'O' : 'X';
        printBoard(board);
        [&]() {
            while (true) {
                getInput(turn, cell);
                cell -= 1;
                x     = cell / 3;
                y     = cell % 3;
                if (board[x][y] == 0) {
                    /* O = 1, X = 2 */
                    board[x][y] = i % 2 + 1;
                    return; //== continue 2;
                }
                cout << "\tCell is full!" << endl;
            }
        }();
        if (hasWinner(board)) {
            draw = false;
            break;
        }
    }
    printBoard(board);
    if (draw)
        cout << "Draw!" << endl;
    else
        cout << "Winner is: " << turn << endl;
}

void clear()
{
#if defined(WIN32) || defined(_WIN32) || \
  defined(__WIN32) && !defined(__CYGWIN__)
    std::system("cls");
#else
    std::system("clear");
#endif
}

bool hasWinner(const int board[3][3])
{
    // Horizontal
    for (int i = 0; i < 3; ++i) {
        if (board[i][0] == 0)
            continue;
        if (board[i][0] == board[i][1] && board[i][0] == board[i][2])
            return true;
    }
    // Vertical
    for (int j = 0; j < 3; ++j) {
        if (board[0][j] == 0)
            continue;
        if (board[0][j] == board[1][j] && board[0][j] == board[2][j])
            return true;
    }
    // Diagonal
    if (board[1][1] == 0)
        return false;
    if (board[1][1] == board[0][0] && board[1][1] == board[2][2])
        return true;
    if (board[1][1] == board[0][2] && board[1][1] == board[2][0])
        return true;

    return false;
}

void printBoard(const int board[3][3])
{
    clear();
    for (int i = 0; i < 3; ++i) {
        cout << ' ';
        for (int j = 0; j < 3; ++j) {
            switch (board[i][j]) {
                case 1:
                    cout << 'O';
                    break;
                case 2:
                    cout << 'X';
                    break;
                default:
                    cout << ' ';
            }
            if (j < 2)
                cout << " | ";
        }
        cout << endl;
        if (i < 2)
            cout << "-----------" << endl;
    }
    cout << endl;
}

void getInput(const char turn, int &number)
{
    cout << turn << ": ";
    cin >> number;

    while (!cin.good() || number < 1 || number > 9) {
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << "\tEnter a number between 1-9!" << endl << turn << ": ";
        cin >> number;
    }
}
