#include "Player.h"
#include <algorithm>
#include "Board.h"

void Player::addPossibleField(Field field)
{ 
	auto it = std::find(m_possibleFields.begin(), m_possibleFields.end(), field);

	// don't add the same field twice
	if (it == m_possibleFields.end())
	{
		m_possibleFields.push_back(field);
	}
}

// for easier calculations of CPU moves
void Player::addPossibleFieldDuplicates(Field field)
{
	m_possibleFields.push_back(field);
}

void Player::eraseOccupiedField(Field field)
{
	auto it = std::remove(m_occupiedFields.begin(), m_occupiedFields.end(), field);
}

bool Player::containsField(size_t x, size_t y)
{
	for (const auto& field : m_possibleFields)
	{
		if (field.getPosition().getX() == x && field.getPosition().getY() == y)
		{
			return true;
		}
	}

	return false;
}

void Player::sortPossibleFields()
{
	std::sort(m_possibleFields.begin(), m_possibleFields.end());
}

Position Player::selectPossibleField(const Board& board)
{
	switch (m_difficulty)
	{
	case Difficulty::easy:
		return (selectRandomPossibleField());
	case Difficulty::normal:
		return (selectPossibleFieldMostDirections());
	case Difficulty::hard:
		return (selectPossibleFieldMostTokens(board));
	case Difficulty::none:
	default:
		return Position(-1, -1);
	}
}

Position Player::selectRandomPossibleField()
{
	auto randomIndex = std::rand() % m_possibleFields.size();

	return m_possibleFields.at(randomIndex).getPosition();
}

Position Player::selectPossibleFieldMostDirections()
{
	Position position;
	int directionsToMove = 0;

	for (size_t i = 0; i < m_possibleFields.size(); ++i)
	{
		int occurrences = std::count(m_possibleFields.begin(), m_possibleFields.end(), m_possibleFields.at(i));

		if (occurrences > directionsToMove)
		{
			directionsToMove = occurrences;
			position = m_possibleFields.at(i).getPosition();
		}
	}

	return position;
}

Position Player::selectPossibleFieldMostTokens(const Board& originalBoard)
{
	Position position;
	unsigned int tokensToTurn = 0;
	std::vector<Field> occupiedFields = m_occupiedFields;

	//Board board(originalBoard);
	Board board;

	//board.saveBoard();

	for (size_t i = 0; i < m_possibleFields.size(); ++i)
	{
		//board.resetBoard();
		board.copyBoard(originalBoard);

		board.placeToken(m_possibleFields.at(i).getPosition(), m_colour);
		board.calculateOccupiedFields(*this);

		if (m_occupiedFields.size() > tokensToTurn)
		{
			tokensToTurn = m_occupiedFields.size();

			position = m_possibleFields.at(i).getPosition();
		}
	}

	m_occupiedFields = occupiedFields;

	return position;
}