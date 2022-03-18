#include "Field.h"

bool Field::operator==(const Field& field) const 
{ 
	if (m_position != field.m_position)
	{
		return false;
	}
	
	if (!m_token && field.m_token || m_token && !field.m_token)
	{
		return false;
	}
	
	if( m_token && field.m_token && *m_token != *field.m_token)
	{ 
		return false;
	}

	return true; 
}

void Field::operator=(const Field& field)
{
	m_position = field.m_position;
	m_token = field.m_token;
}

void Field::addToken(Token::Colour colour)
{
	m_token = std::shared_ptr<Token>(new Token(m_position.getX(), m_position.getY(), colour));
}