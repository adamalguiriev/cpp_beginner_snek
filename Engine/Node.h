#pragma once

#include "Location.h"
#include "Board.h"
#include "Snake.h"
#include <random>
class Snake;
class Node
{
public:
	Node(Snake& rSnek);
	
	void Draw(Board& brd);
	
	void Respawn();
	Location& GetLocation() { return m_loc; }

private:
	std::mt19937 m_rng;
	std::uniform_int_distribution<int> m_nodeXDist;
	std::uniform_int_distribution<int> m_nodeYDist;

	Location m_loc;
	Snake& m_rSnek;
	static constexpr Color m_color = Colors::Red;
};