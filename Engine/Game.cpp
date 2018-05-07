/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.cpp																			  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#include "MainWindow.h"
#include "Game.h"
#include "SpriteCodex.h"

//testing
#include "TestLocation.h"

Game::Game( MainWindow& wnd )
	:
	wnd( wnd ),
	gfx( wnd ),
	m_rng ( std::random_device()()),
	m_board(gfx),
	m_colorDist(0, 255),
	m_snek(Location{ 5,5 }),
	m_node(m_snek)
{
#ifdef _DEBUG
	//Execute Tests
	TestLocation::test();
#endif
}

void Game::Go()
{
	gfx.BeginFrame();	
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel()
{
	if (m_started)
	{
		if (!m_gameOver)
		{
			Snake::EMoveResult moved = Snake::EMoveResult::NOT_MOVED;
			if (wnd.kbd.KeyIsPressed(VK_RIGHT))
			{
				m_deltaLoc = { 1, 0 };
			}
			else if (wnd.kbd.KeyIsPressed(VK_DOWN))
			{
				m_deltaLoc = { 0, 1 };
			}
			else if (wnd.kbd.KeyIsPressed(VK_LEFT))
			{
				m_deltaLoc = { -1, 0 };
			}
			else if (wnd.kbd.KeyIsPressed(VK_UP))
			{
				m_deltaLoc = { 0, -1 };
			}
			//x !=0 and y !=0
			if (m_deltaLoc != 0)
			{
				++m_snekMoveCounter;
				if (m_snekMoveCounter > m_snekMovePeriod)
				{
					//ChangeSnakeBodyColor();
					moved = m_snek.MoveBy(m_deltaLoc);
					m_snekMoveCounter = 0;
				}
			}

			switch (moved)
			{
				case Snake::EMoveResult::SUCCESS:
					if (m_snek.CollectNode(m_node))
						m_node.Respawn();
					break;
				case Snake::EMoveResult::ATE_MYSELF:
					m_gameOver = true;
					break;
				case Snake::EMoveResult::BACK_STEP_BLOCKED:
					/*
					 * If we're trying to "step back we recover
					 * previous m_deltaLoc and move the Snek to it
					 */
					m_deltaLoc *= -1;
					m_snek.MoveBy(m_deltaLoc);
					break;
				case Snake::EMoveResult::HIT_BORDER:
					break;
				case Snake::EMoveResult::NOT_MOVED:
					break;
				default:
					break;
			}
		}
	}
	else
		m_started = wnd.kbd.KeyIsPressed(VK_RETURN);
}

void Game::ChangeSnakeBodyColor()
{
	Snake::BodyColor = Color(m_colorDist(m_rng), m_colorDist(m_rng), m_colorDist(m_rng));
}

void Game::ComposeFrame()
{
	if (m_started)
	{
		m_board.DrawBorders();

		if (m_gameOver)
			SpriteCodex::DrawGameOver(0, 0, gfx);

		m_node.Draw(m_board);
		m_snek.Draw(m_board);
	}
	else
		SpriteCodex::DrawTitle(0, 0, gfx);
	
	//Testing board
	//for (int y = 0; y < m_board.GetHeight(); ++y)
	//{
	//	for (int x = 0; x < m_board.GetWidth(); ++x)
	//	{
	//		Location loc = { x, y };
	//		Color c(m_colorDist(m_rng), m_colorDist(m_rng), m_colorDist(m_rng));
	//		m_board.DrawCell(loc, c);
	//	}
	//}
}
