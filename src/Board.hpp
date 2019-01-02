#ifndef GAME_BOARD_HPP_INCLUDEGUARD
#define GAME_BOARD_HPP_INCLUDEGUARD

#include <string>
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

	void fillBoard ()
	{
		std::set<int> allValues = {1,2,3,4,5,6,7,8,9};
		for (auto cell : m_cells) 
		{
			std::set<int> neighborValues = getNeighbourValues(cell->getPosition());

			std::vector<int> options;
			std::set_difference(allValues.begin(), allValues.end(),
				neighborValues.begin(), neighborValues.end(),
				std::inserter(options, options.begin())
			);
			if (options.empty()) break;
			std::random_shuffle(options.begin(), options.end());
			cell->setValue(options[0]);
		}

		print();
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
