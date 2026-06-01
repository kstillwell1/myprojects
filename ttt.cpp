#include <iostream>
#include <vector>
class Game
{
private:
	bool turn = true;
	bool win = false;
	std::vector<char> board = { '1', '2', '3', 
								'4', '5', '6', 
								'7', '8', '9', };


	void welcomeMessage()
	{
		std::cout << "Welcome to tictactoe" << std::endl;
		std::cout << "To begin, please only enter the number of the space you would like to fill with your entry" << std::endl;
	}

	void printBoard()
	{
		std::cout << std::endl;
		std::cout << board[0] << " | " << board[1] << " | " << board[2] << std::endl;
		std::cout << "---------" << std::endl;
		std::cout << board[3] << " | " << board[4] << " | " << board[5] << std::endl;
		std::cout << "---------" << std::endl;
		std::cout << board[6] << " | " << board[7] << " | " << board[8] << std::endl;
		std::cout << std::endl;
	}

	void replace(char spot)
	{
		for (int i = 0; i < board.size(); ++i)
		{
			if (spot == board[i])
			{
				board[i] = turn ? 'X' : 'O';
				return;
			}
		}
	}

	void checkWin()
	{
		if (board[0] == board[1] && board[1] == board[2]) { win = true; return; }
		if (board[3] == board[4] && board[4] == board[5]) { win = true; return; }
		if (board[6] == board[7] && board[7] == board[8]) { win = true; return; }
		if (board[0] == board[3] && board[3] == board[6]) { win = true; return; }
		if (board[1] == board[4] && board[4] == board[7]) { win = true; return; }
		if (board[2] == board[5] && board[5] == board[8]) { win = true; return; }
		if (board[0] == board[4] && board[4] == board[8]) { win = true; return; }
		if (board[2] == board[4] && board[4] == board[6]) { win = true; return; }
	}

public:

	Game() {};
	~Game() {};

	void runGame()
	{
		welcomeMessage();

		while (!win)
		{
			char input;
			printBoard();

			if (turn)
			{
				std::cout << "Player 1(X): Please enter the number of the space you'd like to fill" << std::endl;
				std::cin >> input;
				replace(input);
				turn = false;
			}
			else
			{
				std::cout << "Player 2(O): Please enter the number of the space you'd like to fill" << std::endl;
				std::cin >> input;
				replace(input);
				turn = true;
			}
			checkWin();
		}
		printBoard();
		std::cout << "game over" << std::endl;
	}
};

int main()
{
	Game g;
	g.runGame();

	return 0;
}