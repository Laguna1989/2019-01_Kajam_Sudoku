#ifndef GAME_STATE_GAME_TWOPLAYER_HPP_INCLUDEGUARD
#define GAME_STATE_GAME_TWOPLAYER_HPP_INCLUDEGUARD

#include <iostream>
#include <vector>
#include <memory>

#include "StateGame.hpp"

namespace JamTemplate
{
	class SmartShape;
}

class GameBoard;


class StateGameTwoPlayer : public StateGame {
public:
	StateGameTwoPlayer() = default;

private:


	std::shared_ptr <GameBoard> m_boardP1;
	std::shared_ptr<GameBoard> m_boardP2;

	virtual void doCreateInternal() override;
	void doInternalUpdate(float const /*elapsed*/) override;
};

#endif
