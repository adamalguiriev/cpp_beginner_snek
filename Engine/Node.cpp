#include "Node.h"



Node::Node(Snake& rSnek) : 
	m_rng(std::random_device()()),
	m_nodeXDist(Board::Start.x, Board::End.x),
	m_nodeYDist(Board::Start.y, Board::End.y),
	m_rSnek(rSnek)
{
	Respawn();
}

void Node::Draw(Board & brd)
{
	brd.DrawCell(m_loc, m_color);
}

void Node::Respawn()
{
	do
	{
		m_loc.x = m_nodeXDist(m_rng);
		m_loc.y = m_nodeYDist(m_rng);
	} while (m_rSnek.HitsBorder(m_loc) || (m_rSnek.IsInTile(m_loc, false) != Snake::EMoveResult::SUCCESS));
}

