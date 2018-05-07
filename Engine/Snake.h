#pragma once

#include "Location.h"
#include "Board.h"
#include "Node.h"
class Node;
class Snake
{
public:
	enum EMoveResult
	{
		NOT_MOVED = 0,
		BACK_STEP_BLOCKED,
		SUCCESS,
		HIT_BORDER,
		ATE_MYSELF
	};
private:
	class Segment
	{
	public:

		void InitHead(const Location& in_loc);
		void InitBody();
		void InitBodyWithColor(Color c);
		void MoveBy(const Location& delta_loc);
		void Follow(const Segment& next);
		void Draw(Board& brd) const;
		const Location& GetLocation() const { return m_loc; }
		void SetLocation(const Location& loc) { m_loc = loc; }
		const Location & GetPrevLocation() const { return m_prevLoc; }


	private:
		Location m_loc;
		Location m_prevLoc;
		Color m_color;
	};

public:
	Snake(const Location& loc);

	EMoveResult MoveBy(const Location& loc);
	void Grow();
	void Draw(Board& brd) const;

	bool CollectNode(Node& rNode);

	bool HitsBorder(const Location& loc) const;
	EMoveResult IsInTile(const Location& loc, bool exceptEnd = true) const;

public:
	static Color HeadColor;
	static Color BodyColor;

private:
	static constexpr int nMaxSegments = 100;
	int nSegments = 3;
	Segment m_segments[nMaxSegments];
};

