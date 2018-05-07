#pragma once

#include "Graphics.h"
#include "Location.h"

class Board
{
public:
	Board(Graphics & rGfx);
	void DrawBorders();
	void DrawCell(const Location loc, Color c);
	int GetWidth() const { return GridWidth; };
	int GetHeight() const { return GridHeight; };
public:
	static constexpr int cellDimension = 25;
	static constexpr int GridWidth = 16;
	static constexpr int GridHeight = 12;
	static constexpr Location End = { Board::GridWidth -1, Board::GridHeight -1 };
	static constexpr Location Start = { 1, 1 };
private:
	Graphics & m_rGfx;
	static constexpr Color BordersColor = Colors::White;
};