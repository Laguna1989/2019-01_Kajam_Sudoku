#include "GameBoard.hpp"
#include "StateGame.hpp"

#include "JamTemplate/TextureManager.hpp"
#include "JamTemplate/Game.hpp"
#include "JamTemplate/SmartText.hpp"
#include "JamTemplate/SmartShape.hpp"
#include "JamTemplate/TweenPosition.hpp"
#include "JamTemplate/TweenAlpha.hpp"

#include "Sudoku/Serializer.hpp"

GameBoard::GameBoard(StateGame& sg) : m_stateGame(sg)
{

}

void GameBoard::checkForNextBoard()
{
	if (m_board.getOpenFields() == 0)
	{
		getNextBoard();
	}
}

void GameBoard::placeRandomCorrectNumber()
{
	for (auto& c : m_board)
	{
		if (c->getValue() == 0)
		{
			auto sol = m_boardFull.getCellAt(c->getPosition())->getValue();
			placeCorrectValue(c, sol);
			break;
		}
	}
	checkForNextBoard();
	setNewHighlights();
}

void GameBoard::doUpdate(float const elapsed) 
{
	m_text->update(elapsed);

	updateSelector(elapsed);
	updateNumbers(elapsed);

	

	if (JamTemplate::InputManager::justPressed(sf::Keyboard::Key::P))
	{
		getNextBoard();
	}

	updateInputTween(elapsed);
}

void GameBoard::updateInputTween(float elapsed)
{

	assert(m_InputOffsetY.size() == m_InputTimerOffset.size());

	if (m_inputSkip > 0)
	{
		m_inputSkip--;
		return;
	}

	for (size_t i = 0; i != m_InputOffsetY.size(); ++i)
	{
		if (m_InputTimerOffset.at(i) > 0)
		{
			m_InputTimerOffset.at(i) -= elapsed;
			float v = m_InputTimerOffset.at(i) / GP::GameBoardInputTimerMax();
			if (v < 0) v = 0;
			if (v > 1) v = 1;

			float ov = JamTemplate::Lerp::cubic<float>(0, 1, v);
			m_InputOffsetY.at(i) = -ov * GP::GameBoardInputOffsetMax();

		}
		else
		{
			m_InputTimerOffset.at(i) = -1;
		}
	}
}

void GameBoard::updateNumbers(float /*elapsed*/)
{
	auto c = m_board.getCellAt(Coord{ m_selectorX,m_selectorY });

	if (c->getValue() != 0)
		return;

	auto cc = m_boardFull.getCellAt(Coord{ m_selectorX,m_selectorY });

	int num = 0;
	if (m_firstPlayer)
	{
		if (JamTemplate::InputManager::justPressed(sf::Keyboard::Key::Num1))
			num = 1;
		else if (JamTemplate::InputManager::justPressed(sf::Keyboard::Key::Num2))
			num = 2;
		else if (JamTemplate::InputManager::justPressed(sf::Keyboard::Key::Num3))
			num = 3;
		else if (JamTemplate::InputManager::justPressed(sf::Keyboard::Key::Num4))
			num = 4;
		else if (JamTemplate::InputManager::justPressed(sf::Keyboard::Key::Num5))
			num = 5;
		else if (JamTemplate::InputManager::justPressed(sf::Keyboard::Key::Num6))
			num = 6;
		else if (JamTemplate::InputManager::justPressed(sf::Keyboard::Key::Num7))
			num = 7;
		else if (JamTemplate::InputManager::justPressed(sf::Keyboard::Key::Num8))
			num = 8;
		else if (JamTemplate::InputManager::justPressed(sf::Keyboard::Key::Num9))
			num = 9;

	}
	else
	{
		if (JamTemplate::InputManager::justPressed(sf::Keyboard::Key::Numpad1))
			num = 1;
		else if (JamTemplate::InputManager::justPressed(sf::Keyboard::Key::Numpad2))
			num = 2;
		else if (JamTemplate::InputManager::justPressed(sf::Keyboard::Key::Numpad3))
			num = 3;
		else if (JamTemplate::InputManager::justPressed(sf::Keyboard::Key::Numpad4))
			num = 4;
		else if (JamTemplate::InputManager::justPressed(sf::Keyboard::Key::Numpad5))
			num = 5;
		else if (JamTemplate::InputManager::justPressed(sf::Keyboard::Key::Numpad6))
			num = 6;
		else if (JamTemplate::InputManager::justPressed(sf::Keyboard::Key::Numpad7))
			num = 7;
		else if (JamTemplate::InputManager::justPressed(sf::Keyboard::Key::Numpad8))
			num = 8;
		else if (JamTemplate::InputManager::justPressed(sf::Keyboard::Key::Numpad9))
			num = 9;
	}
	if (num == 0) return;
	if (cc->getValue() == static_cast<unsigned int>(num))
	{
		placeCorrectValue(c, num);
	}
	else
	{
		placeWrongValue();
	}
}

void GameBoard::placeCorrectValue(std::shared_ptr<Cell> c, unsigned int num)
{
	c->setValue(num);
	checkForNextBoard();
	setNewHighlights();
	m_InputTimerOffset.at(posFromCoord(c->getPosition())) = GP::GameBoardInputTimerMax()/2.0f;
	m_selector->flash(0.35f, GP::PaletteFlashGreen());
	m_correctNumberCallback();
}
void GameBoard::placeWrongValue()
{
	if (m_wrongNumberCallback.operator bool())
	{
		m_wrongNumberCallback();
	}
	m_selector->shake(0.35f, 2, 0.0125f);
	m_selector->flash(0.45f, GP::PaletteFlashRed());
}

