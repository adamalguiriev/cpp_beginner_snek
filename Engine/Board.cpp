#include "Board.h"
#include <assert.h>

Board::Board(Graphics & rGfx)
	:
	m_rGfx(rGfx)
{
}

void Board::DrawBorders()
{
	for (int y = 0; y < Board::height; ++y)
	{
		DrawCell(Location{ Board::width - 1, y }, BordersColor);
		DrawCell(Location{ 0, y }, BordersColor);
	}

	for (int x = 0; x < Board::width; ++x)
	{
		DrawCell(Location{ x, 0 }, BordersColor);
		DrawCell(Location{ x, Board::height -1 }, BordersColor);
	}
}

void Board::DrawCell(const Location loc, Color c)
{
	assert(loc.x >= 0);
	assert(loc.x < width);
	assert(loc.y >= 0);
	assert(loc.y < height);
	m_rGfx.DrawRectDim(loc.x * cellDimension, loc.y * cellDimension, cellDimension, cellDimension, c);
}
 