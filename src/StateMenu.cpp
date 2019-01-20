#include "StateMenu.hpp"
#include "JamTemplate/Game.hpp"
#include "JamTemplate/TextureManager.hpp"
#include "StateGameOnePlayer.hpp"
#include "StateGameTwoPlayer.hpp"
#include "GameProperties.hpp"


StateMenu::StateMenu() = default;
void StateMenu::doInternalUpdate(float const /*elapsed*/)
{
	//if (getAge() >= 0.25)
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
	{
		getGame()->switchState(std::make_shared<StateGameOnePlayer>());
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::B))
	{
		getGame()->switchState(std::make_shared<StateGameTwoPlayer>());
	}
}
void StateMenu::doCreate()
{

	sf::Color bright = sf::Color{ 54, 98, 147 };
	sf::Color dark = sf::Color{ 38, 69, 104 };

	sf::Image img{};
	img.create(static_cast<unsigned int>(GP::CellPositionSpacing() * 9), static_cast<unsigned int>(GP::CellPositionSpacing() * 9), bright);

	for (int p = 0; p != 3; ++p)
	{
		int min = static_cast<int>(GP::CellPositionSpacing() * 3 * p);
		int max = static_cast<int>(GP::CellPositionSpacing() * 3 * (p + 1));
		for (int i = min; i != max; ++i)
			for (int j = min; j != max; ++j)
			{
				unsigned int x = i;
				unsigned int y = j;
				img.setPixel(x, y, dark);

			}
	}
	{
		int minX = static_cast<int>(0);
		int maxX = static_cast<int>(GP::CellPositionSpacing() * 3);

		int minY = static_cast<int>(GP::CellPositionSpacing() * 3 * 2);
		int maxY = static_cast<int>(GP::CellPositionSpacing() * 3 * 3);

		for (int i = minX; i != maxX; ++i)
			for (int j = minY; j != maxY; ++j)
			{
				unsigned int x = i;
				unsigned int y = j;
				img.setPixel(x, y, dark);

			}


		for (int i = minY; i != maxY; ++i)
			for (int j = minX; j != maxX; ++j)
			{
				unsigned int x = i;
				unsigned int y = j;
				img.setPixel(x, y, dark);

			}
	}



	sf::Texture t{};
	t.loadFromImage(img);
	JamTemplate::TextureManager::addTexture("__gameboard", t);
}