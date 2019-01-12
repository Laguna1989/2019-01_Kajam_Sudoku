#ifndef GAME_STATE_MENU_HPP_INCLUDEGUARD
#define GAME_STATE_MENU_HPP_INCLUDEGUARD

#include <iostream>
#include "JamTemplate/GameState.hpp"
#include "JamTemplate/Game.hpp"
#include "JamTemplate/TextureManager.hpp"
#include "StateGame.hpp"
class StateMenu : public JamTemplate::GameState {
public:
	StateMenu() = default;
private:
	void doInternalUpdate (float const /*elapsed*/) override 
	{
		//if (getAge() >= 0.25)
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
		{
			getGame()->switchState(std::make_shared<StateGame>());
		}
		
	}
	void doCreate()
	{

		sf::Color bright = sf::Color{ 180,180,180 };
		sf::Color dark = sf::Color{ 130,130,130 };

		sf::Image img{};
		img.create(static_cast<unsigned int>(GP::CellPositionSpacing() * 9), static_cast<unsigned int>(GP::CellPositionSpacing() * 9), bright);
		
		for (int p = 0; p != 3; ++p)
		{
			int min = GP::CellPositionSpacing() * 3 *p;
			int max = GP::CellPositionSpacing() * 3 * (p+1);
			for (int i = min; i != max; ++i)
			for (int j = min; j != max; ++j)
			{
				unsigned int x = i;
				unsigned int y = j;
				img.setPixel(x, y, dark);

			}
		}
		{
			int minX = 0;
			int maxX = GP::CellPositionSpacing() * 3;

			int minY = GP::CellPositionSpacing()* 3 * 2;
			int maxY = GP::CellPositionSpacing()* 3 * 3;
			
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
};

#endif
