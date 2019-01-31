#include "StateGameOnePlayer.hpp"
#include "PuzzleStorage.hpp"
#include "GameBoard.hpp"
#include "Hud.hpp"
#include "StateMenu.hpp"
#include "JamTemplate/Game.hpp"
#include "Sudoku/Board.hpp"
#include "Sudoku/Serializer.hpp"

void StateGameOnePlayer::doCreateInternal()
{
	PuzzleStorage ps{};

	//Board b;
	//Board s;

	//std::string str = "";
	//str += "8,6,3,9,2,5,1,4,7,";
	//str += "x1,x9,5,8,7,4,3,6,2,";
	//str += "2,7,4,3,1,6,9,8,5,";
	//str += "4,8,1,6,9,2,7,5,3,";
	//str += "5,3,7,1,4,8,6,2,9,";
	//str += "6,2,9,5,3,7,4,1,8,";
	//str += "7,4,8,2,6,9,5,3,1,";
	//str += "x9,x1,2,4,5,3,8,7,6,";
	//str += "3,5,6,7,8,1,2,9,4";
	//Serializer::Deserialize(str, b, s);
	//
	//std::deque<std::shared_ptr<Cell>> emptyCells;
	//emptyCells.push_back(b.getCellAt({ 1,0 }));
	//emptyCells.push_back(b.getCellAt({ 1,1 }));
	//emptyCells.push_back(b.getCellAt({ 7,0 }));
	//emptyCells.push_back(b.getCellAt({ 7,1 }));
	//
	//for (auto const& c : emptyCells)
	//{
	//	std::cout << c->getValue() << std::endl;
	//}

	//std::cout << std::endl;
	//b.print();
	//std::cout << std::endl;

	//std::cout << b.solve(0, 0) << std::endl;

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
