#pragma once
#include <memory>
#include "Board.h"
#include "Player.h"

class GameController
{
public:

	GameController();
	void setUpGame();
	void runGame();
	std::string evaluateWinner();

	Player& getPlayer1() const { return *m_player1; }
	Player& getPlayer2() const { return *m_player2; }
	Board& getBoard() const { return *m_board; }

	void makePlayer2CPU(Player::Difficulty difficulty);

private:
	void checkWinConditions();

	std::shared_ptr<Board> m_board;
	std::shared_ptr<Player> m_player1;
	std::shared_ptr<Player> m_player2;
	std::shared_ptr<Player> m_activePlayer;

	bool m_gameOver = false;
};

