#pragma once
#include <vector>
#include <string>
#include "Token.h"
#include "Field.h"

class Board;

class Player
{
public:
	enum class Difficulty
	{
		none, // player
		easy, // CPU, random fields
		normal, // CPU, field that turns in most directions
		hard, // CPU, field that turns most tokens
	};

	Player(Token::Colour colour) : m_colour(colour), m_difficulty(Difficulty::none) {}
	Player(Token::Colour colour, Difficulty difficulty) : m_colour(colour), m_difficulty(difficulty) {}

	void clearPossibleFields() { m_possibleFields.clear(); }
	void clearOccupiedFields() { m_occupiedFields.clear(); }
	void addPossibleField(Field field);
	void addPossibleFieldDuplicates(Field field);
	Token::Colour getColour() const { return m_colour; }
	void addOccupiedField(Field field) { m_occupiedFields.push_back(field); }
	void eraseOccupiedField(Field field);
	std::string getPlayerName() const { return m_colour == Token::Colour::blue ? "o" : "x"; }
	const std::vector<Field> &getPossibleFields() { return m_possibleFields; }
	const std::vector<Field>& getOccupiedFields() { return m_occupiedFields; }
	bool containsField(size_t x, size_t y);
	void sortPossibleFields();
	void setDifficulty(Difficulty difficulty) { m_difficulty = difficulty; }
	Difficulty getDifficulty() const { return m_difficulty; }

	// for CPU
	Position selectPossibleField(const Board& board);

private:
	// for CPU
	Position selectRandomPossibleField();
	Position selectPossibleFieldMostDirections();
	Position selectPossibleFieldMostTokens(const Board& originalBoard);

	Token::Colour m_colour;
	Difficulty m_difficulty;
	std::vector<Field> m_occupiedFields;
	std::vector<Field> m_possibleFields;
};

