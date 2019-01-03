#include <SFML/Graphics.hpp>
#include "JamTemplate/Game.hpp"

#include "StateMenu.hpp"

#include "Board.hpp"

int main()
{

	Board b{};
	b.print();
	b.fillBoard();

	std::cout << "filled\n";
	Board b2{};
	std::deque<std::shared_ptr<Cell>> toFill;
	for (int i = 0; i != 9; ++i)
		for (int j = 0; j != 9; ++j)
		{
			Coord c{ i,j };
			if ((i == 5 && j == 5)  || (i == 5 && j == 4))
			{
				toFill.push_back(b2.getCellAt(c));
				continue;
			}
			b2.getCellAt(c)->setValue(b.getCellAt(c)->getValue());
		}
	std::cout << b2.doFillCell(toFill) << std::endl;


	return 0;



	JamTemplate::Game::Sptr game = std::make_shared<JamTemplate::Game>();
	game->setUp(800, 600, 4, "SFML works!");

	auto window = game->getRenderWindow();
	auto renderTexture = game->getRenderTarget();
	auto view = game->getView();

	game->switchState(std::make_shared<StateMenu>());
	sf::Clock clock;

	


	while (window->isOpen())
	{
		sf::Time elapsed = clock.restart();
		sf::Event event;
		while (window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window->close();
		}		
		game->update(elapsed.asSeconds());
		game->draw();
	}

	return 0;
}
