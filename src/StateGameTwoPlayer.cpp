#include "StateGameTwoPlayer.hpp"

#include "PuzzleStorage.hpp"


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
	
	m_boardP1->setWrongNumberCallBack([b = m_boardP2]() {b->placeRandomCorrectNumber(); });
	m_boardP2->setWrongNumberCallBack([b = m_boardP1]() {b->placeRandomCorrectNumber(); });
}
