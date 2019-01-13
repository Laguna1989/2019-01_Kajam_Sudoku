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
}


class StateGame : public JamTemplate::GameState {
public:
	StateGame() = default;

private:

	std::shared_ptr<Hud> m_hud;

	std::shared_ptr<JamTemplate::SmartShape> m_background;
	std::shared_ptr<JamTemplate::SmartShape> m_overlay;


	void doCreate() override;

	virtual void doCreateInternal();

	virtual void doInternalUpdate(float const elapsed) override;
	virtual void doInternalDraw() const override;
};

#endif
