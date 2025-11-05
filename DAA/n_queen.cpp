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
            board[row] = col;         // ✅ correct assignment
            if (Solve(row + 1))       // ✅ recursive call
                return 1;
        }
    }
    return 0; // no valid column found, backtrack
}

int main() {
    cout << "Enter the size of the board (n): ";
    cin >> n;

    if (n == 2 || n == 3) {
        cout << "No solutions exist for n = " << n;
        return 0;
    }

    board = new int[n];  // ✅ proper allocation (global board)

    if (Solve(0)) {
        cout << "\nSolution:\n";
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++)
                cout << (board[i] == j ? " Q " : " . ");
            cout << endl;
        }
    } else {
        cout << "No solution exists.";
    }

    delete[] board; // cleanup
    return 0;
}
