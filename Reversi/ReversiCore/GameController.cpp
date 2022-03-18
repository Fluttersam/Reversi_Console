#include <iostream>
#include "Gamecontroller.h"

GameController::GameController()
{
	m_player1 = std::shared_ptr<Player>(new Player(Token::Colour::blue));
	m_player2 = std::shared_ptr<Player>(new Player(Token::Colour::green));
	m_activePlayer = m_player1;

	m_board = std::shared_ptr<Board>(new Board);
}

void GameController::setUpGame()
{
	m_board->initBoard();
	m_board->calculateOccupiedFields(*m_player1);
	m_board->calculateOccupiedFields(*m_player2);

	m_board->calculatePossibleFields(*m_activePlayer);

	std::cout << "Do you want to play against (1) CPU or (2) another player?" << std::endl;
	size_t numberOfPlayers;
	std::cin >> numberOfPlayers;
	std::cin.get();

	if (numberOfPlayers == 1)
	{
		std::cout << "What difficulty do you want to play? (1) easy (2) normal (3) hard" << std::endl;
		int difficulty;
		std::cin >> difficulty;

		m_player2->setDifficulty(static_cast<Player::Difficulty> (difficulty));
	}
}

void GameController::runGame()
{
	size_t x = 0, y = 0;

	m_board->drawBoard();

	while (!m_gameOver)
	{
		std::cout << "\n" << m_activePlayer->getPlayerName() << "'s turn: " << std::endl;

		if (m_activePlayer->getDifficulty() != Player::Difficulty::none)
		{
			Position position = m_activePlayer->selectPossibleField(*m_board);
			x = position.getX();
			y = position.getY();
		}
		else
		{
			for (const auto& field : m_activePlayer->getPossibleFields())
			{
				// need to change that again
				std::cout << field.getPosition().getX() << " " << field.getPosition().getY() << std::endl;
			}
			std::cout << "x: ";
			std::cin >> x;
			std::cout << "y: ";
			std::cin >> y;

			while (!m_activePlayer->containsField(x, y))
			{
				std::cout << "You can't place a token there." << std::endl;
				std::cout << "x: ";
				std::cin >> x;
				std::cout << "y: ";
				std::cin >> y;
			}
		}

		// add token and change the colour of existing tokens
		m_board->placeToken(Position(x, y), m_activePlayer->getColour());

		// recalcualte the occupied fields after new token
		m_board->calculateOccupiedFields(*m_player1);
		m_board->calculateOccupiedFields(*m_player2);

		// change active player and recalculate possible fields to put token on
		m_activePlayer = m_activePlayer == m_player1 ? m_player2 : m_player1;
		m_board->calculatePossibleFields(*m_activePlayer);

		m_board->drawBoard();

		checkWinConditions();
	}

	evaluateWinner();
}

void GameController::checkWinConditions()
{
	// no turns left for any player
	if (m_activePlayer->getPossibleFields().empty())
	{
		// change active player and recalculate possible fields to put token on
		m_activePlayer = m_activePlayer == m_player1 ? m_player2 : m_player1;
		m_board->calculatePossibleFields(*m_activePlayer);

		if (m_activePlayer->getPossibleFields().empty())
		{
			m_gameOver = true;

			return;
		}
	}

	// one player has no fields left
	if (m_player1->getOccupiedFields().empty() || m_player2->getOccupiedFields().empty())
	{
		m_gameOver = true;

		return;
	}

	// the board is full
	if (!m_board->getNumberOfEmptyFields())
	{
		m_gameOver = true;

		return;
	}
}

std::string GameController::evaluateWinner()
{
	std::string winnerName = "";

	if (m_player1->getOccupiedFields().size() > m_player2->getOccupiedFields().size())
	{
		winnerName = m_player1->getPlayerName();
	}
	else if (m_player1->getOccupiedFields().size() < m_player2->getOccupiedFields().size())
	{
		winnerName = m_player2->getPlayerName();
	}
	else
	{
		winnerName = "Everyone wins";
		std::cout << "\n Draw! Everyone wins! Woohoo! \n Thanks for playing" << std::endl;
		return winnerName;
	}

	std::cout << "\n" << winnerName << " wins! Woohoo!\n Thanks for playing" << std::endl;

	return winnerName;
}

void GameController::makePlayer2CPU(Player::Difficulty difficulty)
{
	m_player2->setDifficulty(difficulty);
}