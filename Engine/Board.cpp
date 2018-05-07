#include "Board.h"
#include <assert.h>

Board::Board(Graphics & rGfx)
	:
	m_rGfx(rGfx)
{
}

void Board::DrawBorders()
{
	for (int y = 0; y < Board::GridHeight; ++y)
	{
		DrawCell(Location{ Board::GridWidth - 1, y }, BordersColor);
		DrawCell(Location{ 0, y }, BordersColor);
	}

	for (int x = 0; x < Board::GridWidth; ++x)
	{
		DrawCell(Location{ x, 0 }, BordersColor);
		DrawCell(Location{ x, Board::GridHeight -1 }, BordersColor);
	}
}

//TODO: Add cell padding
void Board::DrawCell(const Location loc, Color c)
{
	assert(loc.x >= 0);
	assert(loc.x < GridWidth);
	assert(loc.y >= 0);
	assert(loc.y < GridHeight);
	m_rGfx.DrawRectDim(loc.x * cellDimension, loc.y * cellDimension, cellDimension, cellDimension, c);
}
 