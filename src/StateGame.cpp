#include "StateGame.hpp"

#include "JamTemplate/SmartSprite.hpp"
#include "JamTemplate/SmartShape.hpp"
#include "JamTemplate/TweenAlpha.hpp"
#include "PuzzleStorage.hpp"

void StateGame::doInternalUpdate (float const elapsed) 
{
	m_overlay->update(elapsed);
	
}

void StateGame::doCreate() 
{
	float w = static_cast<float>(getGame()->getRenderTarget()->getSize().x);
	float h = static_cast<float>(getGame()->getRenderTarget()->getSize().y);
	m_hud = std::make_shared<Hud>();
	add(m_hud);

	using JamTemplate::TweenAlpha;
	using JamTemplate::SmartShape;

	m_overlay = std::make_shared<SmartShape>();
	m_overlay->makeRect(sf::Vector2f{ w,h });
	m_overlay->setColor(sf::Color{ 0,0,0 });
	m_overlay->update(0);
	auto tw = TweenAlpha<SmartShape>::create(m_overlay, 0.5f, sf::Uint8{ 255 }, sf::Uint8{ 0 });
	add(tw);

	std::cout << "sg1\n";
	PuzzleStorage ps{};
	
	std::cout << "sg2\n";
	m_boardP1 = std::make_shared<GameBoard>(*this);
	std::cout << "sg3\n";
	m_boardP1->setPuzzleList(std::move(ps.getPuzzleList(true)));
	add(m_boardP1);
	std::cout << "sg5\n";
	m_boardP2 = std::make_shared<GameBoard>(*this);
	m_boardP2->setFirstPlayer(true);
	std::cout << "sg5\n";
	m_boardP2->setPuzzleList(std::move(ps.getPuzzleList(false)));
	add(m_boardP2);
	std::cout << "sg6\n";

}
