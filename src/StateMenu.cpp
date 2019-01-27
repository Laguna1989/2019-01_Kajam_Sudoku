#include "StateMenu.hpp"
#include "JamTemplate/Game.hpp"
#include "JamTemplate/TextureManager.hpp"
#include "StateGameOnePlayer.hpp"
#include "StateGameTwoPlayer.hpp"
#include "GameProperties.hpp"
#include "JamTemplate/SmartText.hpp"
#include "JamTemplate/SmartShape.hpp"
#include "JamTemplate/TweenScale.hpp"
#include "JamTemplate/TweenAlpha.hpp"
#include "JamTemplate/TweenPosition.hpp"


StateMenu::StateMenu() = default;
void StateMenu::doInternalUpdate(float const elapsed)
{
	if (m_starting == false)
	{
		using ip = JamTemplate::InputManager;
		if (ip::justPressed(sf::Keyboard::Key::Space) || ip::justPressed(sf::Keyboard::Key::Return))
		{
			if (m_modeSelect == false)
			{
				m_starting = true;
				auto tw = JamTemplate::TweenAlpha<JamTemplate::SmartShape>::create(m_overlay, 0.5f, sf::Uint8{ 0 }, sf::Uint8{ 255 });
				tw->setSkipFrames();
				tw->addCompleteCallback([this]() {getGame()->switchState(std::make_shared<StateGameOnePlayer>());  });
				add(tw);
			}
			else
			{
				m_starting = true;

				auto tw = JamTemplate::TweenAlpha<JamTemplate::SmartShape>::create(m_overlay, 0.5f, sf::Uint8{ 0 }, sf::Uint8{ 255 });
				tw->setSkipFrames();
				tw->addCompleteCallback([this]() {getGame()->switchState(std::make_shared<StateGameTwoPlayer>());  });
				add(tw);
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

		if (ip::justPressed(sf::Keyboard::Up) || ip::justPressed(sf::Keyboard::W))
		{
			increaseDifficulty();
		}
		if (ip::justPressed(sf::Keyboard::Down) || ip::justPressed(sf::Keyboard::S))
		{
			decreaseDifficulty();
		}

		m_text_Title->update(elapsed);
		m_text_Difficulty->update(elapsed);
		m_text_1P->update(elapsed);
		m_text_2P->update(elapsed);
	}
	else
	{

	}
}

void StateMenu::increaseDifficulty()
{
	if (GP::getDifficulty() == GP::DifficultyEnum::EASY)
		GP::setDifficulty(GP::DifficultyEnum::MEDIUM);
	else if (GP::getDifficulty() == GP::DifficultyEnum::MEDIUM)
		GP::setDifficulty(GP::DifficultyEnum::HARD);
	updateDifficultyString();
	m_text_Difficulty->flash(0.35f, GP::PaletteFlashRed());
}

void StateMenu::decreaseDifficulty()
{
	if (GP::getDifficulty() == GP::DifficultyEnum::HARD)
		GP::setDifficulty(GP::DifficultyEnum::MEDIUM);
	else if (GP::getDifficulty() == GP::DifficultyEnum::MEDIUM)
		GP::setDifficulty(GP::DifficultyEnum::EASY);
	updateDifficultyString();
	m_text_Difficulty->flash(0.35f, GP::PaletteFlashGreen());
}

void StateMenu::updateDifficultyString()
{
	m_text_Difficulty->setText(GP::Difficulty2String(GP::getDifficulty()));
	m_text_Difficulty->update(0.0f);
	
	
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

	
	m_text_Difficulty = std::make_shared<JamTemplate::SmartText>();
	m_text_Difficulty->loadFont("assets/font.ttf");
	m_text_Difficulty->setCharacterSize(16U);
	m_text_Difficulty->setText("Medium");
	m_text_Difficulty->setPosition({ wC, 200 });
	m_text_Difficulty->setColor(sf::Color{ 248, 249, 254 });
	m_text_Difficulty->SetTextAlign(JamTemplate::SmartText::TextAlign::CENTER);
	m_text_Difficulty->update(0.0f);

	m_text_Credits = std::make_shared<JamTemplate::SmartText>();
	m_text_Credits->loadFont("assets/font.ttf");
	m_text_Credits->setCharacterSize(12U);
	m_text_Credits->setText("Created by @Laguna_999 for #kajam\nJanuary 2019");
	m_text_Credits->setPosition({ 10, 310 });
	m_text_Credits->setColor(sf::Color{ 248, 249, 254 });
	m_text_Credits->SetTextAlign(JamTemplate::SmartText::TextAlign::LEFT);
	m_text_Credits->update(0.0f);
	switchToLeft();


	m_overlay = std::make_shared<JamTemplate::SmartShape>();
	m_overlay->makeRect(sf::Vector2f{ w,h });
	m_overlay->setColor(sf::Color{ 0,0,0 });
	m_overlay->update(0);
	
	{
		auto tw = JamTemplate::TweenAlpha<JamTemplate::SmartShape>::create(m_overlay, 0.5f, sf::Uint8{ 255 }, sf::Uint8{ 0 });
		tw->setSkipFrames();
		add(tw);
	}
	using tp = JamTemplate::TweenPosition<JamTemplate::SmartText>;
	using ta = JamTemplate::TweenAlpha<JamTemplate::SmartText>;
	{
		
		/*auto tw1 = tp::create(m_text_Title, 0.25f, (m_text_Title->getPosition() + sf::Vector2f{ 0,-100 }), m_text_Title->getPosition());
		tw1->setStartDelay(0.1f);
		tw1->setSkipFrames();
		add(tw1);*/

		auto ta1 = ta::create(m_text_Title, 0.25f, 0, 255);
		ta1->setStartDelay(0.2f);
		ta1->setSkipFrames();
		add(ta1);
	}
	{
		auto ta2 = ta::create(m_text_Difficulty, 0.25f, 0, 255);
		ta2->setStartDelay(0.8f);
		ta2->setSkipFrames();
		add(ta2);
	}
	{
		auto s2 = m_text_1P->getPosition() + sf::Vector2f{ -300,0 };
		auto e2 = m_text_1P->getPosition();

		auto tw2 = tp::create(m_text_1P, 0.35f, s2, e2);
		tw2->setStartDelay(0.3f);
		tw2->setSkipFrames();
		add(tw2);
	}
	{
		auto s3 = m_text_2P->getPosition() + sf::Vector2f{ 300,0 };
		auto e3 = m_text_2P->getPosition();
		
		auto tw3 = tp::create(m_text_2P, 0.35f, s3, e3);
		tw3->setStartDelay(0.4f);
		tw3->setSkipFrames();
		add(tw3);
	}


}
void StateMenu::doInternalDraw() const
{
	m_background->draw(getGame()->getRenderTarget());

	float w = static_cast<float>(getGame()->getRenderTarget()->getSize().x);
	float wC = w / 2;

	m_text_Title->setPosition({ wC + 2, 20 + 2 });
	m_text_Title->setColor(GP::PaletteFontShadow());
	m_text_Title->update(0.0f);
	m_text_Title->draw(getGame()->getRenderTarget());


	m_text_Title->setPosition({ wC, 20 });
	m_text_Title->setColor(GP::PaletteFontFront());
	m_text_Title->update(0.0f);
	m_text_Title->draw(getGame()->getRenderTarget());	
	
	m_text_1P->draw(getGame()->getRenderTarget());
	m_text_2P->draw(getGame()->getRenderTarget());
	m_text_Difficulty->draw(getGame()->getRenderTarget());
	m_text_Credits->draw(getGame()->getRenderTarget());
	m_overlay->draw(getGame()->getRenderTarget());
	
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