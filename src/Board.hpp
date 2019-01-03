#ifndef GAME_BOARD_HPP_INCLUDEGUARD
#define GAME_BOARD_HPP_INCLUDEGUARD

#include <string>
#include <deque>
#include <vector>
#include <memory>
#include <iostream>
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


	void createPuzzle(int upTo = 80)
	{
		if (upTo > m_cells.size())
		{
			throw std::exception{};
		}
		fillBoard();
		random_shuffle(m_cells.begin(), m_cells.end());
		std::deque<std::shared_ptr<Cell>> cells;
		for (int m = 0; m != upTo; ++m)
		{
			cells.push_back(m_cells.at(m));
		}
		
		std::deque<std::shared_ptr<Cell>> toTest;
		while (!cells.empty())
		{
			std::cout << toTest.size() << std::endl;
			auto value = cells.front()->getValue();
			cells.front()->setValue(0);
			toTest.push_front(cells.front());

			if (doFillCell(toTest, 0) == 2)
			{
				std::cout << "not unique anymore!\n";
				cells.front()->setValue(value);
				toTest.pop_front();
			}
			cells.pop_front();

		}



	}


	void fillBoard ()
	{
		std::deque<std::shared_ptr<Cell>> cells;
		for (auto c : m_cells)
		{
			cells.push_back(c);
		}
		doFillCell(cells, 0);
	}


	int doFillCell(std::deque<std::shared_ptr<Cell>> remainingCells, int value = 0)
	{
		static std::set<int> const allValues = { 1,2,3,4,5,6,7,8,9 };


		auto cell = remainingCells.front();
		remainingCells.pop_front();

		std::set<int> neighborValues = getNeighbourValues(cell->getPosition());
		std::vector<int> options;
		std::set_difference(allValues.begin(), allValues.end(),
			neighborValues.begin(), neighborValues.end(),
			std::inserter(options, options.begin())
		);
		random_shuffle(options.begin(), options.end());

		for (auto op : options)
		{
			cell->setValue(op);
			
			// all cells have been filled
			if (remainingCells.empty())
			{
				value += 1;
				

				return value;
			}
				

			// go down recursively
			value = doFillCell(remainingCells, value);
			if (value != 0)
			{
				if (value >= 2)
					return 2;
			}
		}

		// this lead to a dead end
		// reset value and push it back to remaining cells
		cell->setValue(0);
		remainingCells.push_front(cell);
		return value;
	}

	std::shared_ptr<Cell> getCellAt(Coord const& coord)
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
