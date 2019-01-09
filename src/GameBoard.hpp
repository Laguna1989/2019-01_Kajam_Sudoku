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

	void setFirstPlayer(bool isFirstPlayer)
	{
		m_firstPlayer = isFirstPlayer;
	}
	
private:
	mutable Board m_board;
	Board m_boardFull;

	mutable JamTemplate::SmartText m_text;

	JamTemplate::SmartShape::Sptr m_selector;
	
	int m_selectorX{ 0 };
	int m_selectorY{ 0 };

	bool m_firstPlayer{ false };

	sf::Vector2f positionFromCoord(int x, int y) const
	{
		return sf::Vector2f{
					GP::CellPositionOffsetX() + x * GP::CellPositionSpacing(),
					GP::CellPositionOffsetY() + y * GP::CellPositionSpacing() } +sf::Vector2f{ (m_firstPlayer ? 0.0f : 10.0f* GP::CellPositionSpacing()), 0 };
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

		int num = 0;
		if (m_firstPlayer)
		{
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

		}
		else
		{
			if (JamTemplate::InputManager::justPressed(sf::Keyboard::Key::Numpad1))
				num = 1;
			else if (JamTemplate::InputManager::justPressed(sf::Keyboard::Key::Numpad2))
				num = 2;
			else if (JamTemplate::InputManager::justPressed(sf::Keyboard::Key::Numpad3))
				num = 3;
			else if (JamTemplate::InputManager::justPressed(sf::Keyboard::Key::Numpad4))
				num = 4;
			else if (JamTemplate::InputManager::justPressed(sf::Keyboard::Key::Numpad5))
				num = 5;
			else if (JamTemplate::InputManager::justPressed(sf::Keyboard::Key::Numpad6))
				num = 6;
			else if (JamTemplate::InputManager::justPressed(sf::Keyboard::Key::Numpad7))
				num = 7;
			else if (JamTemplate::InputManager::justPressed(sf::Keyboard::Key::Numpad8))
				num = 8;
			else if (JamTemplate::InputManager::justPressed(sf::Keyboard::Key::Numpad9))
				num = 9;
		}
		if (num == 0) return;
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
		//std::cout << m_selectorX << " " << m_selectorY << "\n";
		int nextX = m_selectorX;
		int nextY = m_selectorY;
		bool moved = false;
		if (
			JamTemplate::InputManager::justReleased(sf::Keyboard::Key::A) && m_firstPlayer ||
			JamTemplate::InputManager::justReleased(sf::Keyboard::Key::Left) && !m_firstPlayer)
		{
			nextX--;
			moved = true;
		}
		if (
			JamTemplate::InputManager::justReleased(sf::Keyboard::Key::D) && m_firstPlayer ||
			JamTemplate::InputManager::justReleased(sf::Keyboard::Key::Right) && !m_firstPlayer)
		{
			nextX++;
			moved = true;
		}

		if (nextX < 0)
			nextX = 0;
		if (nextX >= 9)
			nextX = 8;

		if (
			JamTemplate::InputManager::justReleased(sf::Keyboard::Key::W) && m_firstPlayer ||
			JamTemplate::InputManager::justReleased(sf::Keyboard::Key::Up) && !m_firstPlayer)
		{
			nextY--;
			moved = true;
		}
		if (
			JamTemplate::InputManager::justReleased(sf::Keyboard::Key::S) && m_firstPlayer ||
			JamTemplate::InputManager::justReleased(sf::Keyboard::Key::Down) && !m_firstPlayer)
		{
			nextY++;
			moved = true;
		}

		if (nextY < 0)
			nextY = 0;
		if (nextY >= 9)
			nextY = 8;

		if (moved)
		{
			std::cout << "move to " << nextX << " " << nextY << " from " << m_selectorX << " " << m_selectorY << std::endl;
			moveCursorTo(nextX, nextY);
		}


		m_selector->update(elapsed);
	}

	void moveCursorTo(int nextX, int nextY)
	{
		m_selectorX = nextX;
		m_selectorY = nextY;
		m_selector->setPosition(positionFromCoord(nextX, nextY));
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
		m_selector->setPosition(positionFromCoord(m_selectorX, m_selectorY));
	};
};

#endif
