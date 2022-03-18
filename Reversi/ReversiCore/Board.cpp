#include "Board.h"
#include <iostream>

Board::Board(const Board& board)
{
	for (size_t i = 0; i < board.m_fields.size(); ++i)
	{
		// TODO das Problem könnte sein, dass push_back die Referenz übernimmt (und keine Kopie).
		// eventuell einfacher Fix wäre: Board.createCopy(). 
		m_fields.push_back(board.m_fields.at(i));
	}
}

void Board::initBoard()
{
	for (size_t i = 1; i <= BOARD_SIZE; ++i)
	{
		for (size_t j = 1; j <= BOARD_SIZE; ++j)
		{
			if (!drawstartTokens(i, j))
			{
				m_fields.push_back(Field(i, j));
			}
		}
	}
}

void Board::drawBoard()
{
	size_t row = 1;

	for (auto field : m_fields)
	{
		if (row != field.getPosition().getX())
		{
			std::cout << "\n";
			++row;
		}

		if (field.getToken() != nullptr)
		{
			switch (field.getToken()->getColour())
			{
			case Token::Colour::green:
				std::cout << "x";
				break;
			case Token::Colour::blue:
				std::cout << "o";
				break;
			default:
				std::cout << "_";
				break;
			}
		}
		else
		{
			std::cout << "_";
		}
	}
}

void Board::calculatePossibleFields(Player &player) 
{
	player.clearPossibleFields();

	auto startIndex = static_cast<int>(Direction::right);
	auto endIndex = static_cast<int>(Direction::rightDown);

	for (int i = startIndex; i <= endIndex; ++i)
	{
		calculatePossibleFields(player, static_cast<Direction>(i));
	}

	player.sortPossibleFields();
}

void Board::calculateOccupiedFields(Player& player)
{
	player.clearOccupiedFields();

	for (const auto& field : m_fields)
	{
		if (field.getToken() && field.getToken()->getColour() == player.getColour())
		{
			player.addOccupiedField(field);
		}
	}
}

void Board::placeToken(Position position, Token::Colour colour)
{
	addToken(position, colour);
	findTokensToChange(position, colour);
}

bool Board::drawstartTokens(size_t x, size_t y)
{
	for (const auto &token : m_startTokens)
	{
		if (token.getPosition().getX() == x && token.getPosition().getY() == y)
		{
			switch (token.getColour())
			{
			case Token::Colour::green:
				m_fields.push_back(Field(x, y, Token::Colour::green));
				return true;
			case Token::Colour::blue:
				m_fields.push_back(Field(x, y, Token::Colour::blue));
				return true;
			default:
				break;
			}
		}
	}

	return false;
}

int Board::getNumberOfEmptyFields()
{
	int numberOfEmptyFields = 0;

	for (const auto& field : m_fields)
	{
		if (!field.getToken())
		{
			++numberOfEmptyFields;
		}
	}

	return numberOfEmptyFields;
}

void Board::setUpBoard(std::string board)
{
	int x = 1;
	int y = 1;

	for (size_t i = 0; i < board.length(); ++i)
	{
		if (board.at(i) == 'o')
		{
			m_fields.push_back(Field(x, y, Token::Colour::blue));
		}
		else if (board.at(i) == 'x')
		{
			m_fields.push_back(Field(x, y, Token::Colour::green));
		}
		else if(board.at(i) == '_')
		{
			m_fields.push_back(Field(x, y));
		}
		
		++y;

		if (board.at(i) == '|')
		{
			y = 1;
			++x;
			std::cout << "\n";
		}
		else
		{
			std::cout << board.at(i);
		}
	}
}

void Board::saveBoard()
{
	for (size_t i = 0; i < m_fields.size(); ++i)
	{
		if (m_fields.at(i).getToken())
		{
			if (m_fields.at(i).getToken()->getColour() == Token::Colour::blue)
			{
				m_savedBoard += "o";
			}
			else if (m_fields.at(i).getToken()->getColour() == Token::Colour::green)
			{
				m_savedBoard += "x";
			}
		}
		else
		{
			m_savedBoard += "_";
		}

		if (i && !((i+1) % 8))
		{
			m_savedBoard += "|";
		}
	}
}

