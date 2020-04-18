//#pragma once
//
//#include "Old_Dude.h"
//
//void Dude::update()
//{
//	applyFriction();
//	x += vX;
//	y += vY;
//	borderCheck();
//}
//
//void Dude::draw(Graphics& _gfx)
//{
//	_gfx.PutPixel(7 + x, 0 + y, 0, 0, 0);
//	_gfx.PutPixel(8 + x, 0 + y, 0, 0, 0);
//	_gfx.PutPixel(9 + x, 0 + y, 0, 0, 0);
//	_gfx.PutPixel(10 + x, 0 + y, 0, 0, 0);
//	_gfx.PutPixel(11 + x, 0 + y, 0, 0, 0);
//	_gfx.PutPixel(12 + x, 0 + y, 0, 0, 0);
//	_gfx.PutPixel(5 + x, 1 + y, 0, 0, 0);
//	_gfx.PutPixel(6 + x, 1 + y, 0, 0, 0);
//	_gfx.PutPixel(7 + x, 1 + y, 254, 221, 88);
//	_gfx.PutPixel(8 + x, 1 + y, 254, 221, 88);
//	_gfx.PutPixel(9 + x, 1 + y, 254, 221, 88);
//	_gfx.PutPixel(10 + x, 1 + y, 254, 221, 88);
//	_gfx.PutPixel(11 + x, 1 + y, 254, 221, 88);
//	_gfx.PutPixel(12 + x, 1 + y, 254, 221, 88);
//	_gfx.PutPixel(13 + x, 1 + y, 0, 0, 0);
//	_gfx.PutPixel(14 + x, 1 + y, 0, 0, 0);
//	_gfx.PutPixel(3 + x, 2 + y, 0, 0, 0);
//	_gfx.PutPixel(4 + x, 2 + y, 0, 0, 0);
//	_gfx.PutPixel(5 + x, 2 + y, 254, 221, 88);
//	_gfx.PutPixel(6 + x, 2 + y, 254, 221, 88);
//	_gfx.PutPixel(7 + x, 2 + y, 254, 221, 88);
//	_gfx.PutPixel(8 + x, 2 + y, 254, 221, 88);
//	_gfx.PutPixel(9 + x, 2 + y, 254, 221, 88);
//	_gfx.PutPixel(10 + x, 2 + y, 254, 221, 88);
//	_gfx.PutPixel(11 + x, 2 + y, 254, 221, 88);
//	_gfx.PutPixel(12 + x, 2 + y, 254, 221, 88);
//	_gfx.PutPixel(13 + x, 2 + y, 254, 221, 88);
//	_gfx.PutPixel(14 + x, 2 + y, 254, 221, 88);
//	_gfx.PutPixel(15 + x, 2 + y, 0, 0, 0);
//	_gfx.PutPixel(16 + x, 2 + y, 0, 0, 0);
//	_gfx.PutPixel(2 + x, 3 + y, 0, 0, 0);
//	_gfx.PutPixel(3 + x, 3 + y, 254, 221, 88);
//	_gfx.PutPixel(4 + x, 3 + y, 254, 221, 88);
//	_gfx.PutPixel(5 + x, 3 + y, 254, 221, 88);
//	_gfx.PutPixel(6 + x, 3 + y, 254, 221, 88);
//	_gfx.PutPixel(7 + x, 3 + y, 254, 221, 88);
//	_gfx.PutPixel(8 + x, 3 + y, 254, 221, 88);
//	_gfx.PutPixel(9 + x, 3 + y, 254, 221, 88);
//	_gfx.PutPixel(10 + x, 3 + y, 254, 221, 88);
//	_gfx.PutPixel(11 + x, 3 + y, 254, 221, 88);
//	_gfx.PutPixel(12 + x, 3 + y, 254, 221, 88);
//	_gfx.PutPixel(13 + x, 3 + y, 254, 221, 88);
//	_gfx.PutPixel(14 + x, 3 + y, 254, 221, 88);
//	_gfx.PutPixel(15 + x, 3 + y, 254, 221, 88);
//	_gfx.PutPixel(16 + x, 3 + y, 254, 221, 88);
//	_gfx.PutPixel(17 + x, 3 + y, 0, 0, 0);
//	_gfx.PutPixel(2 + x, 4 + y, 0, 0, 0);
//	_gfx.PutPixel(3 + x, 4 + y, 254, 221, 88);
//	_gfx.PutPixel(4 + x, 4 + y, 254, 221, 88);
//	_gfx.PutPixel(5 + x, 4 + y, 254, 221, 88);
//	_gfx.PutPixel(6 + x, 4 + y, 254, 221, 88);
//	_gfx.PutPixel(7 + x, 4 + y, 254, 221, 88);
//	_gfx.PutPixel(8 + x, 4 + y, 254, 221, 88);
//	_gfx.PutPixel(9 + x, 4 + y, 254, 221, 88);
//	_gfx.PutPixel(10 + x, 4 + y, 254, 221, 88);
//	_gfx.PutPixel(11 + x, 4 + y, 254, 221, 88);
//	_gfx.PutPixel(12 + x, 4 + y, 254, 221, 88);
//	_gfx.PutPixel(13 + x, 4 + y, 254, 221, 88);
//	_gfx.PutPixel(14 + x, 4 + y, 254, 221, 88);
//	_gfx.PutPixel(15 + x, 4 + y, 254, 221, 88);
//	_gfx.PutPixel(16 + x, 4 + y, 254, 221, 88);
//	_gfx.PutPixel(17 + x, 4 + y, 0, 0, 0);
//	_gfx.PutPixel(1 + x, 5 + y, 0, 0, 0);
//	_gfx.PutPixel(2 + x, 5 + y, 254, 221, 88);
//	_gfx.PutPixel(3 + x, 5 + y, 0, 0, 0);
//	_gfx.PutPixel(4 + x, 5 + y, 0, 0, 0);
//	_gfx.PutPixel(5 + x, 5 + y, 254, 221, 88);
//	_gfx.PutPixel(6 + x, 5 + y, 254, 221, 88);
//	_gfx.PutPixel(7 + x, 5 + y, 254, 221, 88);
//	_gfx.PutPixel(8 + x, 5 + y, 254, 221, 88);
//	_gfx.PutPixel(9 + x, 5 + y, 254, 221, 88);
//	_gfx.PutPixel(10 + x, 5 + y, 254, 221, 88);
//	_gfx.PutPixel(11 + x, 5 + y, 0, 0, 0);
//	_gfx.PutPixel(12 + x, 5 + y, 0, 0, 0);
//	_gfx.PutPixel(13 + x, 5 + y, 0, 0, 0);
//	_gfx.PutPixel(14 + x, 5 + y, 0, 0, 0);
//	_gfx.PutPixel(15 + x, 5 + y, 254, 221, 88);
//	_gfx.PutPixel(16 + x, 5 + y, 254, 221, 88);
//	_gfx.PutPixel(17 + x, 5 + y, 254, 221, 88);
//	_gfx.PutPixel(18 + x, 5 + y, 0, 0, 0);
//	_gfx.PutPixel(1 + x, 6 + y, 0, 0, 0);
//	_gfx.PutPixel(2 + x, 6 + y, 0, 0, 0);
//	_gfx.PutPixel(3 + x, 6 + y, 255, 255, 255);
//	_gfx.PutPixel(4 + x, 6 + y, 0, 0, 0);
//	_gfx.PutPixel(5 + x, 6 + y, 0, 0, 0);
//	_gfx.PutPixel(6 + x, 6 + y, 254, 221, 88);
//	_gfx.PutPixel(7 + x, 6 + y, 254, 221, 88);
//	_gfx.PutPixel(8 + x, 6 + y, 254, 221, 88);
//	_gfx.PutPixel(9 + x, 6 + y, 254, 221, 88);
//	_gfx.PutPixel(10 + x, 6 + y, 0, 0, 0);
//	_gfx.PutPixel(11 + x, 6 + y, 255, 255, 255);
//	_gfx.PutPixel(12 + x, 6 + y, 255, 255, 255);
//	_gfx.PutPixel(13 + x, 6 + y, 0, 0, 0);
//	_gfx.PutPixel(14 + x, 6 + y, 0, 0, 0);
//	_gfx.PutPixel(15 + x, 6 + y, 0, 0, 0);
//	_gfx.PutPixel(16 + x, 6 + y, 254, 221, 88);
//	_gfx.PutPixel(17 + x, 6 + y, 254, 221, 88);
//	_gfx.PutPixel(18 + x, 6 + y, 0, 0, 0);
//	_gfx.PutPixel(0 + x, 7 + y, 0, 0, 0);
//	_gfx.PutPixel(1 + x, 7 + y, 0, 0, 0);
//	_gfx.PutPixel(2 + x, 7 + y, 255, 255, 255);
//	_gfx.PutPixel(3 + x, 7 + y, 255, 255, 255);
//	_gfx.PutPixel(4 + x, 7 + y, 0, 0, 0);
//	_gfx.PutPixel(5 + x, 7 + y, 0, 0, 0);
//	_gfx.PutPixel(6 + x, 7 + y, 254, 221, 88);
//	_gfx.PutPixel(7 + x, 7 + y, 254, 221, 88);
//	_gfx.PutPixel(8 + x, 7 + y, 254, 221, 88);
//	_gfx.PutPixel(9 + x, 7 + y, 254, 221, 88);
//	_gfx.PutPixel(10 + x, 7 + y, 0, 0, 0);
//	_gfx.PutPixel(11 + x, 7 + y, 255, 255, 255);
//	_gfx.PutPixel(12 + x, 7 + y, 255, 255, 255);
//	_gfx.PutPixel(13 + x, 7 + y, 0, 0, 0);
//	_gfx.PutPixel(14 + x, 7 + y, 0, 0, 0);
//	_gfx.PutPixel(15 + x, 7 + y, 0, 0, 0);
//	_gfx.PutPixel(16 + x, 7 + y, 254, 221, 88);
//	_gfx.PutPixel(17 + x, 7 + y, 254, 221, 88);
//	_gfx.PutPixel(18 + x, 7 + y, 254, 221, 88);
//	_gfx.PutPixel(19 + x, 7 + y, 0, 0, 0);
//	_gfx.PutPixel(0 + x, 8 + y, 0, 0, 0);
//	_gfx.PutPixel(1 + x, 8 + y, 0, 0, 0);
//	_gfx.PutPixel(2 + x, 8 + y, 255, 255, 255);
//	_gfx.PutPixel(3 + x, 8 + y, 255, 255, 255);
//	_gfx.PutPixel(4 + x, 8 + y, 255, 255, 255);
//	_gfx.PutPixel(5 + x, 8 + y, 0, 0, 0);
//	_gfx.PutPixel(6 + x, 8 + y, 254, 221, 88);
//	_gfx.PutPixel(7 + x, 8 + y, 254, 221, 88);
//	_gfx.PutPixel(8 + x, 8 + y, 254, 221, 88);
//	_gfx.PutPixel(9 + x, 8 + y, 254, 221, 88);
//	_gfx.PutPixel(10 + x, 8 + y, 0, 0, 0);
//	_gfx.PutPixel(11 + x, 8 + y, 255, 255, 255);
//	_gfx.PutPixel(12 + x, 8 + y, 255, 255, 255);
//	_gfx.PutPixel(13 + x, 8 + y, 255, 255, 255);
//	_gfx.PutPixel(14 + x, 8 + y, 255, 255, 255);
//	_gfx.PutPixel(15 + x, 8 + y, 0, 0, 0);
//	_gfx.PutPixel(16 + x, 8 + y, 254, 221, 88);
//	_gfx.PutPixel(17 + x, 8 + y, 254, 221, 88);
//	_gfx.PutPixel(18 + x, 8 + y, 254, 221, 88);
//	_gfx.PutPixel(19 + x, 8 + y, 0, 0, 0);
//	_gfx.PutPixel(0 + x, 9 + y, 0, 0, 0);
//	_gfx.PutPixel(1 + x, 9 + y, 254, 221, 88);
//	_gfx.PutPixel(2 + x, 9 + y, 0, 0, 0);
//	_gfx.PutPixel(3 + x, 9 + y, 0, 0, 0);
//	_gfx.PutPixel(4 + x, 9 + y, 0, 0, 0);
//	_gfx.PutPixel(5 + x, 9 + y, 0, 0, 0);
//	_gfx.PutPixel(6 + x, 9 + y, 254, 221, 88);
//	_gfx.PutPixel(7 + x, 9 + y, 254, 221, 88);
//	_gfx.PutPixel(8 + x, 9 + y, 254, 221, 88);
//	_gfx.PutPixel(9 + x, 9 + y, 254, 221, 88);
//	_gfx.PutPixel(10 + x, 9 + y, 254, 221, 88);
//	_gfx.PutPixel(11 + x, 9 + y, 0, 0, 0);
//	_gfx.PutPixel(12 + x, 9 + y, 0, 0, 0);
//	_gfx.PutPixel(13 + x, 9 + y, 0, 0, 0);
//	_gfx.PutPixel(14 + x, 9 + y, 0, 0, 0);
//	_gfx.PutPixel(15 + x, 9 + y, 254, 221, 88);
//	_gfx.PutPixel(16 + x, 9 + y, 254, 221, 88);
//	_gfx.PutPixel(17 + x, 9 + y, 254, 221, 88);
//	_gfx.PutPixel(18 + x, 9 + y, 254, 221, 88);
//	_gfx.PutPixel(19 + x, 9 + y, 0, 0, 0);
//	_gfx.PutPixel(0 + x, 10 + y, 0, 0, 0);
//	_gfx.PutPixel(1 + x, 10 + y, 254, 221, 88);
//	_gfx.PutPixel(2 + x, 10 + y, 254, 221, 88);
//	_gfx.PutPixel(3 + x, 10 + y, 254, 221, 88);
//	_gfx.PutPixel(4 + x, 10 + y, 254, 221, 88);
//	_gfx.PutPixel(5 + x, 10 + y, 254, 221, 88);
//	_gfx.PutPixel(6 + x, 10 + y, 254, 221, 88);
//	_gfx.PutPixel(7 + x, 10 + y, 254, 221, 88);
//	_gfx.PutPixel(8 + x, 10 + y, 254, 221, 88);
//	_gfx.PutPixel(9 + x, 10 + y, 254, 221, 88);
//	_gfx.PutPixel(10 + x, 10 + y, 254, 221, 88);
//	_gfx.PutPixel(11 + x, 10 + y, 254, 221, 88);
//	_gfx.PutPixel(12 + x, 10 + y, 254, 221, 88);
//	_gfx.PutPixel(13 + x, 10 + y, 254, 221, 88);
//	_gfx.PutPixel(14 + x, 10 + y, 254, 221, 88);
//	_gfx.PutPixel(15 + x, 10 + y, 254, 221, 88);
//	_gfx.PutPixel(16 + x, 10 + y, 254, 221, 88);
//	_gfx.PutPixel(17 + x, 10 + y, 254, 221, 88);
//	_gfx.PutPixel(18 + x, 10 + y, 254, 221, 88);
//	_gfx.PutPixel(19 + x, 10 + y, 0, 0, 0);
//	_gfx.PutPixel(0 + x, 11 + y, 0, 0, 0);
//	_gfx.PutPixel(1 + x, 11 + y, 254, 221, 88);
//	_gfx.PutPixel(2 + x, 11 + y, 254, 221, 88);
//	_gfx.PutPixel(3 + x, 11 + y, 254, 221, 88);
//	_gfx.PutPixel(4 + x, 11 + y, 254, 221, 88);
//	_gfx.PutPixel(5 + x, 11 + y, 254, 221, 88);
//	_gfx.PutPixel(6 + x, 11 + y, 254, 221, 88);
//	_gfx.PutPixel(7 + x, 11 + y, 20, 14, 18);
//	_gfx.PutPixel(8 + x, 11 + y, 18, 11, 14);
//	_gfx.PutPixel(9 + x, 11 + y, 18, 12, 14);
//	_gfx.PutPixel(10 + x, 11 + y, 18, 12, 14);
//	_gfx.PutPixel(11 + x, 11 + y, 21, 13, 16);
//	_gfx.PutPixel(12 + x, 11 + y, 24, 11, 15);
//	_gfx.PutPixel(13 + x, 11 + y, 0, 0, 0);
//	_gfx.PutPixel(14 + x, 11 + y, 254, 221, 88);
//	_gfx.PutPixel(15 + x, 11 + y, 254, 221, 88);
//	_gfx.PutPixel(16 + x, 11 + y, 254, 221, 88);
//	_gfx.PutPixel(17 + x, 11 + y, 254, 221, 88);
//	_gfx.PutPixel(18 + x, 11 + y, 254, 221, 88);
//	_gfx.PutPixel(19 + x, 11 + y, 0, 0, 0);
//	_gfx.PutPixel(0 + x, 12 + y, 0, 0, 0);
//	_gfx.PutPixel(1 + x, 12 + y, 254, 221, 88);
//	_gfx.PutPixel(2 + x, 12 + y, 254, 221, 88);
//	_gfx.PutPixel(3 + x, 12 + y, 254, 221, 88);
//	_gfx.PutPixel(4 + x, 12 + y, 254, 221, 88);
//	_gfx.PutPixel(5 + x, 12 + y, 254, 221, 88);
//	_gfx.PutPixel(6 + x, 12 + y, 23, 9, 23);
//	_gfx.PutPixel(7 + x, 12 + y, 135, 26, 68);
//	_gfx.PutPixel(8 + x, 12 + y, 135, 26, 68);
//	_gfx.PutPixel(9 + x, 12 + y, 135, 26, 68);
//	_gfx.PutPixel(10 + x, 12 + y, 135, 26, 68);
//	_gfx.PutPixel(11 + x, 12 + y, 135, 26, 68);
//	_gfx.PutPixel(12 + x, 12 + y, 135, 26, 68);
//	_gfx.PutPixel(13 + x, 12 + y, 135, 26, 68);
//	_gfx.PutPixel(14 + x, 12 + y, 0, 0, 0);
//	_gfx.PutPixel(15 + x, 12 + y, 254, 221, 88);
//	_gfx.PutPixel(16 + x, 12 + y, 254, 221, 88);
//	_gfx.PutPixel(17 + x, 12 + y, 254, 221, 88);
//	_gfx.PutPixel(18 + x, 12 + y, 254, 221, 88);
//	_gfx.PutPixel(19 + x, 12 + y, 0, 0, 0);
//	_gfx.PutPixel(1 + x, 13 + y, 0, 0, 0);
//	_gfx.PutPixel(2 + x, 13 + y, 254, 221, 88);
//	_gfx.PutPixel(3 + x, 13 + y, 254, 221, 88);
//	_gfx.PutPixel(4 + x, 13 + y, 254, 221, 88);
//	_gfx.PutPixel(5 + x, 13 + y, 0, 0, 0);
//	_gfx.PutPixel(6 + x, 13 + y, 135, 26, 68);
//	_gfx.PutPixel(7 + x, 13 + y, 135, 26, 68);
//	_gfx.PutPixel(8 + x, 13 + y, 135, 26, 68);
//	_gfx.PutPixel(9 + x, 13 + y, 135, 26, 68);
//	_gfx.PutPixel(10 + x, 13 + y, 135, 26, 68);
//	_gfx.PutPixel(11 + x, 13 + y, 135, 26, 68);
//	_gfx.PutPixel(12 + x, 13 + y, 135, 26, 68);
//	_gfx.PutPixel(13 + x, 13 + y, 135, 26, 68);
//	_gfx.PutPixel(14 + x, 13 + y, 135, 26, 68);
//	_gfx.PutPixel(15 + x, 13 + y, 0, 0, 0);
//	_gfx.PutPixel(16 + x, 13 + y, 254, 221, 88);
//	_gfx.PutPixel(17 + x, 13 + y, 254, 221, 88);
//	_gfx.PutPixel(18 + x, 13 + y, 0, 0, 0);
//	_gfx.PutPixel(1 + x, 14 + y, 0, 0, 0);
//	_gfx.PutPixel(2 + x, 14 + y, 254, 221, 88);
//	_gfx.PutPixel(3 + x, 14 + y, 254, 221, 88);
//	_gfx.PutPixel(4 + x, 14 + y, 0, 0, 0);
//	_gfx.PutPixel(5 + x, 14 + y, 135, 26, 68);
//	_gfx.PutPixel(6 + x, 14 + y, 135, 26, 68);
//	_gfx.PutPixel(7 + x, 14 + y, 135, 26, 68);
//	_gfx.PutPixel(8 + x, 14 + y, 135, 26, 68);
//	_gfx.PutPixel(9 + x, 14 + y, 251, 192, 224);
//	_gfx.PutPixel(10 + x, 14 + y, 251, 192, 224);
//	_gfx.PutPixel(11 + x, 14 + y, 251, 192, 224);
//	_gfx.PutPixel(12 + x, 14 + y, 251, 192, 224);
//	_gfx.PutPixel(13 + x, 14 + y, 135, 26, 68);
//	_gfx.PutPixel(14 + x, 14 + y, 135, 26, 68);
//	_gfx.PutPixel(15 + x, 14 + y, 0, 0, 0);
//	_gfx.PutPixel(16 + x, 14 + y, 254, 221, 88);
//	_gfx.PutPixel(17 + x, 14 + y, 254, 221, 88);
//	_gfx.PutPixel(18 + x, 14 + y, 0, 0, 0);
//	_gfx.PutPixel(2 + x, 15 + y, 0, 0, 0);
//	_gfx.PutPixel(3 + x, 15 + y, 254, 221, 88);
//	_gfx.PutPixel(4 + x, 15 + y, 0, 0, 0);
//	_gfx.PutPixel(5 + x, 15 + y, 135, 26, 68);
//	_gfx.PutPixel(6 + x, 15 + y, 135, 26, 68);
//	_gfx.PutPixel(7 + x, 15 + y, 135, 26, 68);
//	_gfx.PutPixel(8 + x, 15 + y, 251, 192, 224);
//	_gfx.PutPixel(9 + x, 15 + y, 251, 192, 224);
//	_gfx.PutPixel(10 + x, 15 + y, 251, 192, 224);
//	_gfx.PutPixel(11 + x, 15 + y, 251, 192, 224);
//	_gfx.PutPixel(12 + x, 15 + y, 251, 192, 224);
//	_gfx.PutPixel(13 + x, 15 + y, 251, 192, 224);
//	_gfx.PutPixel(14 + x, 15 + y, 135, 26, 68);
//	_gfx.PutPixel(15 + x, 15 + y, 0, 0, 0);
//	_gfx.PutPixel(16 + x, 15 + y, 254, 221, 88);
//	_gfx.PutPixel(17 + x, 15 + y, 0, 0, 0);
//	_gfx.PutPixel(2 + x, 16 + y, 0, 0, 0);
//	_gfx.PutPixel(3 + x, 16 + y, 254, 221, 88);
//	_gfx.PutPixel(4 + x, 16 + y, 0, 0, 0);
//	_gfx.PutPixel(5 + x, 16 + y, 135, 26, 68);
//	_gfx.PutPixel(6 + x, 16 + y, 135, 26, 68);
//	_gfx.PutPixel(7 + x, 16 + y, 135, 26, 68);
//	_gfx.PutPixel(8 + x, 16 + y, 251, 192, 224);
//	_gfx.PutPixel(9 + x, 16 + y, 251, 192, 224);
//	_gfx.PutPixel(10 + x, 16 + y, 251, 192, 224);
//	_gfx.PutPixel(11 + x, 16 + y, 251, 192, 224);
//	_gfx.PutPixel(12 + x, 16 + y, 251, 192, 224);
//	_gfx.PutPixel(13 + x, 16 + y, 251, 192, 224);
//	_gfx.PutPixel(14 + x, 16 + y, 135, 26, 68);
//	_gfx.PutPixel(15 + x, 16 + y, 0, 0, 0);
//	_gfx.PutPixel(16 + x, 16 + y, 254, 221, 88);
//	_gfx.PutPixel(17 + x, 16 + y, 0, 0, 0);
//	_gfx.PutPixel(3 + x, 17 + y, 0, 0, 0);
//	_gfx.PutPixel(4 + x, 17 + y, 0, 0, 0);
//	_gfx.PutPixel(5 + x, 17 + y, 0, 0, 0);
//	_gfx.PutPixel(6 + x, 17 + y, 0, 0, 0);
//	_gfx.PutPixel(7 + x, 17 + y, 0, 0, 0);
//	_gfx.PutPixel(8 + x, 17 + y, 0, 0, 0);
//	_gfx.PutPixel(9 + x, 17 + y, 0, 0, 0);
//	_gfx.PutPixel(10 + x, 17 + y, 0, 0, 0);
//	_gfx.PutPixel(11 + x, 17 + y, 0, 0, 0);
//	_gfx.PutPixel(12 + x, 17 + y, 0, 0, 0);
//	_gfx.PutPixel(13 + x, 17 + y, 0, 0, 0);
//	_gfx.PutPixel(14 + x, 17 + y, 0, 0, 0);
//	_gfx.PutPixel(15 + x, 17 + y, 0, 0, 0);
//	_gfx.PutPixel(16 + x, 17 + y, 0, 0, 0);
//	_gfx.PutPixel(5 + x, 18 + y, 0, 0, 0);
//	_gfx.PutPixel(6 + x, 18 + y, 0, 0, 0);
//	_gfx.PutPixel(7 + x, 18 + y, 254, 221, 88);
//	_gfx.PutPixel(8 + x, 18 + y, 254, 221, 88);
//	_gfx.PutPixel(9 + x, 18 + y, 254, 221, 88);
//	_gfx.PutPixel(10 + x, 18 + y, 254, 221, 88);
//	_gfx.PutPixel(11 + x, 18 + y, 254, 221, 88);
//	_gfx.PutPixel(12 + x, 18 + y, 254, 221, 88);
//	_gfx.PutPixel(13 + x, 18 + y, 0, 0, 0);
//	_gfx.PutPixel(14 + x, 18 + y, 0, 0, 0);
//	_gfx.PutPixel(7 + x, 19 + y, 0, 0, 0);
//	_gfx.PutPixel(8 + x, 19 + y, 0, 0, 0);
//	_gfx.PutPixel(9 + x, 19 + y, 0, 0, 0);
//	_gfx.PutPixel(10 + x, 19 + y, 0, 0, 0);
//	_gfx.PutPixel(11 + x, 19 + y, 0, 0, 0);
//	_gfx.PutPixel(12 + x, 19 + y, 0, 0, 0);
//}
//
//void Dude::applyFriction()
//{
//	//if moving apply friction, if V less than 0.25 just stop.
//	if (vY > (kAcceleration - 0.25f)) {
//		vY += (kFriction * -1.0f);
//	}
//	else if (vY < ((kAcceleration - 0.25f) * -1)) {
//		vY += kFriction;
//	}
//	else
//	{
//		vY = 0.0f;
//	}
//	if (vX > (kAcceleration - 0.25f)) {
//		vX += (kFriction * -1.0f);
//	}
//	else if (vX < ((kAcceleration - 0.25f) * -1)) {
//		vX += kFriction;
//	}
//	else
//	{
//		vX = 0.0f;
//	}
//}
//
//void Dude::getPlayerInput(MainWindow& _wnd)
//{
//	// if player speed is less than max speed they can accelerate
//	if (std::abs(vX) < kMaxSpeed)
//	{
//		if (x >= 1 && x <= Graphics::ScreenWidth - 30)
//		{
//			if (_wnd.kbd.KeyIsPressed(VK_RIGHT)) {
//				vX += kAcceleration;
//			}
//			if (_wnd.kbd.KeyIsPressed(VK_LEFT)) {
//				vX += (kAcceleration * -1.0f);
//			}
//		}
//	}
//	if (std::abs(vY) < kMaxSpeed)
//	{
//		if (y >= 1 && y <= Graphics::ScreenHeight - 30)
//		{
//			if (_wnd.kbd.KeyIsPressed(VK_DOWN)) {
//				vY += kAcceleration;
//			}
//			if (_wnd.kbd.KeyIsPressed(VK_UP)) {
//				vY += (kAcceleration * -1.0f);
//			}
//		}
//	}
//}