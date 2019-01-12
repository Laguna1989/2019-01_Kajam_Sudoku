#ifndef GAME_GAME_BOARD_GUARD_HPP 
#define GAME_GAME_BOARD_GUARD_HPP

#include <memory>
#include <string>

#include "JamTemplate/GameObject.hpp"

#include "Sudoku/Board.hpp"
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
	
	void setPuzzleList(std::vector<std::string>&& list)
	{
		m_puzzleList = std::move(list);
	}


private:
	mutable Board m_board;
	Board m_boardFull;

	mutable std::shared_ptr<JamTemplate::SmartText> m_text;

	int m_selectorX{ 0 };
	int m_selectorY{ 0 };
	std::shared_ptr<JamTemplate::SmartShape> m_selector;

	mutable std::shared_ptr<JamTemplate::SmartShape> m_hightlight;

	std::vector<float> m_InputOffsetY;
	std::vector<float> m_InputTimerOffset;

	StateGame& m_stateGame;

	bool m_firstPlayer{ false };

	std::vector<std::string> m_puzzleList;
	size_t m_puzzleListIdx{ 0 };

	sf::Sprite m_boardBackground;

	inline sf::Vector2f positionFromCoord(int x, int y) const
	{
		return sf::Vector2f{
					GP::CellPositionOffsetX() + x * GP::CellPositionSpacing(),
					GP::CellPositionOffsetY() + y * GP::CellPositionSpacing() } +sf::Vector2f{ (m_firstPlayer ? 0.0f : 10.0f* GP::CellPositionSpacing()), 0 };
	}

	virtual void doDraw() const override;
	virtual void doCreate() override;

	virtual void doUpdate(float const elapsed) override;
	void updateInputTween(float elapsed);
	void updateNumbers(float elapsed);
	void updateSelector(float elapsed);

	void checkForNextBoard();
	void getNextBoard();

	void placeCorrectValue(std::shared_ptr<Cell> c, int num);
	void placeWrongValue();

	void moveCursorTo(int nextX, int nextY);
};

#endif
