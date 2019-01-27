#include "StateGameOnePlayer.hpp"
#include "PuzzleStorage.hpp"
#include "GameBoard.hpp"
#include "Hud.hpp"
#include "StateMenu.hpp"
#include "JamTemplate/Game.hpp"

void StateGameOnePlayer::doCreateInternal()
{
	PuzzleStorage ps{};

	m_boardP1 = std::make_shared<GameBoard>(*this);
	m_boardP1->setPuzzleList(std::move(ps.getPuzzleList(true)));
	m_boardP1->setFirstPlayer(true);
	add(m_boardP1);
	m_hud->AddScoreP1();
	m_boardP1->setCorrectNumberCallBack([this]() {m_hud->AddScoreP1(); });
	m_boardP1->setWrongNumberCallBack([this]() {m_hud->AddScoreP1(-1); });
}

void StateGameOnePlayer::doInternalUpdate(float const /*elapsed*/)
{
	if (m_boardP1->m_finished >= 1)
	{
		getGame()->switchState(std::make_shared<StateMenu>());
	}
}
