#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

class Player
{
private:
	std::string name;
	std::string title = "";
	int wins = 0, losses = 0, currWinStreak = 0;
	bool streaking = false;


public:
	Player() {};
	~Player() {};

	Player(std::string theName)
		: name(theName)
		, title("")
		, wins(0)
		, losses(0)
		, currWinStreak(0)
	{
	};

	std::string getName()
	{
		return name;
	}

	std::string getTitle()
	{
		return title;
	}

	void setTitle(std::string newTitle)
	{
		title = newTitle;
	}

	void addWin()
	{
		wins++;
		currWinStreak++;
	}

	void addLoss()
	{
		losses++;
	}

	int getWins()
	{
		return wins;
	}

	int getLosses()
	{
		return losses;
	}

	int getCurrWinStreak()
	{
		return currWinStreak;
	}

	void setCurrWinStreak(int amount)
	{
		currWinStreak = amount;
	}

	bool getStreaking()
	{
		return streaking;
	}

	void setStreaking(bool flag)
	{
		streaking = flag;
	}
};

class IGame
{
public:
	virtual void printBoard() = 0;
	virtual bool checkTie() = 0;
	virtual bool checkSpot(int spot) = 0;
	virtual void replace(bool turn) = 0;
	virtual bool checkWin() = 0;
	virtual void setBoard() = 0;
	virtual ~IGame() {}
};

class TTT : public IGame
{
private:

	int rows[9] = { 0, 0, 0, 1, 1, 1, 2, 2, 2 };
	int cols[9] = { 0, 1, 2, 0, 1, 2, 0, 1, 2 };

	char board[3][3];
	bool spotCheck[3][3];

public:

	void printBoard() override
	{
		std::cout << std::endl;
		std::cout << board[0][0] << " | " << board[0][1] << " | " << board[0][2] << std::endl;
		std::cout << "---------" << std::endl;
		std::cout << board[1][0] << " | " << board[1][1] << " | " << board[1][2] << std::endl;
		std::cout << "---------" << std::endl;
		std::cout << board[2][0] << " | " << board[2][1] << " | " << board[2][2] << std::endl;
		std::cout << std::endl;
	}

	bool checkTie() override
	{
		int count = 0;
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
				if (spotCheck[i][j] == true)
					count++;

		if (count == 9)
			return true;

		return false;
	}

	bool checkSpot(int spot) override
	{
		if (spotCheck[rows[spot]][cols[spot]] == true)
			return true;
		return false;
	}

	void replace(bool turn) override
	{
		int input;
		std::cin >> input;
		if (input >= 9 || input <= -1)
		{
			std::cout << "Invalid input, please try again: " << std::endl;
			replace(turn);
		}
		else
		{
			if (!checkSpot(input))
			{
				board[rows[input]][cols[input]] = turn ? 'X' : 'O';
				spotCheck[rows[input]][cols[input]] = true;
			}
			else
			{
				std::cout << "Invalid input, please try again: " << std::endl;
				replace(turn);
			}
		}
	}

	bool checkWin() override
	{
		static const int winLines[8][3] = {
			{0, 1, 2}, {3, 4, 5}, {6, 7, 8},
			{0, 3, 6}, {1, 4, 7}, {2, 5, 8},
			{0, 4, 8}, {2, 4, 6}
		};

		for (auto& winnerlines : winLines)
		{
			if (board[rows[winnerlines[0]]][cols[winnerlines[0]]] == board[rows[winnerlines[1]]][cols[winnerlines[1]]] &&
				board[rows[winnerlines[1]]][cols[winnerlines[1]]] == board[rows[winnerlines[2]]][cols[winnerlines[2]]])
				return true;
		}
		return false;
	}

	void setBoard() override
	{
		char num = '0';
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				board[i][j] = num;
				num++;
			}
		}


		memset(spotCheck, false, sizeof(spotCheck));
	}
};

