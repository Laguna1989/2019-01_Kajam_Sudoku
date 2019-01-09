#ifndef GAME_STATE_GAME_HPP_INCLUDEGUARD
#define GAME_STATE_GAME_HPP_INCLUDEGUARD

#include <iostream>
#include <vector>
#include <memory>

#include "JamTemplate/GameState.hpp"


#include "Hud.hpp"
#include "GameBoard.hpp"

namespace JamTemplate
{
	class SmartShape;
	class GameBoard;
}


class StateGame : public JamTemplate::GameState {
public:
	StateGame() = default;

private:

	std::shared_ptr<Hud> m_hud;

	std::shared_ptr<JamTemplate::SmartShape> m_overlay;

	std::shared_ptr <GameBoard> m_boardP1;
	std::shared_ptr<GameBoard> m_boardP2;

	void doInternalUpdate(float const elapsed) override;

	void doCreate() override;

};

#endif