void GameBoard::updateSelector(float elapsed)
{
	
	
	int nextX = m_selectorX;
	int nextY = m_selectorY;
	bool moved = false;
	if (
		JamTemplate::InputManager::justPressed(sf::Keyboard::Key::A) && m_firstPlayer ||
		JamTemplate::InputManager::justPressed(sf::Keyboard::Key::Left) && !m_firstPlayer)
	{
		nextX--;
		moved = true;
	}
	if (
		JamTemplate::InputManager::justPressed(sf::Keyboard::Key::D) && m_firstPlayer ||
		JamTemplate::InputManager::justPressed(sf::Keyboard::Key::Right) && !m_firstPlayer)
	{
		nextX++;
		moved = true;
	}

	if (nextX < 0)
		nextX = 0;
	if (nextX >= 9)
		nextX = 8;

	if (
		JamTemplate::InputManager::justPressed(sf::Keyboard::Key::W) && m_firstPlayer ||
		JamTemplate::InputManager::justPressed(sf::Keyboard::Key::Up) && !m_firstPlayer)
	{
		nextY--;
		moved = true;
	}
	if (
		JamTemplate::InputManager::justPressed(sf::Keyboard::Key::S) && m_firstPlayer ||
		JamTemplate::InputManager::justPressed(sf::Keyboard::Key::Down) && !m_firstPlayer)
	{
		nextY++;
		moved = true;
	}

	if (nextY < 0)
		nextY = 0;
	if (nextY >= 9)
		nextY = 8;

	if (moved)
	{
		moveCursorTo(nextX, nextY);
	}


	m_selector->update(elapsed);
}

void GameBoard::moveCursorTo(int nextX, int nextY)
{
	m_selectorX = nextX;
	m_selectorY = nextY;

	{	// tween to position
		auto start = m_selector->getPosition();
		auto end = positionFromCoord(m_selectorX, m_selectorY);


		auto tw = JamTemplate::TweenPosition<JamTemplate::SmartShape>::create(m_selector, 0.125, start, end);
		m_stateGame.add(tw);
	}

	setNewHighlights();

	{	// tween alpha of highlight
		auto tw = JamTemplate::TweenAlpha<JamTemplate::SmartShape>::create(m_hightlight, 0.2f, 0, 255);
		m_stateGame.add(tw);
	}
	

}

void GameBoard::setNewHighlights()
{
	m_highlightList.clear();
	Coord spos{ m_selectorX, m_selectorY };
	auto ct = m_board.getCellAt(spos);
	auto v = ct->getValue();
	if (v == 0) return;
	
	for (auto const& c : m_board)
	{
		if ((c->getPosition().x != spos.x || c->getPosition().y != spos.y)  && c->getValue() == v)
		{
			m_highlightList.push_back(c->getPosition());
		}
	}

}

void GameBoard::doDraw() const 
{
	getGame()->getRenderTarget()->draw(m_boardBackground);
	
	for (auto c : m_highlightList)
	{
		m_hightlight->setPosition(positionFromCoord(c.x, c.y));
		m_hightlight->update(0.0f);
		m_hightlight->draw(getGame()->getRenderTarget());
	}

	m_selector->draw(getGame()->getRenderTarget());
	int idx = 0;
	for (auto const& c : m_board)
	{
		
		if (c->getValue() != 0)
		{
			auto pos = positionFromCoord(c->getPosition().x, c->getPosition().y) + sf::Vector2f{ 10,5 };
			m_text->setText(std::to_string(c->getValue()));
			m_text->setCharacterSize(16U);
			m_text->setPosition(pos + sf::Vector2f{ 2,2 });

			float v = (1 + m_InputOffsetY.at(idx) / GP::GameBoardInputOffsetMax());
			if (v < 0) v = 0;
			if (v > 1) v = 1;
			sf::Uint8 a = static_cast<sf::Uint8>(155 + v * 100);

			m_text->setColor(GP::PaletteFontShadow(a));
			m_text->update(0.0f);
			m_text->draw(getGame()->getRenderTarget());

			m_text->setPosition(pos + sf::Vector2f{ 0,  m_InputOffsetY.at(idx) });

			m_text->update(0.0f);
			m_text->setColor(GP::PaletteFontFront());
			m_text->draw(getGame()->getRenderTarget());	
		}
		idx++;
	}
};

void GameBoard::getNextBoard()
{
	m_board.clearBoard();
	m_boardFull.clearBoard();
	Serializer::Deserialize(m_puzzleList[m_puzzleListIdx], m_board, m_boardFull);
	m_puzzleListIdx++;
	for (auto& v : m_InputTimerOffset)
	{
		v = JamTemplate::Random::getFloatGauss(GP::GameBoardInputTimerMax(), 0.105f);
	}
	m_finished++;
}

 void GameBoard::doCreate()
{
	m_InputTimerOffset.resize(81, 0);
	m_InputOffsetY.resize(81, 0);


	getNextBoard();
	m_finished = 0;

	m_text = std::make_shared<JamTemplate::SmartText>();
	m_text->loadFont("assets/font.ttf");

	m_selector = std::make_shared<JamTemplate::SmartShape>();
	m_selector->makeRect(sf::Vector2f{ GP::CellPositionSpacing() , GP::CellPositionSpacing() });
	m_selector->setColor(GP::PaletteSelector());
	
	m_selector->setPosition(positionFromCoord(m_selectorX, m_selectorY));

	m_hightlight = std::make_shared<JamTemplate::SmartShape>();
	m_hightlight->makeRect(sf::Vector2f{ GP::CellPositionSpacing() , GP::CellPositionSpacing() });
	m_hightlight->setColor(GP::PaletteHighlight());
	
	m_boardBackground.setTexture(JamTemplate::TextureManager::get("__gameboard"));
	m_boardBackground.setPosition(positionFromCoord(0,0));
}
