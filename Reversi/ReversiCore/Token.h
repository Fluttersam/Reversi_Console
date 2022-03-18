#pragma once
#include "Position.h"

class Token
{
public:
	enum class Colour
	{
		green,
		blue,
	};

	Token(size_t x, size_t y, Colour colour) : m_position(x, y), m_colour(colour) {}
	Position getPosition() const { return m_position; }
	Colour getColour() const { return m_colour; }
	void changeColour(Token::Colour colour) { m_colour = colour; }

	bool operator==(const Token& token) const { return (m_colour == token.m_colour && m_position == token.m_position); }
	bool operator!=(const Token& token) const { return !(*this == token); }
	void operator=(const Token& token) { m_colour = token.m_colour; m_position = token.m_position; }

private:
	Colour m_colour;
	Position m_position;
};