class Connect4 : public IGame
{
private:
	char board[6][7];
	bool spotCheck[6][7];

public:
	void printBoard()
	{
		std::cout << std::endl;
		std::cout << board[0][0] << " | " << board[0][1] << " | " << board[0][2] << " | " << board[0][3] << " | " << board[0][4] << " | " << board[0][5] << " | " << board[0][6] << std::endl;
		std::cout << board[1][0] << " | " << board[1][1] << " | " << board[1][2] << " | " << board[1][3] << " | " << board[1][4] << " | " << board[1][5] << " | " << board[1][6] << std::endl;
		std::cout << board[2][0] << " | " << board[2][1] << " | " << board[2][2] << " | " << board[2][3] << " | " << board[2][4] << " | " << board[2][5] << " | " << board[2][6] << std::endl;
		std::cout << board[3][0] << " | " << board[3][1] << " | " << board[3][2] << " | " << board[3][3] << " | " << board[3][4] << " | " << board[3][5] << " | " << board[3][6] << std::endl;
		std::cout << board[4][0] << " | " << board[4][1] << " | " << board[4][2] << " | " << board[4][3] << " | " << board[4][4] << " | " << board[4][5] << " | " << board[4][6] << std::endl;
		std::cout << board[5][0] << " | " << board[5][1] << " | " << board[5][2] << " | " << board[5][3] << " | " << board[5][4] << " | " << board[5][5] << " | " << board[5][6] << std::endl;
		std::cout << std::endl;
	}
	bool checkTie();
	bool checkSpot(int spot);
	void replace(bool turn);
	bool checkWin();
	void setBoard()
	{
		int num = '0';
		for (int i = 0; i < 6; ++i)
		{
			for (int j = 0; j < 7; ++j)
			{
				board[i][j] = num;
				num++;
			}
		}
		memset(spotCheck, false, sizeof(spotCheck));
	}
};

class Game
{
private:
	bool turn = true;
	bool end = false;
	std::vector<Player> playerPool;
	bool anotherGame = true;

	IGame* currentGame = nullptr;

	Player* currPlayer1 = nullptr;
	Player* currPlayer2 = nullptr;

	void playerPoolEntry()
	{
		std::cout << "Please enter each name and press enter after each name\n";
		std::cout << "If all names are entered, type 'end'\n";
		std::string playerName;
		while (!(playerName == "end"))
		{
			std::cin >> playerName;
			if (playerName == "end")
			{
				return;
			}
			playerPool.emplace_back(playerName);
		}
		std::cout << "You've completed the name entry" << std::endl;
	}

	void welcomeMessage()
	{
		std::cout << "Welcome to Kev's Games" << std::endl;
	}

	void selectGame()
	{
		int choice;
		std::cout << "Select a game by typing in the number of the game you would like to play: \n";
		std::cout << "1. Tic Tac Toe\n";
		std::cout << "2. Connect Four\n";
		std::cin >> choice;

		delete currentGame;

		switch (choice)
		{
			case 1:
			{
				currentGame = new TTT();
				break;
			}
			case 2:
			{
				currentGame = new Connect4;
				break;
			}
			default:
			{
				std::cout << "invalid selection please try again\n";
				selectGame();
			}
		}
	}

	void playerSelection()
	{
		while (currPlayer1 == nullptr)
		{
			std::cout << "Enter the Name of the first player and then press enter: " << std::endl;
			std::string playerNameInput;
			std::cin >> playerNameInput;

			for (int i = 0; i < playerPool.size(); ++i)
			{
				if (playerNameInput == playerPool[i].getName())
				{
					currPlayer1 = &playerPool[i];
					break;
				}
			}
			if (currPlayer1 == nullptr)
			{
				std::cout << "This player was not in the list, please try again" << std::endl;
			}
		}

		while (currPlayer2 == nullptr)
		{
			std::cout << "Enter the Name of the second player and then press enter: " << std::endl;
			std::string playerNameInput2;
			std::cin >> playerNameInput2;

			for (int i = 0; i < playerPool.size(); ++i)
			{
				if (playerNameInput2 == playerPool[i].getName())
				{
					currPlayer2 = &playerPool[i];
					break;
				}
			}
			if (currPlayer2 == nullptr)
			{
				std::cout << "This player was not in the list, please try again" << std::endl;
			}
		}
	}

