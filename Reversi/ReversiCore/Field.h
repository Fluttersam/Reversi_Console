#pragma once
#include <memory>
#include "Token.h"

class Field
{
public:

	Field() : m_position(100, 100) {}
	Field(size_t x, size_t y) : m_position(x, y) {}
	Field(size_t x, size_t y, Token::Colour colour) : m_position(x, y) 
	{
		m_token = std::shared_ptr<Token>(new Token(x, y, colour));
	}

	bool operator==(const Field& field) const; 
	bool operator != (const Field& field) const { return !(*this == field); }
	bool operator<(const Field& field) const { return m_position < field.m_position; }
	bool operator>(const Field& field) const { return !(*this < field); }
	void operator=(const Field& field);

	Token *getToken() const { return m_token.get(); }
	Position getPosition() const { return m_position; }
	void addToken(Token::Colour colour);

private:
	Position m_position;
	std::shared_ptr<Token> m_token;
};

