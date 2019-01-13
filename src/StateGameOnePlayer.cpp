#include "StateGameOnePlayer.hpp"
#include "PuzzleStorage.hpp"

void StateGameOnePlayer::doCreateInternal()
{
	PuzzleStorage ps{};

	m_boardP1 = std::make_shared<GameBoard>(*this);
	m_boardP1->setPuzzleList(std::move(ps.getPuzzleList(true)));
	m_boardP1->setFirstPlayer(true);
	add(m_boardP1);

	//m_boardP1->setWrongNumberCallBack([b = m_boardP2]() {b->placeRandomCorrectNumber(); });
}
