#ifndef GAME_BOARD_GUARD_HPP 
#define  GAME_BOARD_GUARD_HPP

#include <memory>
#include <string>

#include "JamTemplate/GameObject.hpp"
#include "JamTemplate/SmartText.hpp"

#include "Board.hpp"
#include "GameProperties.hpp"


class GameBoard : public JamTemplate::GameObject
{
public:
	using Sptr = std::shared_ptr<GameBoard>;

	
private:
	mutable Board m_board;

	mutable JamTemplate::SmartText m_text;

	virtual void doUpdate(float const elapsed) override
	{
		m_text.update(elapsed);
	};

	virtual void doDraw() const override 
	{
		for (auto const& c : m_board)
		{
			if (c->getValue() != 0)
			{
				sf::Vector2f pos{
					GP::CellPositionOffsetX() + c->getPosition().x * GP::CellPositionSpacing(),
					GP::CellPositionOffsetY() + c->getPosition().y * GP::CellPositionSpacing() };
				m_text.setPosition(pos);
				m_text.setText(std::to_string(c->getValue()));
				m_text.update(0.0f);
				m_text.draw(getGame()->getRenderTarget());
			}
		}
	};

	virtual void doCreate() override 
	{
		m_board.createPuzzle(15);
		m_text.loadFont("assets/font.ttf");
		
	};
};

#endif
