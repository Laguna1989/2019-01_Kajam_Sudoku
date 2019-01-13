#ifndef GAME_STATE_GAME_ONEPLAYER_HPP_INCLUDEGUARD
#define GAME_STATE_GAME_ONEPLAYER_HPP_INCLUDEGUARD

#include <iostream>
#include <vector>
#include <memory>


#include "Hud.hpp"
#include "GameBoard.hpp"
#include "StateGame.hpp"

namespace JamTemplate
{
	class SmartShape;
}


class StateGameOnePlayer : public StateGame {
public:
	StateGameOnePlayer() = default;

private:

	std::shared_ptr <GameBoard> m_boardP1;

	virtual void doCreateInternal() override;
};

#endif