void Board::loadBoard()
{
	int x = 1;
	int y = 1;

	for (size_t i = 0; i < m_savedBoard.length(); ++i)
	{
		if (m_savedBoard.at(i) == 'o')
		{
			m_fields.push_back(Field(x, y, Token::Colour::blue));
		}
		else if (m_savedBoard.at(i) == 'x')
		{
			m_fields.push_back(Field(x, y, Token::Colour::green));
		}
		else if (m_savedBoard.at(i) == '_')
		{
			m_fields.push_back(Field(x, y));
		}

		++y;

		if (m_savedBoard.at(i) == '|')
		{
			y = 1;
			++x;
		}
	}
}

void Board::resetBoard()
{
	m_fields.clear();
	loadBoard();
}

void Board::copyBoard(const Board& board)
{
	for (size_t i = 0; i < board.m_fields.size(); ++i)
	{
		size_t x = board.m_fields.at(i).getPosition().getX();
		size_t y = board.m_fields.at(i).getPosition().getY();

		if (board.m_fields.at(i).getToken())
		{
			Token::Colour tokenColour = board.m_fields.at(i).getToken()->getColour();

			m_fields.push_back(Field(x, y, tokenColour));
		}
		else
		{
			m_fields.push_back(Field(x, y));
		}

	}
}

void Board::addTokensToChange(std::vector<Field> tokensToChange)
{
	for (const auto& token : tokensToChange)
	{
		m_tokensToChange.push_back(token);
	}
}

void Board::changeTokenColour(Token::Colour colour)
{
	for (const auto& field : m_tokensToChange)
	{
		field.getToken()->changeColour(colour);
	}
}

int Board::getIndex(Position position)
{
	return (position.getX() - 1) * BOARD_SIZE + (position.getY() - 1);
}

bool Board::addPossibleTokensToChange(int index, Token::Colour colour, std::vector<Field>& possibleTokensToChange)
{
	if (m_fields.at(index).getToken() && m_fields.at(index).getToken()->getColour() != colour)
	{
		possibleTokensToChange.push_back(m_fields.at(index));
	}

	if (m_fields.at(index).getToken() && m_fields.at(index).getToken()->getColour() == colour)
	{
		return true;
	}

	return false;
}

bool Board::calcualteTokensToChange(const int fieldIndex, Direction direction, Token::Colour colour, std::vector<Field>& possibleTokensToChange)
{
	const int jump = indexToMove(direction);

	if (fieldIndex + jump >= 0 && fieldIndex + jump < m_fields.size() && m_fields.at(fieldIndex + jump).getToken() && m_fields.at(fieldIndex + jump).getToken()->getColour() != colour)
	{
		size_t row = m_fields.at(fieldIndex).getPosition().getX();

		for (int i = fieldIndex + jump; i >= 0 && i < m_fields.size(); i = i + jump)
		{
			if (reachedLastTokenToChange(direction, i, row, jump, m_fields.at(i).getPosition(), colour))
			{
				break;
			}

			if (addPossibleTokensToChange(i, colour, possibleTokensToChange))
			{
				return true;
			}
		}
	}

	return false;
}

const int Board::indexToMove(Direction direction)
{
	switch (direction)
	{
	case Direction::right:
		return ROW_INDEX_JUMP;
	case Direction::left:
		return -ROW_INDEX_JUMP;
	case Direction::down:
		return COLUMN_INDEX_JUMP;
	case Direction::up:
		return -COLUMN_INDEX_JUMP;
	case Direction::rightUp:
		return -RIGHT_TOP_BOTTOM_LEFT_JUMP;
	case Direction::leftDown:
		return RIGHT_TOP_BOTTOM_LEFT_JUMP;
	case Direction::leftUp:
		return -LEFT_TOP_BOTTOM_RIGHT_JUMP;
	case Direction::rightDown:
		return LEFT_TOP_BOTTOM_RIGHT_JUMP;
	default:
		return -1;
	}
}

