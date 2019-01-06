#ifndef GAME_BOARD_GUARD_HPP 
#define  GAME_BOARD_GUARD_HPP

#include <memory>
#include <string>

#include "JamTemplate/GameObject.hpp"
#include "JamTemplate/SmartText.hpp"
#include "JamTemplate/SmartShape.hpp"

#include "Board.hpp"
#include "GameProperties.hpp"


class GameBoard : public JamTemplate::GameObject
{
public:
	using Sptr = std::shared_ptr<GameBoard>;

	
private:
	mutable Board m_board;
	Board m_boardFull;

	mutable JamTemplate::SmartText m_text;

	JamTemplate::SmartShape::Sptr m_selector;
	
	int m_selectorX{ 0 };
	int m_selectorY{ 0 };

	sf::Vector2f positionFromCoord(int x, int y) const
	{
		return sf::Vector2f {
					GP::CellPositionOffsetX() + x * GP::CellPositionSpacing(),
					GP::CellPositionOffsetY() + y * GP::CellPositionSpacing() };
	}

	virtual void doUpdate(float const elapsed) override
	{
		m_text.update(elapsed);
		
		updateSelector(elapsed);
		updateNumbers(elapsed);
	};


	void updateNumbers(float elapsed)
	{
		auto c = m_board.getCellAt(Coord{ m_selectorX,m_selectorY });

		if (c->getValue() != 0)
			return;

		auto cc = m_boardFull.getCellAt(Coord{ m_selectorX,m_selectorY });

		//std::cout << "at emply place: " << cc->getValue() << "\n";
		int num = 0;
		if (JamTemplate::InputManager::justPressed(sf::Keyboard::Key::Num1))
			num = 1;
		else if (JamTemplate::InputManager::justPressed(sf::Keyboard::Key::Num2))
			num = 2;
		else if (JamTemplate::InputManager::justPressed(sf::Keyboard::Key::Num3))
			num = 3;
		else if (JamTemplate::InputManager::justPressed(sf::Keyboard::Key::Num4))
			num = 4;
		else if (JamTemplate::InputManager::justPressed(sf::Keyboard::Key::Num5))
			num = 5;
		else if (JamTemplate::InputManager::justPressed(sf::Keyboard::Key::Num6))
			num = 6;
		else if (JamTemplate::InputManager::justPressed(sf::Keyboard::Key::Num7))
			num = 7;
		else if (JamTemplate::InputManager::justPressed(sf::Keyboard::Key::Num8))
			num = 8;
		else if (JamTemplate::InputManager::justPressed(sf::Keyboard::Key::Num9))
			num = 9;
		if (num == 0) return;
			
		std::cout << "placing value: " << num << std::endl;
		if (cc->getValue() == num)
		{
			placeCorrectValue(c, num);
		}
		else
		{
			placeWrongValue();
		}
	}

	void placeCorrectValue(std::shared_ptr<Cell> c, int num)
	{
		c->setValue(num);
	}
	void placeWrongValue()
	{

	}

	void updateSelector(float elapsed)
	{
		std::cout << m_selectorX << " " << m_selectorY << "\n";
		if (
			JamTemplate::InputManager::justPressed(sf::Keyboard::Key::A) || 
			JamTemplate::InputManager::justPressed(sf::Keyboard::Key::Left))
		{
			m_selectorX--;
			if (m_selectorX < 0)
				m_selectorX = 0;
		}
		if (
			JamTemplate::InputManager::justPressed(sf::Keyboard::Key::D) || 
			JamTemplate::InputManager::justPressed(sf::Keyboard::Key::Right))
		{
			m_selectorX++;
			if (m_selectorX >= 9)
				m_selectorX = 8;
		}


		if (
			JamTemplate::InputManager::justPressed(sf::Keyboard::Key::W) ||
			JamTemplate::InputManager::justPressed(sf::Keyboard::Key::Up))
		{
			m_selectorY--;
			if (m_selectorY < 0)
				m_selectorY = 0;
		}
		if (
			JamTemplate::InputManager::justPressed(sf::Keyboard::Key::S) ||
			JamTemplate::InputManager::justPressed(sf::Keyboard::Key::Down))
		{
			m_selectorY++;
			if (m_selectorY >= 9)
				m_selectorY = 8;
		}


		m_selector->setPosition(positionFromCoord(m_selectorX, m_selectorY));
		m_selector->update(elapsed);
	}

	virtual void doDraw() const override 
	{
		m_selector->draw(getGame()->getRenderTarget());
		for (auto const& c : m_board)
		{
			if (c->getValue() != 0)
			{
				m_text.setPosition(positionFromCoord(c->getPosition().x, c->getPosition().y));
				m_text.setText(std::to_string(c->getValue()));
				m_text.update(0.0f);
				m_text.setCharacterSize(16U);
				m_text.draw(getGame()->getRenderTarget());
			}
		}
	};

	virtual void doCreate() override 
	{
		m_board.createPuzzle(2);

		m_board.getSolution(m_boardFull);
		
		m_text.loadFont("assets/font.ttf");

		m_selector = std::make_shared<JamTemplate::SmartShape>();
		m_selector->makeRect(sf::Vector2f{ GP::CellPositionSpacing() , GP::CellPositionSpacing() });
		m_selector->setColor(sf::Color::Red);
		
	};
};

#endif
