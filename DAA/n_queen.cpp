#include <iostream>
#include <cmath>  // for abs()
using namespace std;

int n;
int* board;

int isSafe(int row, int col) {
    for (int i = 0; i < row; i++) {
        if (board[i] == col || abs(board[i] - col) == abs(i - row))
            return 0;
    }
    return 1;
}

int Solve(int row) {
    if (row == n)
        return 1;  // all queens placed

    for (int col = 0; col < n; col++) {
        if (isSafe(row, col)) {
            board[row] = col;
            if (Solve(row + 1))
                return 1;
        }
    }
    return 0; // backtrack
}

int main() {
    cout << "Enter the size of the board (n): ";
    cin >> n;

    if (n == 2 || n == 3) {
        cout << "No solutions exist for n = " << n;
        return 0;
    }

    board = new int[n];  // allocate memory for board

    int firstCol;
    cout << "Enter the column for the first queen (0 to " << n - 1 << "): ";
    cin >> firstCol;

    if (firstCol < 0 || firstCol >= n) {
        cout << "Invalid column! Must be between 0 and " << n - 1;
        delete[] board;
        return 0;
    }

    board[0] = firstCol; // user-placed first queen

    if (Solve(1)) {  // start solving from row 1
        cout << "\nSolution:\n";
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++)
                cout << (board[i] == j ? " Q " : " . ");
            cout << endl;
        }
    } else {
        cout << "\nNo solution exists with first queen at (row 0, column " << firstCol << ").\n";
    }

    delete[] board;
    return 0;
}
