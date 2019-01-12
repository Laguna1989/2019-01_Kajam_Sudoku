#ifndef GAME_CELL_HPP_INCLUDEGUARD
#define GAME_CELL_HPP_INCLUDEGUARD

#include <string>
#include <set>

#include "Coord.hpp"

class Cell
{
public:
	Cell(int i, int j) : m_pos{ Coord{i,j} }
	{
	}
	
	Coord const getPosition() const { return m_pos; }
	void setPosition(Coord c) { m_pos = c; }

	void setValue(unsigned int v) { m_value = v; }
	unsigned int const getValue() const { return m_value; }

	void addNeighbour(Coord c)
	{
		if (c == getPosition()) return;
		m_neighbors.insert(c);
	}
	std::set<Coord> getNeighbors()
	{
		return m_neighbors;
	}
private:
	Coord m_pos;
	std::set<Coord> m_neighbors;
	unsigned int m_value{ 0 };
};
#endif
