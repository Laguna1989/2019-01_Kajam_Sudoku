#ifndef GAME_GAME_BOARD_GUARD_HPP 
#define GAME_GAME_BOARD_GUARD_HPP

#include <memory>
#include <string>

#include "JamTemplate/GameObject.hpp"

#include "Board.hpp"
#include "GameProperties.hpp"
#include "JamTemplate/InputManager.hpp"

namespace JamTemplate
{
	class SmartText;
	class SmartShape;
}

class StateGame;

class GameBoard : public JamTemplate::GameObject
{
public:

	GameBoard(StateGame& sg);

	using Sptr = std::shared_ptr<GameBoard>;

	void setFirstPlayer(bool isFirstPlayer)
	{
		m_firstPlayer = isFirstPlayer;
	}
	
private:
	mutable Board m_board;
	Board m_boardFull;

	mutable std::shared_ptr<JamTemplate::SmartText> m_text;
	std::shared_ptr<JamTemplate::SmartShape> m_selector;

	StateGame& m_stateGame;
	
	int m_selectorX{ 0 };
	int m_selectorY{ 0 };

	bool m_firstPlayer{ false };

	inline sf::Vector2f positionFromCoord(int x, int y) const
	{
		return sf::Vector2f{
					GP::CellPositionOffsetX() + x * GP::CellPositionSpacing(),
					GP::CellPositionOffsetY() + y * GP::CellPositionSpacing() } +sf::Vector2f{ (m_firstPlayer ? 0.0f : 10.0f* GP::CellPositionSpacing()), 0 };
	}

	virtual void doUpdate(float const elapsed) override;

	void checkForNextBoard();

	void updateNumbers(float elapsed);

	void placeCorrectValue(std::shared_ptr<Cell> c, int num);

	void placeWrongValue();

	void updateSelector(float elapsed);

	void moveCursorTo(int nextX, int nextY);

	virtual void doDraw() const override;

	virtual void doCreate() override;
};

#endif
