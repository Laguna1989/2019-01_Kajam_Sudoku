#ifndef GAME_GAMEPROPERTIES_HPP_INCLUDEGUARD
#define GAME_GAMEPROPERTIES_HPP_INCLUDEGUARD

class GP
{
public:
	GP() = delete;

	static float CellPositionSpacing() { return 32.0f; }
	static float CellPositionOffsetX() { return 10.0f; }
	static float CellPositionOffsetY() { return 10.0f; }
	static float GameBoardInputTimerMax() { return 0.5f; }
	static float GameBoardInputOffsetMax() { return 350; }
};

#endif
