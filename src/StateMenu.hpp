#ifndef GAME_STATE_MENU_HPP_INCLUDEGUARD
#define GAME_STATE_MENU_HPP_INCLUDEGUARD

#include "JamTemplate/GameState.hpp"

class StateMenu : public JamTemplate::GameState {
public:
	StateMenu();
private:
	void doInternalUpdate(float const /*elapsed*/) override;
	void doCreate();
};

#endif
