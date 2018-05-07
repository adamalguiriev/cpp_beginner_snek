#pragma once

#include "Graphics.h"
#include "Location.h"

class Board
{
public:
	Board(Graphics & rGfx);
	void DrawBorders();
	void DrawCell(const Location loc, Color c);
	int GetWidth() const { return width; };
	int GetHeight() const { return height; };
public:
	static constexpr int cellDimension = 50;
	static constexpr int width = 16;
	static constexpr int height = 12;
	static constexpr Location End = { Board::width -1, Board::height -1 };
	static constexpr Location Start = { 0, 0 };
private:
	Graphics & m_rGfx;
	static constexpr Color BordersColor = Colors::White;
};