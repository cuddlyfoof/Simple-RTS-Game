/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.h																				  *
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
#pragma once

#include "Keyboard.h"
#include "Mouse.h"
#include "Graphics.h"
#include <vector>
#include "RTS Files/EntityManagmentSystems.h"
#include "RTS Files/EntStruct.h"
//#include "RTS Files/Entities.h"
#include "FrameTimer.h"

class Game
{
public:
    Game(class MainWindow& wnd);
	Game( const Game& ) = delete;
	Game& operator=( const Game& ) = delete;
	void Go();
private:
	void ComposeFrame();
	void UpdateModel();
	/********************************/
	/*  User Functions              */
    void drawRect(int, int, int, int);
    void drawLine(int, int, int, int);
    void drawCursor(int, int, int);
    bool squareCollision(int, int, int, int, int, int);
    void drawTitle(int, int);
    void drawGameOver(int, int);
	/********************************/
private:
	MainWindow& wnd;
	Graphics gfx;
    EntStruct Entities;
    EntityManagmentSystems EMS{ Entities };
    FrameTimer ft;
    //Entities entityData;
	/********************************/
	/*  User Variables              */
    bool gameStart = false;
    bool rightWasPressed = false;
    bool leftWasPressed = false;
    bool hWasPressed = false;
    bool dWasPressed = false;
    int rightMouseX = 100;
    int rightMouseY = 100;
    int leftMouseX = 100;
    int leftMouseY = 100;
	/********************************/
};