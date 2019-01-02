#ifndef GAME_STATE_GAME_HPP_INCLUDEGUARD
#define GAME_STATE_GAME_HPP_INCLUDEGUARD

#include <iostream>
#include <vector>

#include "JamTemplate/GameState.hpp"
#include "JamTemplate/Timer.hpp"
#include "JamTemplate/Collision.hpp"
#include "JamTemplate/ObjectGroup.hpp"
#include "JamTemplate/SmartSprite.hpp"
#include "JamTemplate/SmartShape.hpp"
#include "JamTemplate/TweenAlpha.hpp"
#include "Hud.hpp"


class StateGame : public JamTemplate::GameState {
public:
	StateGame() = default;


private:

	std::shared_ptr<Hud> m_hud;

	JamTemplate::SmartShape::Sptr m_overlay;

	void doInternalUpdate (float const elapsed) override
	{
		m_overlay->update(elapsed);
	}

	void doCreate() override
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
	}

	void doInternalDraw() const override
	{

	}
};

#endif
