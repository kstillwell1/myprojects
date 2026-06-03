/*
Task: Implementation of Persistent Player Profiles & Multi-Match Sessions

Objective: Upgrade the current single-match execution into a persistent "Session" that can track player statistics across multiple consecutive games.

Requirements:

	Player Registration: When the program starts, the user must be able to register a pool of players by entering their names.

	Match Setup: Before each match begins, the program must prompt the user to select two players from the registered pool to compete in the current round.

	Dynamic Turn Announcements: Instead of hardcoded "Player 1" or "Player 2" prompts, the game must identify the current player by their name (e.g., "Alice, please enter your move").

	The "Yokozuna" Promotion: The system must track each player's win streak across multiple games. If a player reaches a win streak of 5 consecutive wins, they are permanently promoted to the rank of "Yokozuna." Once promoted, their name must always be prefixed with this title for the remainder of the program's execution (e.g., "Yokozuna Alice").

	Session Statistics: At the conclusion of every match, the program must output a summary for the two participants, displaying:
		Their Name (including any titles).
		Total games won during this session.
		Total games lost during this session.
		Their current active win streak.

	Session Loop: After a match ends and stats are displayed, the program should ask if the user wants to play another match with the existing player pool or exit the program.

	Note: create update stats function and plug in to both checkWin and checkCat functions

*/

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

struct Board
{
	std::vector<char> board;
	std::vector<bool> spotCheck;
};

class Game
{
private:
	bool turn = true;
	bool end = false;
	std::vector<Player> playerPool;
	bool anotherGame = true;

	Board board;

	Player* currPlayer1 = nullptr;
	Player* currPlayer2 = nullptr;

	void playerPoolEntry()
	{
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
		std::cout << "Welcome to group tictactoe" << std::endl;
		std::cout << "Enter each player's name and press enter after each name, when done please enter 'end' (just like that in all caps)" << std::endl;
	}

	void printBoard()
	{
		std::cout << std::endl;
		std::cout << board.board[0] << " | " << board.board[1] << " | " << board.board[2] << std::endl;
		std::cout << "---------" << std::endl;
		std::cout << board.board[3] << " | " << board.board[4] << " | " << board.board[5] << std::endl;
		std::cout << "---------" << std::endl;
		std::cout << board.board[6] << " | " << board.board[7] << " | " << board.board[8] << std::endl;
		std::cout << std::endl;
	}

	bool checkCat()
	{
		int count = 0;
		for (int i = 0; i < board.spotCheck.size(); ++i)
		{
			if (checkSpot(i))
			{
				count++;
			}
		}
		if (count == 9)
		{
			end = true;
			std::cout << std::endl;
			std::cout << " No Winners " << std::endl;
			return true;
		}
		return false;
	}

	bool checkSpot(int spot)
	{
		if (board.spotCheck[spot] == true)
		{
			return true;
		}
		return false;
	}