	void updateStats(Player* currPlayerWin, Player* currPlayerLoss)
	{
		currentGame->printBoard();

		currPlayerWin->addWin();
		if (currPlayerWin->getStreaking() == false)
		{
			currPlayerWin->setStreaking(true);
		}
		if (currPlayerWin->getCurrWinStreak() == 5)
		{
			if (currPlayerWin->getTitle() != "Yokozuna ")
			{
				currPlayerWin->setTitle("Yokozuna ");
			}
		}
		std::cout << currPlayerWin->getTitle() << currPlayerWin->getName() << "'s Wins: " << currPlayerWin->getWins() << "  Losses: " << currPlayerWin->getLosses() << "  Current Win Streak: " << currPlayerWin->getCurrWinStreak() << std::endl;

		if (currPlayerLoss->getStreaking() == true)
		{
			currPlayerLoss->setStreaking(false);
			currPlayerLoss->setCurrWinStreak(0);
		}
		currPlayerLoss->addLoss();
		std::cout << currPlayerLoss->getTitle() << currPlayerLoss->getName() << "'s Wins: " << currPlayerLoss->getWins() << "  Losses: " << currPlayerLoss->getLosses() << "  Current Win Streak: " << currPlayerLoss->getCurrWinStreak() << std::endl;


		if (currentGame->checkTie())
		{
			std::cout << "Game was a tie" << std::endl;
			std::cout << currPlayerWin->getTitle() << currPlayerWin->getName() << "'s Wins: " << currPlayerWin->getWins() << "  Losses: " << currPlayerWin->getLosses() << "  Current Win Streak: " << currPlayerWin->getCurrWinStreak() << std::endl;
			std::cout << currPlayerLoss->getTitle() << currPlayerLoss->getName() << "'s Wins: " << currPlayerLoss->getWins() << "  Losses: " << currPlayerLoss->getLosses() << "  Current Win Streak: " << currPlayerLoss->getCurrWinStreak() << std::endl;
		}
	}

	void postGameQuestions()
	{
		int answer;
		std::cout << std::endl;
		std::cout << "Welcome to the post game questions, please enter the number associated with how you would like to continue\n";
		std::cout << "1. Play again with the same players\n";
		std::cout << "2. Play again with a new set of players\n";
		std::cout << "3. Play again but a new game\n";
		std::cout << "4. End the program\n";
		std::cin >> answer;

		if (answer == 1)
		{
			anotherGame = true;
			end = false;
			currentGame->setBoard();
		}
		else if (answer == 2)
		{
			currPlayer1 = nullptr;
			currPlayer2 = nullptr;
			playerSelection();
			anotherGame = true;
			end = false;
			currentGame->setBoard();
		}
		else if (answer == 3)
		{
			currPlayer1 = nullptr;
			currPlayer2 = nullptr;
			playerSelection();
			anotherGame = true;
			selectGame();
			//enter on how to redirect to another game
		}
		else
		{
			std::cout << "Thanks for playing Group TicTacToe by Stilly, Below you final the final stats for all players. " << std::endl;
			std::cout << std::endl;
			for (int i = 0; i < playerPool.size(); ++i)
			{
				std::cout << playerPool[i].getTitle() << playerPool[i].getName() << "  Wins: " << playerPool[i].getWins() << "  Losses: " << playerPool[i].getLosses() << "  Current Win Streak: " << playerPool[i].getCurrWinStreak() << std::endl;
			}
			anotherGame = false;
			end = true;
		}
	}

	void gameLoop()
	{
		currentGame->setBoard();
		while (!end)
		{
			currentGame->printBoard();

			if (turn)
			{
				std::cout << currPlayer1->getTitle() << currPlayer1->getName() << "(" << (turn ? 'X' : 'O') << ") Please enter your first move : " << std::endl;
				currentGame->replace(turn);
				if (currentGame->checkWin())
				{
					updateStats(currPlayer1, currPlayer2);
					break;
				}
				turn = false;
			}
			else
			{
				std::cout << currPlayer2->getTitle() << currPlayer2->getName() << "(" << (turn ? 'X' : 'O') << ") Please enter your first move:" << std::endl;
				currentGame->replace(turn);
				if (currentGame->checkWin())
				{
					updateStats(currPlayer2, currPlayer1);
					break;
				}
				turn = true;
			}
			currentGame->checkWin();
			if (!currentGame->checkWin())
			{
				currentGame->checkTie();
			}
		}
		postGameQuestions();
	}

public:

	Game() {};
	~Game()
	{
		delete currentGame;
	}

	void runGame()
	{
		welcomeMessage();
		selectGame();
		if (playerPool.empty())
		{
			playerPoolEntry();
		}
		playerSelection();

		while (anotherGame == true)
		{
			gameLoop();
		}
	}
};

int main()
{
	Game g;
	g.runGame();

	return 0;
}