void Board::calculatePossibleFields(Player& player, Direction direction)
{
	const int jump = indexToMove(direction);

	for (size_t i = 0; i < m_fields.size(); ++i)
	{
		if (m_fields.at(i).getToken() && m_fields.at(i).getToken()->getColour() == player.getColour())
		{
			size_t row = m_fields.at(i).getPosition().getX();

			if (i + jump >= 0 && i + jump < m_fields.size() && m_fields.at(i + jump).getToken() != nullptr)
			{
				if (m_fields.at(i + jump).getToken()->getColour() != player.getColour())
				{
					for (int x = i + jump; x >= 0 && x < m_fields.size(); x = x + jump)
					{
						if (possibleFieldConditionNotMet(direction, x, row, jump, player))
						{
							break;
						}
						else
						{
							//possible field found
							if (m_fields.at(x).getToken() == nullptr)
							{
								// normal = choose the field where tokens in most directions are changed
								if (player.getDifficulty() == Player::Difficulty::normal)
								{
									player.addPossibleFieldDuplicates(m_fields.at(x));
								}
								else
								{
									player.addPossibleField(m_fields.at(x));
								}
								break;
							}
						}
					}
				}
			}
		}
	}
}

bool Board::possibleFieldConditionNotMet(Direction direction, int index, int row, int jump, const Player& player)
{
	auto currentField = m_fields.at(index);
	// checks the previous field from the direction it's coming from
	auto previousField = m_fields.at(index - jump);

	switch (direction)
	{
	case Direction::right:
	case Direction::left:
		return (currentField.getPosition().getX() != row // searched through the whole row
				|| currentField.getToken() && currentField.getToken()->getColour() == player.getColour()); // enemy token is already surrounded by player tokens and can't be turned;
	case Direction::down:
	case Direction::up:
		return (currentField.getToken() && currentField.getToken()->getColour() == player.getColour()); // enemy token is already surrounded by player tokens and can't be turned;
	case Direction::rightUp:
	case Direction::leftDown:
		return (currentField.getPosition().getX() == previousField.getPosition().getX() // rows mustn't be the same
				|| currentField.getToken() && currentField.getToken()->getColour() == player.getColour()); // enemy token is already surrounded by player tokens and can't be turned;
	case Direction::leftUp:
		return (currentField.getPosition().getX() + 1 < previousField.getPosition().getX() // don't skip a row
				|| currentField.getToken() && currentField.getToken()->getColour() == player.getColour()); // enemy token is already surrounded by player tokens and can't be turned;
	case Direction::rightDown:
		return (currentField.getPosition().getX() > previousField.getPosition().getX() + 1 // don't skip a row
				|| currentField.getToken() && currentField.getToken()->getColour() == player.getColour()); // enemy token is already surrounded by player tokens and can't be turned;;
	default:
		return false;
	}
}

bool Board::reachedLastTokenToChange(Direction direction, int index, int row, int jump, const Position& position, const Player& player)
{
	switch (direction)
	{
	case Direction::right:
	case Direction::left:
		return (position.getX() != row); // reached end of row
	case Direction::rightUp:
	case Direction::leftDown:
		return (m_fields.at(index).getPosition().getX() == m_fields.at(index - jump).getPosition().getX()); // rows mustn't be the same
	case Direction::leftUp:
		return (m_fields.at(index).getPosition().getX() + 1 < m_fields.at(index - jump).getPosition().getX()); // don't skip a row
	case Direction::rightDown:
		return ((m_fields.at(index).getPosition().getX() > m_fields.at(index - jump).getPosition().getX() + 1)); // don't skip a row
	case Direction::down:
	case Direction::up:
	default:
		return false;
	}
}

void Board::addToken(Position position, Token::Colour colour)
{
	for (auto& field : m_fields)
	{
		if (field.getPosition() == position)
		{
			field.addToken(colour);
		}
	}
}

void Board::findTokensToChange(Position position, Token::Colour colour)
{
	int fieldIndex = getIndex(position);
	m_tokensToChange.clear();
	std::vector<Field> possibleTokensToChange;

	auto startIndex = static_cast<int>(Direction::right);
	auto endIndex = static_cast<int>(Direction::rightDown);

	for (int i = startIndex; i <= endIndex; ++i)
	{
		if (calcualteTokensToChange(fieldIndex, static_cast<Direction>(i), colour, possibleTokensToChange))
		{
			addTokensToChange(possibleTokensToChange);
		}

		possibleTokensToChange.clear();
	}

	changeTokenColour(colour);
}