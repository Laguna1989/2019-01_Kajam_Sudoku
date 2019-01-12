#ifndef GAME_COORD_HPP_INCLUDEGUARD
#define GAME_COORD_HPP_INCLUDEGUARD

struct Coord
{
	int x{ 0 };
	int y{ 0 };
};

inline bool operator== (const Coord& o, const Coord p) { return (o.x == p.x && o.y == p.y); }

inline bool operator < (const Coord &lhs, const Coord &rhs) {
	return lhs.x < rhs.x || (lhs.x == rhs.x && lhs.y < rhs.y);
}



#endif
