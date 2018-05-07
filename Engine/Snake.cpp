#include "Snake.h"
#include <assert.h>

Color Snake::HeadColor = Colors::Green;
Color Snake::BodyColor = Colors::Gray;

void Snake::Segment::InitHead(const Location & in_loc)
{
	m_loc = in_loc;
	m_color = Snake::HeadColor;
}

void Snake::Segment::InitBody()
{
	m_color = Snake::BodyColor;
}

void Snake::Segment::InitBodyWithColor(Color c)
{
	m_color = c;
}


void Snake::Segment::MoveBy(const Location & delta_loc)
{
	assert((abs(delta_loc.x) + abs(delta_loc.y)) == 1);
	m_prevLoc = m_loc;
	m_loc += delta_loc;
}

void Snake::Segment::Follow(const Segment & next)
{
	m_prevLoc = m_loc;
	m_loc = next.m_loc;
}

void Snake::Segment::Draw(Board & brd) const
{
	brd.DrawCell(m_loc, m_color);
}


Snake::Snake(const Location & loc)
{
	m_segments[0].InitHead(loc);
	//init first segments
	for (int i = 1; i < nSegments; ++i)
	{
		m_segments[i].InitBody();
		m_segments[i].SetLocation(Location{loc.x - i, loc.y});
	}
	//m_segments[1].InitBodyWithColor(Colors::Red);
	//m_segments[2].InitBodyWithColor(Colors::Gray);
}

Snake::EMoveResult Snake::MoveBy(const Location & loc)
{
	EMoveResult result = SUCCESS;
	Location headNextLoc = m_segments[0].GetLocation() + loc;

	if (HitsBorder(headNextLoc))
		return HIT_BORDER;

	result = IsInTile(headNextLoc);
	if (result != SUCCESS)
		return result;

	for (int i = nSegments-1; i > 0; --i)
	{
		m_segments[i].Follow(m_segments[i -1]);
	}

	m_segments[0].MoveBy(loc);

	return SUCCESS;
}

void Snake::Grow()
{
	if (nSegments < nMaxSegments)
	{
		m_segments[nSegments].InitBody();
		m_segments[nSegments].SetLocation(m_segments[nSegments - 1].GetPrevLocation());
		++nSegments;
	}
}

void Snake::Draw(Board & brd) const
{
	for (int i = 0; i < nSegments; ++i)
	{
		m_segments[i].Draw(brd);
	}
}

bool Snake::CollectNode(Node & rNode)
{
	//If Snek's head is on same Cell than Node it collects the node
	if (rNode.GetLocation() == m_segments[0].GetLocation())
	{
		Grow();
		return true;
	}
		

	return false;
}

bool Snake::HitsBorder(const Location& nextLoc) const
{
	if ((nextLoc.x < Board::Start.x) ||
		(nextLoc.x >= Board::End.x) ||
		(nextLoc.y < Board::Start.y) ||
		(nextLoc.y >= Board::End.y))
	{
		return true;
	}

	return false;
}

Snake::EMoveResult Snake::IsInTile(const Location & loc, bool exceptEnd) const
{
	//ignore head and tail
	for (int i = 1; i < nSegments - 1; ++i)
	{
		if ((loc == m_segments[i].GetLocation()))
		{
			if (i == 1)
				return EMoveResult::BACK_STEP_BLOCKED;

			return EMoveResult::ATE_MYSELF;
		}
	}

	return EMoveResult::SUCCESS;
}
