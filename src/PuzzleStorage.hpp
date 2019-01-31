#ifndef _GAME_VSSUDOKU_PUZZLESTORAGE_INCLUDEGUARD_HPP
#define _GAME_VSSUDOKU_PUZZLESTORAGE_INCLUDEGUARD_HPP

#include "Sudoku/Serializer.hpp"

#include <vector>
#include <map>
#include <string>
#include <fstream>
#include <ctime>

#include "GameProperties.hpp"

class PuzzleStorage
{
public:
	std::map<int, std::vector<std::string>> m_allPuzzles;
	int minLevel{ 5 };
	int maxLevel{ 50 };

	PuzzleStorage()
	{
		size_t N = GP::GameBoardMaxParse();
		//std::cout << "loading puzzles";
		std::srand( static_cast<unsigned int>(std::time(0)) );	// seed it correctly
		
		if (GP::getDifficulty() == GP::DifficultyEnum::EASY)
		{
			minLevel = 5;
			maxLevel = 20;
		}
		else if (GP::getDifficulty() == GP::DifficultyEnum::MEDIUM)
		{
			minLevel = 21;
			maxLevel = 35;
		}
		else if (GP::getDifficulty() == GP::DifficultyEnum::HARD)
		{
			minLevel = 36;
			maxLevel = 50;
		}

		for (int i = minLevel; i != maxLevel; ++i)
		{
			
			std::string fn = "assets/p_" + std::to_string(i) + ".puz";
			std::ifstream in(fn);
			if (in.fail())
			{
				std::cerr << "error, cannot load puzzle file:  " << fn << " . Please run SudokuCreatror!" << std::endl;
				//throw std::exception("cannot load sudoku file.");
			}
			std::string str;
			//std::cout <<  fn <<"\n";
			size_t count = 0;
			while (std::getline(in, str))
			{

				if (str.length() < 5) continue;

				
				Board p{};
				Board s{};
				Serializer::Deserialize(str, p, s);
				if (p.getNumberOfSolutions(0, 0, 0) == 1)
				{
					m_allPuzzles[i].push_back(str);
					count++;
				}
				if (count >= N) break;
			}
			std::random_shuffle(m_allPuzzles[i].begin(), m_allPuzzles[i].end());
		}
		std::cout << " done with N= "  << m_allPuzzles.size() << "\n";
	}

	std::vector<std::string> getPuzzleList(bool firstPlayer = true)
	{
		std::vector<std::string> retVal;
		for (int i = minLevel; i != maxLevel; ++i)
		{
			auto size = m_allPuzzles[i].size();
			
			for (size_t j = 0; j != size /2-1; ++j)
			{
				size_t ofs = firstPlayer ? 0 : size / 2;
				retVal.push_back(m_allPuzzles[i][j + ofs]);
			}
		}
		//std::cout << "randomize puzzles\n";
		std::random_shuffle(retVal.begin(), retVal.end());
		return retVal;
	}
};

#endif
