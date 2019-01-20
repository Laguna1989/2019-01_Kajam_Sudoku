#include "StateMenu.hpp"
#include "JamTemplate/Game.hpp"
#include "JamTemplate/TextureManager.hpp"
#include "StateGameOnePlayer.hpp"
#include "StateGameTwoPlayer.hpp"
#include "GameProperties.hpp"
#include "JamTemplate/SmartText.hpp"
#include "JamTemplate/SmartShape.hpp"


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
	createImages();

	float w = static_cast<float>(getGame()->getRenderTarget()->getSize().x);
	float h = static_cast<float>(getGame()->getRenderTarget()->getSize().y);
	float wC = w / 2;

	m_background = std::make_shared < JamTemplate::SmartShape>();
	m_background->makeRect({ w,h });
	m_background->setColor(GP::PaletteBackground());
	m_background->update(0.0f);

	m_text_Title = std::make_shared<JamTemplate::SmartText>();
	m_text_Title->loadFont("assets/font.ttf");
	m_text_Title->setCharacterSize(32U);
	m_text_Title->setText("VsSudoku");
	m_text_Title->setPosition({ wC, 20});
	m_text_Title->setColor(sf::Color{ 248, 249, 254 });
	m_text_Title->update(0.0f);

	m_text_1P = std::make_shared<JamTemplate::SmartText>();
	m_text_1P->loadFont("assets/font.ttf");
	m_text_1P->setCharacterSize(16U);
	m_text_1P->setText("Single Player");
	m_text_1P->setPosition({ wC - 200, 100 });
	m_text_1P->setColor(sf::Color{ 248, 249, 254 });
	m_text_1P->update(0.0f);

	m_text_2P = std::make_shared<JamTemplate::SmartText>();
	m_text_2P->loadFont("assets/font.ttf");
	m_text_2P->setCharacterSize(16U);
	m_text_2P->setText("Versus Mode");
	m_text_2P->setPosition({ wC+ 200, 100 });
	m_text_2P->setColor(sf::Color{ 248, 249, 254 });
	m_text_2P->update(0.0f);
}
void StateMenu::doInternalDraw() const
{
	m_background->draw(getGame()->getRenderTarget());
	m_text_Title->draw(getGame()->getRenderTarget());
	m_text_1P->draw(getGame()->getRenderTarget());
	m_text_2P->draw(getGame()->getRenderTarget());
}






void StateMenu::createImages()
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