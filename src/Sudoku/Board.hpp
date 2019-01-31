#ifndef GAME_SUDOKUBOARD_HPP_INCLUDEGUARD
#define GAME_SUDOKUBOARD_HPP_INCLUDEGUARD

#include <string>
#include <deque>
#include <vector>
#include <memory>
#include <iostream>
#include <iterator>
#include <algorithm>

#include "Cell.hpp"

class Board {
public:
	Board()
	{
		for (int i = 0; i != 9; ++i)
			for (int j = 0; j != 9; ++j)
			{
				auto c = std::make_shared<Cell>(i, j);
				m_cells.push_back(c);

				// add neighbors (line and row)
				for (int k = 0; k != 9; ++k)
				{
					c->addNeighbour(Coord{k,j});
					c->addNeighbour(Coord{ i,k });
				}


				// add neighbors (block)
				int ci = i / 3;
				int cj = j / 3;
				for (int ki = ci * 3; ki != (ci + 1) * 3; ++ki)
				{
					for (int kj = cj * 3; kj != (cj + 1) * 3; ++kj)
					{
						c->addNeighbour(Coord{ki,kj});
					}
				}
			}
	}

	void getSolution(Board& b)
	{
		// copy values
		for (int i = 0; i != 9; ++i)
		for (int j = 0; j != 9; ++j)
		{
			auto num = getCellAt(Coord{ i,j })->getValue();
			b.getCellAt(Coord{ i,j })->setValue(num);
		}

		b.fillBoard();
	}

	int getOpenFields()
	{
		int sum = 0;
		for (auto c : m_cells)
		{
			if (c->getValue() == 0)
				sum++;
		}
		return sum;
	}

	std::set<int> getNeighbourValues(Coord const& co)
	{
		std::set<int> ret;
		auto c = getCellAt(co);
		for (auto const co2 : c->getNeighbors())
		{
			auto c2 = getCellAt(co2);
			ret.insert(c2->getValue());
		}
		return ret;
	}

	auto begin() { return m_cells.begin(); }
	auto end() { return m_cells.end(); }

	std::shared_ptr<Cell> at(size_t idx) { return m_cells.at(idx); }


	void createPuzzle(size_t upTo = 10)
	{
		fillBoard();
		random_shuffle(m_cells.begin(), m_cells.end());
		std::deque<std::shared_ptr<Cell>> cells;
		for (size_t m = 0; m != upTo; ++m)
		{
			cells.push_back(m_cells.at(m));
		}
		
		std::deque<std::shared_ptr<Cell>> toTest;
		while (!cells.empty())
		{
			//std::cout << toTest.size() << std::endl;
			auto value = cells.front()->getValue();
			cells.front()->setValue(0);
			toTest.push_front(cells.front());

			if (getNumberOfSolutions(0,0,0) >= 2)
			{
				std::cout << "not unique anymore!\n";
				cells.front()->setValue(value);
				toTest.pop_front();
			}
			else
			{
				cells.front()->setValue(0);
				toTest.pop_front();
			}
			cells.pop_front();
		}
	}

	void clearBoard()
	{
		for (auto c : m_cells)
		{
			c->setValue(0);
		}

		std::sort(m_cells.begin(), m_cells.end(), [](auto c1, auto c2) { return c1->getPosition() < c2->getPosition(); });
	}

	void fillBoard ()
	{
		std::deque<std::shared_ptr<Cell>> cells;
		for (auto c : m_cells)
		{
			if(c->getValue() == 0)
				cells.push_back(c);	
		}
		doFillCell(cells, 0);
	}

	bool legal(std::shared_ptr<Cell> cell, int val)
	{
		std::set<int> nv = getNeighbourValues(cell->getPosition());
		bool b = std::find(nv.begin(), nv.end(), val) == nv.end();
		
		return b;
	}

	int getNumberOfSolutions(int i, int j, int count = 0)
	{
		//std::cout << i << " " << j << std::endl;
		if (i == 9)
		{
			i = 0;
			if (++j == 9)
			{
				return count + 1;
			}
		}
		std::shared_ptr<Cell> c = getCellAt({ i,j });
		if (c->getValue() != 0)
		{
			return getNumberOfSolutions(i + 1, j, count);
		}
		for (int val = 1; val <= 9 && count < 2; ++val) 
		{
			if (legal(c, val)) 
			{
				c->setValue(val);
				// add additional solutions
				count = getNumberOfSolutions(i + 1, j, count);
			}
		}
		c->setValue(0);
		return count;
	}


	int doFillCell(std::deque<std::shared_ptr<Cell>> remainingCells, int count = 0)
	{
		static std::set<int> const allValues = { 1,2,3,4,5,6,7,8,9 };

		std::shared_ptr<Cell> cell{ nullptr };
		while(true)
		{
			if (remainingCells.empty()) break;
			cell = remainingCells.front();
			remainingCells.pop_front();
			if (cell->getValue() == 0)
				break;
		}

		std::set<int> neighborValues = getNeighbourValues(cell->getPosition());
		std::vector<int> options;
		std::set_difference(allValues.begin(), allValues.end(),
			neighborValues.begin(), neighborValues.end(),
			std::inserter(options, options.begin())
		);
		random_shuffle(options.begin(), options.end());

		for (auto op : options)
		{
			if (cell != nullptr)
				cell->setValue(op);
			
			// all cells have been filled
			if (remainingCells.empty())
			{
				return count +1;
			}

			// go down recursively
			count = doFillCell(remainingCells, count);
			//std::cout << remainingCells.size() << " " << count << "\n";
			if (count != 0)
			{
				if (count >= 2)
					count = 2;

				return count;
			}
		}

		// this lead to a dead end
		// reset value and push it back to remaining cells
		cell->setValue(0);
		remainingCells.push_front(cell);
		return count;
	}

	std::shared_ptr<Cell> getCellAt(Coord const& coord) const
	{
		std::shared_ptr<Cell> ret{ nullptr };
		for (auto& c : m_cells)
		{
			if (c->getPosition() == coord)
			{
				ret = c;
				break;
			}
		}
		return ret;
	}
	std::vector<std::shared_ptr<Cell>> m_cells;

	void print()
	{
		int ci = 0;
		std::cout << "+--------+--------+--------+\n";
		for (int i = 0; i != 9; ++i)
		{

			int cj = 0;
			std::cout << "| ";
			for (int j = 0; j != 9; ++j)
			{
				
				auto c = getCellAt(Coord{ j,i });
				if (c->getValue() != 0)
					std::cout << c->getValue() << " ";
				else std::cout << "  ";
				cj++;
				if (cj % 3 == 0)
				{
					std::cout << " | ";
				}
			}
			ci++;
			if (ci % 3 == 0)
			{
				std::cout << "\n";
				std::cout << "+--------+--------+--------+";
			}
			std::cout << std::endl;
		}

		std::cout << std::endl;
	}
};


#endif
