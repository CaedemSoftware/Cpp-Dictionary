#include <iostream>
using namespace std;

bool isWon(char symbol, char board[][3])
{
	// NOTE: i am sure this can be  improved upon but i just wanted to get something working for now. please change if you find a better way to do it. maybe loops?

	// checks for matching symbols
	if ((board[0][0] == symbol && board[0][1] == symbol && board[0][2] == symbol) || (board[0][0] == symbol && board[1][0] == symbol && board[2][0] == symbol)) { // checks first column (left) and first row (top)
		return true;   // if 3 symbols match, returns true to end the While loop in main, ending the game
	}

	if ((board[1][0] == symbol && board[1][1] == symbol && board[1][2] == symbol) || (board[0][1] == symbol && board[1][1] == symbol && board[2][1] == symbol)) { // checks second column (middle down) and second row (middle horizontal)
		return true;  // if 3 symbols match, returns true to end the While loop in main, ending the game
	}

	if ((board[2][0] == symbol && board[2][1] == symbol && board[2][2] == symbol) || (board[0][2] == symbol && board[1][2] == symbol && board[2][2] == symbol)) { // checks third column (right) and third row (bottom)
		return true;  // if 3 symbols match, returns true to end the While loop in main, ending the game
	}

	if ((board[0][0] == symbol && board[1][1] == symbol && board[2][2] == symbol) || (board[0][2] == symbol && board[1][1] == symbol && board[2][0] == symbol)) { // checks if all diagonal matches
		return true;  // if 3 symbols match, returns true to end the While loop in main, ending the game
	}
	return false; // if none of the checks are true, return false to continue While loop until game is done
}

bool isDraw(char board[][3])
{
	for (int row = 0; row < 3; row++) {
		for (int column = 0; column < 3; column++) {
			if (board[row][column] == ' ') {
				return false;
			}
		}
	}
	return true;
}

void displayBoard(char board[][3])
{
	cout << "\n-------------" << endl;
	cout << "| " << board[0][0] << " | " << board[0][1] << " | " << board[0][2] << " | " << endl;
	cout << "-------------" << endl;
	cout << "| " << board[1][0] << " | " << board[1][1] << " | " << board[1][2] << " | " << endl;
	cout << "-------------" << endl;
	cout << "| " << board[2][0] << " | " << board[2][1] << " | " << board[2][2] << " | " << endl;
	cout << "-------------" << endl;
}

void makeAMove(char board[][3], char symbol)
{
	cout << "Enter a row (0, 1, 2) for player " << symbol << "   : ";
	int rowIndex;
	while (!(cin >> rowIndex)) { // If input was not an integer
		cin.clear(); // Reset error flag
		cin.ignore(1000, '\n'); // Skip next 1000 chars or until newline
		cout << "Wrong type. Enter a row (0, 1, 2) for player " << symbol << "   : ";
	}
	cout << "Enter a column (0, 1, 2) for player " << symbol << ": ";
	int columnIndex;
	while (!(cin >> columnIndex)) { // If input was not an integer
		cin.clear(); // Reset error flag
		cin.ignore(1000, '\n'); // Skip next 1000 chars or until newline
		cout << "Wrong type. Enter a column (0, 1, 2) for player " << symbol << ": ";
	}
	if (board[rowIndex][columnIndex] == ' ') {
		board[rowIndex][columnIndex] = symbol;
	}
	else {
		cout << "This cell is already occupied. Try a different cell" << endl;
		makeAMove(board, symbol);
	}
}

int main() {
	//
	//	PLEASE DO NOT CHANGE function main
	//
	char board[3][3] = { { ' ', ' ', ' ' },{ ' ', ' ', ' ' },{ ' ', ' ', ' ' } };
	displayBoard(board);

	while (true) {
		// The first player makes a move
		makeAMove(board, 'X');
		displayBoard(board);
		if (isWon('X', board)) {
			cout << "X player won" << endl;
			exit(0);
		}
		else if (isDraw(board)) {
			cout << "No winner" << endl;
			exit(0);
		}

		// The second player makes a move
		makeAMove(board, 'O');
		displayBoard(board);

		if (isWon('O', board)) {
			cout << "O player won" << endl;
			exit(0);
		}
		else if (isDraw(board)) {
			cout << "No winner" << endl;
			exit(0);
		}
	}

	return 0;
}
