#pragma once
#include <vector>
#include "Field.h"
#include "Token.h"
#include "Player.h"


class Board
{
public:
	enum class Direction
	{
		right,
		left,
		down,
		up,
		rightUp,
		leftDown,
		leftUp,
		rightDown
	};

	Board() {}
	Board (const Board& board);
	void initBoard();
	void drawBoard();
	void calculatePossibleFields(Player& player);
	void calculateOccupiedFields(Player& player);
	void placeToken(Position position, Token::Colour colour);
	int getNumberOfEmptyFields();
	void setUpBoard(std::string board);
	void saveBoard();
	void loadBoard();
	void resetBoard();
	void copyBoard(const Board& board);

	std::vector<Field>& getFields() { return m_fields; };

private:
	bool drawstartTokens(size_t x, size_t y);
	void addTokensToChange(std::vector<Field> tokensToChange);
	void changeTokenColour(Token::Colour colour);
	int getIndex(Position position);
	bool addPossibleTokensToChange(int index, Token::Colour colour, std::vector<Field>& possibleTokensToChange);
	bool calcualteTokensToChange(const int fieldIndex, Direction direction, Token::Colour colour, std::vector<Field>& possibleTokensToChange);
	const int indexToMove(Direction direction);
	void calculatePossibleFields(Player& player, Direction direction);
	bool possibleFieldConditionNotMet(Direction direction, int index, int row, int jump, const Player& player);
	bool reachedLastTokenToChange(Direction direction, int index, int row, int jump, const Position& position, const Player& player);

	void addToken(Position position, Token::Colour colour);
	void findTokensToChange(Position position, Token::Colour colour);

	std::vector<Field> m_fields;
	std::vector<Field> m_tokensToChange;
	const size_t BOARD_SIZE = 8;

	const int ROW_INDEX_JUMP = 1;
	const int COLUMN_INDEX_JUMP = 8;
	const int LEFT_TOP_BOTTOM_RIGHT_JUMP = 9;
	const int RIGHT_TOP_BOTTOM_LEFT_JUMP = 7;

	const std::vector<Token> m_startTokens{ {4,4,Token::Colour::blue}, {4,5,Token::Colour::green},
										{5,4,Token::Colour::green}, {5,5,Token::Colour::blue} };

	std::string m_savedBoard;
};

