#include "StateGameTwoPlayer.hpp"
#include "PuzzleStorage.hpp"
#include "GameBoard.hpp"
#include "Hud.hpp"

void StateGameTwoPlayer::doCreateInternal()
{
	PuzzleStorage ps{};
	
	m_boardP1 = std::make_shared<GameBoard>(*this);
	m_boardP1->setPuzzleList(std::move(ps.getPuzzleList(true)));
	m_boardP1->setFirstPlayer(true);
	add(m_boardP1);
	
	m_boardP2 = std::make_shared<GameBoard>(*this);
	m_boardP2->setPuzzleList(std::move(ps.getPuzzleList(false)));
	add(m_boardP2);
	
	m_boardP1->setWrongNumberCallBack([b = m_boardP2, this]() {b->placeRandomCorrectNumber(); m_hud->AddScoreP1(-1); });
	m_boardP2->setWrongNumberCallBack([b = m_boardP1, this]() {b->placeRandomCorrectNumber(); m_hud->AddScoreP2(-1); });

	m_boardP1->setCorrectNumberCallBack([this]() {m_hud->AddScoreP1(); });
	m_boardP2->setCorrectNumberCallBack([this]() {m_hud->AddScoreP2(); });
	m_hud->AddScoreP1();
	m_hud->AddScoreP2();
}
