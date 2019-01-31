#ifndef SERIALIZER_HPP_GUARD
#define SERIALIZER_HPP_GUARD
#include "Board.hpp"
#include "../JamTemplate/SplitString.hpp"
#include <string>


class Serializer
{
public:
	Serializer() = delete;

	static std::string Serialize( Board const& puzzle, Board const& solution)
	{
		std::string retVal = "";
		for (int i = 0; i != 9; ++i)
		for (int j = 0; j != 9; ++j)
		{
			auto px = puzzle.getCellAt({ i,j });
			auto v = px->getValue();
			if (v == 0)
			{
				auto sx = solution.getCellAt({ i,j });
				v = sx->getValue();
				retVal += "x";
			}
			retVal += std::to_string(v);
			retVal += ",";
		}
		return retVal;
	}

	static void Deserialize(std::string const& in, Board& puzzle, Board& solution)
	{
		JamTemplate::SplitString ss{ in };
		auto ssv = ss.split(',');
		size_t idx = 0;
		for (int i = 0; i != 9; ++i)
		for (int j = 0; j != 9; ++j)
		{
			std::string t = ssv[idx];
			if (t.at(0) == 'x')
			{
				puzzle.getCellAt({ i,j })->setValue(0);
				int v = std::stoi(t.substr(1));
				solution.getCellAt({ i,j })->setValue(v);
			}
			else
			{
				int v = std::stoi(t);
				puzzle.getCellAt({ i,j })->setValue(v);
				solution.getCellAt({ i,j })->setValue(v);
			}
			idx++;
		}
	}
};

#endif
