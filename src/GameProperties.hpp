#ifndef GAME_GAMEPROPERTIES_HPP_INCLUDEGUARD
#define GAME_GAMEPROPERTIES_HPP_INCLUDEGUARD

class GP
{
public:
	GP() = delete;

	static float CellPositionSpacing() { return 32.0f; }
	static float CellPositionOffsetX() { return 10.0f; }
	static float CellPositionOffsetY() { return 10.0f; }
};

#endif
