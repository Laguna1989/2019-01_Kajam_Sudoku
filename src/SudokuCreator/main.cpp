#include "../Sudoku/Board.hpp"
#include "../Sudoku/Serializer.hpp"

#include <iostream>
#include <fstream>
#include <map>
#include <random>

constexpr long N = 2000;

int main()
{
	std::map<int, std::string> saved;

	std::default_random_engine dre;
	std::uniform_int_distribution<int> dist(5,50);

	 //create puzzles
	for (long i = 0; i != N; ++i)
	{
		 
		std::cout << i << " ";
		Board b{};
		b.createPuzzle(dist(dre));
		auto of = b.getOpenFields();
		std::cout << of << std::endl;
		Board s{};
		b.getSolution(s);
		saved[of] += Serializer::Serialize(b, s) + "\n";
	}
	// save puzzles
	for (auto kvp = saved.begin(); kvp != saved.end(); ++kvp)
	{
		int of = kvp->first;

		std::string fn = "assets/p_" + std::to_string(of) + ".puz";
		std::ofstream out(fn);

		out << kvp->second << "\n";
	}

	std::ifstream in("assets/p_49.puz");
	std::string str;
	while (std::getline(in, str))
	{
		if (str.length() < 5) continue;

		Board p{};
		Board s{};
		Serializer::Deserialize(str, p, s);
		p.print();
	}

}
