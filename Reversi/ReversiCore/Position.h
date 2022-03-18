#pragma once

class Position
{
public:
	Position(size_t x, size_t y) : m_x(x), m_y(y) {}
	Position() : m_x(-1), m_y(-1) {}

	size_t getX() const { return m_x; }
	size_t getY() const { return m_y; }

	bool operator==(const Position& position) const { return (m_x == position.m_x && m_y == position.m_y); }
	bool operator!=(const Position& position) const { return !(*this == position); }
	bool operator<(const Position& position) const { return (m_x < position.m_x || m_x == position.m_x && m_y < position.m_y); }
	bool operator>(const Position& position) const { return !(*this < position); }
	void operator=(const Position& position) { m_x = position.m_x; m_y = position.m_y; }

private:
	size_t m_x;
	size_t m_y;
};