	void replace()
	{
		int input;
		std::cin >> input;
		if (input >= 9 || input <= -1)
		{
			std::cout << "Invalid input, please try again: " << std::endl;
			replace();
		}
		else
		{
			if (!checkSpot(input))
			{
				board.board[input] = turn ? 'X' : 'O';
				board.spotCheck[input] = true;
			}
			else
			{
				std::cout << "Invalid input, please try again: " << std::endl;
				replace();
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

	bool checkWin()
	{
		if (board.board[0] == board.board[1] && board.board[1] == board.board[2]) { return true; }
		else if (board.board[3] == board.board[4] && board.board[4] == board.board[5]) { return true; }
		else if (board.board[6] == board.board[7] && board.board[7] == board.board[8]) { return true; }
		else if (board.board[0] == board.board[3] && board.board[3] == board.board[6]) { return true; }
		else if (board.board[1] == board.board[4] && board.board[4] == board.board[7]) { return true; }
		else if (board.board[2] == board.board[5] && board.board[5] == board.board[8]) { return true; }
		else if (board.board[0] == board.board[4] && board.board[4] == board.board[8]) { return true; }
		else if (board.board[2] == board.board[4] && board.board[4] == board.board[6]) { return true; }
		else { return false; }
	}

	void updateStats()
	{
		printBoard();

		if (turn)
		{
			currPlayer1->addWin();
			if (currPlayer1->getStreaking() == false)
			{
				currPlayer1->setStreaking(true);
			}
			if (currPlayer1->getCurrWinStreak() == 5)
			{
				if (currPlayer1->getTitle() != "Yokozuna ")
				{
					currPlayer1->setTitle("Yokozuna ");
				}
			}
			std::cout << currPlayer1->getTitle() << currPlayer1->getName() << "'s Wins: " << currPlayer1->getWins() << "  Losses: " << currPlayer1->getLosses() << "  Current Win Streak: " << currPlayer1->getCurrWinStreak() << std::endl;

			if (currPlayer2->getStreaking() == true)
			{
				currPlayer2->setStreaking(false);
				currPlayer2->setCurrWinStreak(0);
			}
			currPlayer2->addLoss();
			std::cout << currPlayer2->getTitle() << currPlayer2->getName() << "'s Wins: " << currPlayer2->getWins() << "  Losses: " << currPlayer2->getLosses() << "  Current Win Streak: " << currPlayer2->getCurrWinStreak() << std::endl;
		}
		else
		{
			currPlayer2->addWin();
			if (currPlayer2->getStreaking() == false)
			{
				currPlayer2->setStreaking(true);
			}
			if (currPlayer2->getCurrWinStreak() == 5)
			{
				if (currPlayer2->getTitle() != "Yokozuna ")
				{
					currPlayer2->setTitle("Yokozuna ");
				}
			}
			std::cout << currPlayer2->getTitle() << currPlayer2->getName() << "'s Wins: " << currPlayer2->getWins() << "  Losses: " << currPlayer2->getLosses() << "  Current Win Streak: " << currPlayer2->getCurrWinStreak() << std::endl;

			if (currPlayer1->getStreaking() == true)
			{
				currPlayer1->setStreaking(false);
				currPlayer1->setCurrWinStreak(0);
			}
			currPlayer1->addLoss();
			std::cout << currPlayer1->getTitle() << currPlayer1->getName() << "'s Wins: " << currPlayer1->getWins() << "  Losses: " << currPlayer1->getLosses() << "  Current Win Streak: " << currPlayer1->getCurrWinStreak() << std::endl;
		}

		if (checkCat())
		{
			std::cout << "Game was a tie" << std::endl;
			std::cout << currPlayer1->getTitle() << currPlayer1->getName() << "'s Wins: " << currPlayer1->getWins() << "  Losses: " << currPlayer1->getLosses() << "  Current Win Streak: " << currPlayer1->getCurrWinStreak() << std::endl;
			std::cout << currPlayer2->getTitle() << currPlayer2->getName() << "'s Wins: " << currPlayer2->getWins() << "  Losses: " << currPlayer2->getLosses() << "  Current Win Streak: " << currPlayer2->getCurrWinStreak() << std::endl;
		}
	}

	void setBoard()
	{
		board.board = { '0', '1', '2',
						'3', '4', '5',
						'6', '7', '8', };

		board.spotCheck = { false, false, false,
							false, false, false,
							false, false, false, };
	}

	void postGameQuestions()
	{
		std::string answer;
		std::cout << std::endl;
		std::cout << " Would you like to play again? (yes/no)" << std::endl;
		std::cin >> answer;
		
		if (answer == "yes")
		{
			std::string answer3;
			std::cout << std::endl;
			std::cout << "Same players? (yes/no)" << std::endl;
			std::cin >> answer3;
			if (answer3 == "yes")
			{
				anotherGame = true;
				end = false;
				setBoard();
				return;
			}
			else
			{
				currPlayer1 = nullptr;
				currPlayer2 = nullptr;
				playerSelection();
				anotherGame = true;
				end = false;
				setBoard();

			}
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
		while (!end)
		{
			printBoard();

			if (turn)
			{
				std::cout << currPlayer1->getTitle() << currPlayer1->getName() << "(X) Please enter your first move:" << std::endl;
				replace();
				if (checkWin())
				{
					updateStats();
					break;
				}
				turn = false;
			}
			else
			{
				std::cout << currPlayer2->getTitle() << currPlayer2->getName() << "(O) Please enter your first move:" << std::endl;
				replace();
				if (checkWin())
				{
					updateStats();
					break;
				}
				turn = true;
			}
			checkWin();
			if (!checkWin())
			{
				checkCat();
			}
		}
		postGameQuestions();
	}

public:

	Game() {};
	~Game() {};

	void runGame()
	{
		setBoard();
		welcomeMessage();
		playerPoolEntry();
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
