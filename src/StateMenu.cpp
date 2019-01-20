#include "StateMenu.hpp"
#include "JamTemplate/Game.hpp"
#include "JamTemplate/TextureManager.hpp"
#include "StateGameOnePlayer.hpp"
#include "StateGameTwoPlayer.hpp"
#include "GameProperties.hpp"
#include "JamTemplate/SmartText.hpp"
#include "JamTemplate/SmartShape.hpp"
#include "JamTemplate/TweenScale.hpp"


StateMenu::StateMenu() = default;
void StateMenu::doInternalUpdate(float const /*elapsed*/)
{
	using ip = JamTemplate::InputManager;
	if (ip::justPressed(sf::Keyboard::Key::Space) || ip::justPressed(sf::Keyboard::Key::Return))
	{
		if (m_modeSelect == false)
		{
			getGame()->switchState(std::make_shared<StateGameOnePlayer>());
		}
		else
		{
			getGame()->switchState(std::make_shared<StateGameTwoPlayer>());
		}
	}
	
	if (ip::justPressed(sf::Keyboard::Key::A) || ip::justPressed(sf::Keyboard::Key::Left))
	{
		if (m_modeSelect == true)
			switchToLeft();
	}
	if (ip::justPressed(sf::Keyboard::Key::D) || ip::justPressed(sf::Keyboard::Key::Right))
	{
		if (m_modeSelect == false)
			switchToRight();
	}
}

void StateMenu::switchToLeft()
{
	m_modeSelect = false;
	using ts = JamTemplate::TweenScale<JamTemplate::SmartText>;
	auto twl = ts::create(m_text_1P, 0.1f, m_text_1P->getScale(), { 1.5f,1.5f });
	add(twl);

	auto twr = ts::create(m_text_2P, 0.1f, m_text_2P->getScale(), { 1.0f,1.0f });
	add(twr);

}
void StateMenu::switchToRight()
{
	m_modeSelect = true;

	using ts = JamTemplate::TweenScale<JamTemplate::SmartText>;
	auto twl = ts::create(m_text_2P, 0.1f, m_text_2P->getScale(), { 1.5f,1.5f });
	add(twl);

	auto twr = ts::create(m_text_1P, 0.1f, m_text_1P->getScale(), { 1.0f,1.0f });
	add(twr);
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
	m_text_Title->SetTextAlign(JamTemplate::SmartText::TextAlign::CENTER);

	m_text_1P = std::make_shared<JamTemplate::SmartText>();
	m_text_1P->loadFont("assets/font.ttf");
	m_text_1P->setCharacterSize(16U);
	m_text_1P->setText("Single Player");
	m_text_1P->setPosition({ wC - 200, 150 });
	m_text_1P->setColor(sf::Color{ 248, 249, 254 });
	m_text_1P->update(0.0f);
	m_text_1P->SetTextAlign(JamTemplate::SmartText::TextAlign::CENTER);

	m_text_2P = std::make_shared<JamTemplate::SmartText>();
	m_text_2P->loadFont("assets/font.ttf");
	m_text_2P->setCharacterSize(16U);
	m_text_2P->setText("Versus Mode");
	m_text_2P->setPosition({ wC+ 200, 150 });
	m_text_2P->setColor(sf::Color{ 248, 249, 254 });
	m_text_2P->update(0.0f);
	m_text_2P->SetTextAlign(JamTemplate::SmartText::TextAlign::CENTER);

	switchToLeft();
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