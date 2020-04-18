#include "Entities.h"
#include "Graphics.h"
#include <cmath>
#include "Game.h"

Entities::Entities()
{
}

Entities::~Entities()
{
}

void Entities::moveSelectedDudes(int x, int y)
{
	for (auto dude : staticSelectedDudesPos) 
	{
		movingSelectedDudesPos.emplace_back(std::move(dude));
	}
	for (auto& dude : movingSelectedDudesPos)
	{
		dude.dx = (float)x;
		dude.dy = (float)y;
	}
	staticSelectedDudesPos.clear();
}

void Entities::addEntityToQueue(int _entNum, int _x, int _y)
{
	switch (_entNum)
	{
	//Add Dude : 0
	case 0 :
		//addVector6Entity(staticDudesPos, _x, _y);
		break;
	//Add Hive : 1
	case 1 :
		for (auto dude : staticSelectedDudesPos)
		{
			if (resources >= 50)
			{
				hives.emplace_back(uuid);
			}
		}
		
		break;
	default:
		break;
	}
}

//void Entities::stopDudes(std::vector<Vector4>& _entsFrom, std::vector<Vector4>& _entsTo, float minSpeed)
//{
//	for (auto it{ _entsFrom.begin() }; it != _entsFrom.end();)
//	{
//		if (it->vX <= minSpeed && it->vY <= minSpeed)
//		{
//			_entsTo.emplace_back(it->x, it->y, it->id);
//			it = _entsFrom.erase(it);
//		}
//		else
//		{
//			it++;
//		}
//	}
//}

void Entities::addVector6Entity(std::vector<Vector6>& _ents, int _entNum, int _x, int _y)
{
	bool canAdd = true;
	for (auto dude : _ents)
	{
		if ((_x + Dude::diameter) >= dude.x 
			&& (_x - Dude::diameter) <= dude.x 
			&& (_y + Dude::diameter) >= dude.y 
			&& (_y - Dude::diameter) <= dude.y)
		{
			canAdd = false;
		}
	}
	if (canAdd)
	{
		_ents.emplace_back(_x, _y, uuid);
		switch (_entNum)
		{
		case 0:
			dudes.emplace_back(uuid);
			break;
		default:
			break;
		}
		uuid++;
	}
}

void Entities::addVector2Entity(std::vector<Vector2>& _ents, int _entNum, int _x, int _y)
{
	bool canAdd = true;
	for (auto dude : _ents)
	{
		if ((_x + Dude::diameter) >= dude.x
			&& (_x - Dude::diameter) <= dude.x
			&& (_y + Dude::diameter) >= dude.y
			&& (_y - Dude::diameter) <= dude.y)
		{
			canAdd = false;
		}
	}
	if (canAdd)
	{
		_ents.emplace_back(_x, _y, uuid);
		switch (_entNum)
		{
		case 1:
			hives.emplace_back(uuid);
			break;
		default:
			break;
		}
		uuid++;
	}
}

//void Entities::updatePoosPosition()
//{
//	for (auto v4 : poosPos) 
//	{
//		if (v4.x >= x && v4.y >= y)
//		{
//
//		}
//		v4.x += Dude::speed;
//		v4.y += Dude::speed;
//	}
//}

void Entities::updatePositions(std::vector<Vector6>& _entsFrom, std::vector<Vector6>& _entsTo)
{
	//This seems to be my moving problem, dudes only move diagonally
	auto doCirclesOverlap = [](float x1, float y1, float r1, float x2, float y2, float r2)
	{
		return (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2) <= (r1 + r2) * (r1 + r2);
	};

	auto getDistance = [](float x1, float y1, float x2, float y2)
	{
		return (std::sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2)));
	};

	for (auto it{_entsFrom.begin()}; it != _entsFrom.end();)
	{	
		float fDistance = getDistance(it->x, it->y, it->dx, it->dy);
		
		it->vX -= Dude::acceleration * (it->x - it->dx) / fDistance;
		it->vY -= Dude::acceleration * (it->y - it->dy) / fDistance;

		applyFriction(*it, 0.1f);

		applySpeedLimit(*it, Dude::speed);

		//
		//if they have reached their goal OR are they going too slow?; stop
		//			
		if ((doCirclesOverlap(it->x, it->y, Dude::radius, it->dx, it->dy, Dude::diameter))
			|| (std::fabs(it->vX) < minSpeed && fabs(it->vY) < minSpeed))
		{
			_entsTo.emplace_back(it->x, it->y, it->id);
			it = _entsFrom.erase(it);
		}
		else
		{
			it->x += it->vX;
			it->y += it->vY;
			it++;
		}		
	}
}

void Entities::collisionCheck(std::vector<Vector6>& ents1, std::vector<Vector6>& ents2)
{
	auto doCirclesOverlap = [](float x1, float y1, float r1, float x2, float y2, float r2)
	{
		return std::fabs((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2)) <= (r1 + r2) * (r1 + r2);
	};

	auto getDistance = [](float x1, float y1, float x2, float y2)
	{
		return std::sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
	};
	for (auto it1{ents1.begin()}; it1 != ents1.end(); it1++)
	{
		for (auto it2{ents2.begin()}; it2 != ents2.end(); it2 ++)
		{
			if (it1->id != it2->id)
			{
				if (doCirclesOverlap(it1->x, it1->y, Dude::radius, it2->x, it2->y, Dude::radius))
				{
					float fDistance = getDistance(it1->x, it1->y, it2->x, it2->y);
					float fOverlap = 0.5f * (fDistance - (Dude::diameter));					

					//Displace first ent
					it1->vX -= fOverlap * (it1->x - it2->x) / fDistance;
					it1->vY -= fOverlap * (it1->y - it2->y) / fDistance;

					//Displace second ent
					it2->vX += fOverlap * (it1->x - it2->x) / fDistance;
					it2->vY += fOverlap * (it1->y - it2->y) / fDistance;

					applyFriction(*it1, 0.1f);
					applyFriction(*it2, 0.1f);

					applySpeedLimit(*it1, Dude::speed);
					applySpeedLimit(*it2, Dude::speed);

					it1->x += it1->vX;
					it1->y += it1->vY;

					it2->x += it2->vX;
					it2->y += it2->vY;
				}
			}
		}
	}
	
}

// TODO: MATHS
//bool Entities::boxCollisionCheck(const int x1, const int y1, const int w1, const int x2, const int y2, const int w2)
//{
//	const int d = (w1 / 2);
//	return ((x1 - d) >= x2 - w1
//		&& (y1 - d) >= y2 - w1
//		&& (x1 + d) <= x2 + w1
//		&& (y1 + d) <= y2 + w1);
//}

void Entities::update()
{	
	updatePositions(movingDudesPos, staticDudesPos);
	updatePositions(movingSelectedDudesPos, staticSelectedDudesPos);

	//Not apart of the issue
	collisionCheck(movingSelectedDudesPos, movingSelectedDudesPos);
	collisionCheck(movingSelectedDudesPos, movingDudesPos);
	collisionCheck(movingSelectedDudesPos, staticDudesPos);
	collisionCheck(movingSelectedDudesPos, staticSelectedDudesPos);
	collisionCheck(movingDudesPos, movingDudesPos);
	collisionCheck(movingDudesPos, staticDudesPos);
	collisionCheck(movingDudesPos, staticSelectedDudesPos);
	collisionCheck(staticDudesPos, staticDudesPos);
	collisionCheck(staticDudesPos, staticSelectedDudesPos);
	collisionCheck(staticSelectedDudesPos, staticSelectedDudesPos);
}

void Entities::selectEntities(MainWindow& _wnd, int _x, int _y)
{	
	selectVector6(_wnd, staticDudesPos, staticSelectedDudesPos, _x, _y);
	selectVector6(_wnd, movingDudesPos, movingSelectedDudesPos, _x, _y);
	selectVector2(_wnd, hivesPos, selectedHivesPos, _x, _y);
}

void Entities::selectVector6(MainWindow& _wnd, std::vector<Vector6>& _entsFrom, std::vector<Vector6>& _entsTo, const int x, const int y)
{
	auto isInBox = [](float x1, float y1, int x2, int y2, int x3, int y3)
	{
		if (x3 < x2)
		{
			std::swap(x2, x3);
		}
		if (y3 < y2)
		{
			std::swap(y2, y3);
		}
		return (x2 <= x1 
			&& x3 >= x1 
			&& y2 <= y1 
			&& y3 >= y1);
	};

	for (auto it{_entsFrom.begin()}; it != _entsFrom.end();)
	{
		if (isInBox(it->x + Dude::radius, it->y + Dude::radius, x, y, _wnd.mouse.GetPosX(), _wnd.mouse.GetPosY()))
		{
			_entsTo.emplace_back(std::move(*it));
			it = _entsFrom.erase(it);
		}
		else
		{
			it++;
		}		
	}
}

void Entities::selectVector2(MainWindow& _wnd, std::vector<Vector2>& _entsFrom, std::vector<Vector2>& _entsTo, const int x, const int y)
{
	auto isInBox = [](float x1, float y1, int x2, int y2, int x3, int y3)
	{
		if (x3 < x2)
		{
			std::swap(x2, x3);
		}
		if (y3 < y2)
		{
			std::swap(y2, y3);
		}
		return (x1 >= x2 && x1 <= x3 && y1 >= y2 && y1 <= y3);
	};

	for (auto it{ _entsFrom.begin() }; it != _entsFrom.end();)
	{
		if (isInBox(it->x + Dude::radius, it->y + Dude::radius, x, y, _wnd.mouse.GetPosX(), _wnd.mouse.GetPosY()))
		{
			_entsTo.emplace_back(std::move(*it));
			it = _entsFrom.erase(it);
		}
		else
		{
			it++;
		}
	}
}

void Entities::deselectEntities()
{
	for (auto dude : movingSelectedDudesPos)
	{
		movingDudesPos.emplace_back(std::move(dude));
	}
	for (auto dude : staticSelectedDudesPos)
	{
		staticDudesPos.emplace_back(std::move(dude));
	}
	for (auto hive : selectedHivesPos) 
	{
		hivesPos.emplace_back(std::move(hive));
	}
	movingSelectedDudesPos.clear();
	staticSelectedDudesPos.clear();
	selectedHivesPos.clear();
}

void Entities::applySpeedLimit(Vector6& _ent, const float limit)
{
	if (_ent.vX > limit)
	{
		_ent.vX = limit;
	}
	else if (_ent.vX < -limit)
	{
		_ent.vX = -limit;
	}
	if (_ent.vY > limit)
	{
		_ent.vY = limit;
	}
	else if (_ent.vY < -limit)
	{
		_ent.vY = -limit;
	}
}

void Entities::applyFriction(Vector6& _ent, const float friction)
{
	_ent.vX += (_ent.vX * friction) * -1.0f;
	_ent.vY += (_ent.vY * friction) * -1.0f;
}


void Entities::render(Graphics& _gfx)
{
	for (auto dude : staticDudesPos) 
	{
		renderDude(_gfx, (int)dude.x, (int)dude.y, 1);
	}
	for (auto dude : movingDudesPos)
	{
		renderDude(_gfx, (int)dude.x, (int)dude.y, 1);
	}
	for (auto dude : staticSelectedDudesPos)
	{
		renderSelectedDude(_gfx, (int)dude.x, (int)dude.y, 1);
	}
	for (auto dude : movingSelectedDudesPos)
	{
		renderSelectedDude(_gfx, (int)dude.x, (int)dude.y, 1);
	}
	for (auto hive : hivesPos)
	{
		renderDude(_gfx, (int)hive.x, (int)hive.y, 3);
	}
	for (auto hive : selectedHivesPos)
	{
		renderSelectedDude(_gfx, (int)hive.x, (int)hive.y, 3);
	}

}

void Entities::renderSelectedDude(Graphics& _gfx, int _x, int _y, int _scale)
{
	renderDude(_gfx, _x, _y, _scale);
	auto drawLine = [&_gfx](float x1, float y1, float x2, float y2)
	{
		if (y2 < y1)
		{
			std::swap(y2, y1);
		}
		if (x2 < x1)
		{
			std::swap(x2, x1);
		}
		if (x1 == x2)
		{
			for (int i = 0; i < (y2 - y1); i++)
			{
				_gfx.PutPixel(x1, (y1 + i), Colors::Green);
			}
		}
		if (y1 == y2)
		{
			for (int i = 0; i < (x2 - x1); i++)
			{
				_gfx.PutPixel((x1 + i), y1, Colors::Green);
			}
		}
	};
	
	drawLine(_x, _y, _x + (Dude::diameter * _scale), _y);
	drawLine(_x + (Dude::diameter * _scale), _y, _x + (Dude::diameter * _scale), _y + (Dude::diameter * _scale));
	drawLine(_x + (Dude::diameter * _scale), _y + (Dude::diameter * _scale), _x, _y + (Dude::diameter * _scale));
	drawLine(_x, _y + (Dude::diameter * _scale), _x, _y);
}

void Entities::renderPoo(Graphics& _gfx, int _x, int _y, int _scale)
{	
	_gfx.PutPixel(14 + _x, 0 + _y, 138, 77, 0);
	_gfx.PutPixel(7 + _x, 1 + _y, 138, 77, 0);
	_gfx.PutPixel(13 + _x, 1 + _y, 138, 77, 0);
	_gfx.PutPixel(20 + _x, 1 + _y, 138, 77, 0);
	_gfx.PutPixel(6 + _x, 2 + _y, 138, 77, 0);
	_gfx.PutPixel(13 + _x, 2 + _y, 138, 77, 0);
	_gfx.PutPixel(20 + _x, 2 + _y, 138, 77, 0);
	_gfx.PutPixel(6 + _x, 3 + _y, 138, 77, 0);
	_gfx.PutPixel(6 + _x, 4 + _y, 138, 77, 0);
	_gfx.PutPixel(14 + _x, 4 + _y, 138, 77, 0);
	_gfx.PutPixel(21 + _x, 4 + _y, 138, 77, 0);
	_gfx.PutPixel(7 + _x, 5 + _y, 138, 77, 0);
	_gfx.PutPixel(13 + _x, 5 + _y, 138, 77, 0);
	_gfx.PutPixel(21 + _x, 5 + _y, 138, 77, 0);
	_gfx.PutPixel(7 + _x, 6 + _y, 138, 77, 0);
	_gfx.PutPixel(20 + _x, 6 + _y, 138, 77, 0);
	_gfx.PutPixel(6 + _x, 7 + _y, 138, 77, 0);
	_gfx.PutPixel(14 + _x, 7 + _y, 51, 28, 0);
	_gfx.PutPixel(15 + _x, 7 + _y, 51, 28, 0);
	_gfx.PutPixel(20 + _x, 7 + _y, 138, 77, 0);
	_gfx.PutPixel(12 + _x, 8 + _y, 51, 28, 0);
	_gfx.PutPixel(13 + _x, 8 + _y, 51, 28, 0);
	_gfx.PutPixel(14 + _x, 8 + _y, 51, 28, 0);
	_gfx.PutPixel(7 + _x, 9 + _y, 138, 77, 0);
	_gfx.PutPixel(11 + _x, 9 + _y, 51, 28, 0);
	_gfx.PutPixel(12 + _x, 9 + _y, 102, 57, 0);
	_gfx.PutPixel(13 + _x, 9 + _y, 138, 77, 0);
	_gfx.PutPixel(14 + _x, 9 + _y, 138, 77, 0);
	_gfx.PutPixel(15 + _x, 9 + _y, 51, 28, 0);
	_gfx.PutPixel(21 + _x, 9 + _y, 138, 77, 0);
	_gfx.PutPixel(10 + _x, 10 + _y, 51, 28, 0);
	_gfx.PutPixel(11 + _x, 10 + _y, 51, 28, 0);
	_gfx.PutPixel(12 + _x, 10 + _y, 102, 57, 0);
	_gfx.PutPixel(13 + _x, 10 + _y, 138, 77, 0);
	_gfx.PutPixel(14 + _x, 10 + _y, 138, 77, 0);
	_gfx.PutPixel(15 + _x, 10 + _y, 51, 28, 0);
	_gfx.PutPixel(20 + _x, 10 + _y, 138, 77, 0);
	_gfx.PutPixel(9 + _x, 11 + _y, 51, 28, 0);
	_gfx.PutPixel(10 + _x, 11 + _y, 138, 77, 0);
	_gfx.PutPixel(11 + _x, 11 + _y, 138, 77, 0);
	_gfx.PutPixel(12 + _x, 11 + _y, 51, 28, 0);
	_gfx.PutPixel(13 + _x, 11 + _y, 51, 28, 0);
	_gfx.PutPixel(14 + _x, 11 + _y, 51, 28, 0);
	_gfx.PutPixel(15 + _x, 11 + _y, 51, 28, 0);
	_gfx.PutPixel(16 + _x, 11 + _y, 51, 28, 0);
	_gfx.PutPixel(9 + _x, 12 + _y, 51, 28, 0);
	_gfx.PutPixel(10 + _x, 12 + _y, 138, 77, 0);
	_gfx.PutPixel(11 + _x, 12 + _y, 138, 77, 0);
	_gfx.PutPixel(12 + _x, 12 + _y, 111, 62, 0);
	_gfx.PutPixel(13 + _x, 12 + _y, 102, 57, 0);
	_gfx.PutPixel(14 + _x, 12 + _y, 102, 57, 0);
	_gfx.PutPixel(15 + _x, 12 + _y, 102, 57, 0);
	_gfx.PutPixel(16 + _x, 12 + _y, 51, 28, 0);
	_gfx.PutPixel(9 + _x, 13 + _y, 51, 28, 0);
	_gfx.PutPixel(10 + _x, 13 + _y, 109, 61, 0);
	_gfx.PutPixel(11 + _x, 13 + _y, 138, 77, 0);
	_gfx.PutPixel(12 + _x, 13 + _y, 138, 77, 0);
	_gfx.PutPixel(13 + _x, 13 + _y, 138, 77, 0);
	_gfx.PutPixel(14 + _x, 13 + _y, 138, 77, 0);
	_gfx.PutPixel(15 + _x, 13 + _y, 138, 77, 0);
	_gfx.PutPixel(16 + _x, 13 + _y, 51, 28, 0);
	_gfx.PutPixel(5 + _x, 14 + _y, 51, 28, 0);
	_gfx.PutPixel(7 + _x, 14 + _y, 51, 28, 0);
	_gfx.PutPixel(8 + _x, 14 + _y, 51, 28, 0);
	_gfx.PutPixel(9 + _x, 14 + _y, 51, 28, 0);
	_gfx.PutPixel(10 + _x, 14 + _y, 51, 28, 0);
	_gfx.PutPixel(11 + _x, 14 + _y, 138, 77, 0);
	_gfx.PutPixel(12 + _x, 14 + _y, 138, 77, 0);
	_gfx.PutPixel(13 + _x, 14 + _y, 138, 77, 0);
	_gfx.PutPixel(14 + _x, 14 + _y, 138, 77, 0);
	_gfx.PutPixel(15 + _x, 14 + _y, 138, 77, 0);
	_gfx.PutPixel(16 + _x, 14 + _y, 51, 28, 0);
	_gfx.PutPixel(4 + _x, 15 + _y, 51, 28, 0);
	_gfx.PutPixel(5 + _x, 15 + _y, 138, 77, 0);
	_gfx.PutPixel(6 + _x, 15 + _y, 51, 28, 0);
	_gfx.PutPixel(7 + _x, 15 + _y, 116, 65, 0);
	_gfx.PutPixel(8 + _x, 15 + _y, 138, 77, 0);
	_gfx.PutPixel(9 + _x, 15 + _y, 138, 77, 0);
	_gfx.PutPixel(10 + _x, 15 + _y, 138, 77, 0);
	_gfx.PutPixel(11 + _x, 15 + _y, 51, 28, 0);
	_gfx.PutPixel(12 + _x, 15 + _y, 51, 28, 0);
	_gfx.PutPixel(13 + _x, 15 + _y, 51, 28, 0);
	_gfx.PutPixel(14 + _x, 15 + _y, 51, 28, 0);
	_gfx.PutPixel(15 + _x, 15 + _y, 51, 28, 0);
	_gfx.PutPixel(16 + _x, 15 + _y, 51, 28, 0);
	_gfx.PutPixel(17 + _x, 15 + _y, 51, 28, 0);
	_gfx.PutPixel(18 + _x, 15 + _y, 51, 28, 0);
	_gfx.PutPixel(1 + _x, 16 + _y, 51, 28, 0);
	_gfx.PutPixel(2 + _x, 16 + _y, 51, 28, 0);
	_gfx.PutPixel(3 + _x, 16 + _y, 51, 28, 0);
	_gfx.PutPixel(4 + _x, 16 + _y, 51, 28, 0);
	_gfx.PutPixel(5 + _x, 16 + _y, 138, 77, 0);
	_gfx.PutPixel(6 + _x, 16 + _y, 51, 28, 0);
	_gfx.PutPixel(7 + _x, 16 + _y, 116, 65, 0);
	_gfx.PutPixel(8 + _x, 16 + _y, 138, 77, 0);
	_gfx.PutPixel(9 + _x, 16 + _y, 138, 77, 0);
	_gfx.PutPixel(10 + _x, 16 + _y, 138, 77, 0);
	_gfx.PutPixel(11 + _x, 16 + _y, 138, 77, 0);
	_gfx.PutPixel(12 + _x, 16 + _y, 138, 77, 0);
	_gfx.PutPixel(13 + _x, 16 + _y, 109, 61, 0);
	_gfx.PutPixel(14 + _x, 16 + _y, 51, 28, 0);
	_gfx.PutPixel(15 + _x, 16 + _y, 138, 77, 0);
	_gfx.PutPixel(16 + _x, 16 + _y, 138, 77, 0);
	_gfx.PutPixel(17 + _x, 16 + _y, 138, 77, 0);
	_gfx.PutPixel(18 + _x, 16 + _y, 123, 69, 0);
	_gfx.PutPixel(19 + _x, 16 + _y, 51, 28, 0);
	_gfx.PutPixel(0 + _x, 17 + _y, 51, 28, 0);
	_gfx.PutPixel(1 + _x, 17 + _y, 87, 49, 0);
	_gfx.PutPixel(2 + _x, 17 + _y, 87, 49, 0);
	_gfx.PutPixel(3 + _x, 17 + _y, 87, 49, 0);
	_gfx.PutPixel(4 + _x, 17 + _y, 87, 49, 0);
	_gfx.PutPixel(5 + _x, 17 + _y, 51, 28, 0);
	_gfx.PutPixel(6 + _x, 17 + _y, 51, 28, 0);
	_gfx.PutPixel(7 + _x, 17 + _y, 43, 24, 0);
	_gfx.PutPixel(8 + _x, 17 + _y, 51, 28, 0);
	_gfx.PutPixel(9 + _x, 17 + _y, 51, 28, 0);
	_gfx.PutPixel(10 + _x, 17 + _y, 51, 28, 0);
	_gfx.PutPixel(11 + _x, 17 + _y, 51, 28, 0);
	_gfx.PutPixel(12 + _x, 17 + _y, 51, 28, 0);
	_gfx.PutPixel(13 + _x, 17 + _y, 40, 22, 0);
	_gfx.PutPixel(14 + _x, 17 + _y, 51, 28, 0);
	_gfx.PutPixel(15 + _x, 17 + _y, 138, 77, 0);
	_gfx.PutPixel(16 + _x, 17 + _y, 138, 77, 0);
	_gfx.PutPixel(17 + _x, 17 + _y, 138, 77, 0);
	_gfx.PutPixel(18 + _x, 17 + _y, 123, 69, 0);
	_gfx.PutPixel(19 + _x, 17 + _y, 51, 28, 0);
	_gfx.PutPixel(0 + _x, 18 + _y, 51, 28, 0);
	_gfx.PutPixel(1 + _x, 18 + _y, 138, 77, 0);
	_gfx.PutPixel(2 + _x, 18 + _y, 138, 77, 0);
	_gfx.PutPixel(3 + _x, 18 + _y, 138, 77, 0);
	_gfx.PutPixel(4 + _x, 18 + _y, 138, 77, 0);
	_gfx.PutPixel(5 + _x, 18 + _y, 51, 28, 0);
	_gfx.PutPixel(6 + _x, 18 + _y, 51, 28, 0);
	_gfx.PutPixel(7 + _x, 18 + _y, 51, 28, 0);
	_gfx.PutPixel(8 + _x, 18 + _y, 51, 28, 0);
	_gfx.PutPixel(9 + _x, 18 + _y, 51, 28, 0);
	_gfx.PutPixel(10 + _x, 18 + _y, 51, 28, 0);
	_gfx.PutPixel(11 + _x, 18 + _y, 51, 28, 0);
	_gfx.PutPixel(12 + _x, 18 + _y, 51, 28, 0);
	_gfx.PutPixel(13 + _x, 18 + _y, 51, 28, 0);
	_gfx.PutPixel(14 + _x, 18 + _y, 51, 28, 0);
	_gfx.PutPixel(15 + _x, 18 + _y, 138, 77, 0);
	_gfx.PutPixel(16 + _x, 18 + _y, 138, 77, 0);
	_gfx.PutPixel(17 + _x, 18 + _y, 138, 77, 0);
	_gfx.PutPixel(18 + _x, 18 + _y, 123, 69, 0);
	_gfx.PutPixel(19 + _x, 18 + _y, 51, 28, 0);
	_gfx.PutPixel(20 + _x, 18 + _y, 51, 28, 0);
	_gfx.PutPixel(21 + _x, 18 + _y, 51, 28, 0);
	_gfx.PutPixel(22 + _x, 18 + _y, 51, 28, 0);
	_gfx.PutPixel(0 + _x, 19 + _y, 51, 28, 0);
	_gfx.PutPixel(1 + _x, 19 + _y, 138, 77, 0);
	_gfx.PutPixel(2 + _x, 19 + _y, 138, 77, 0);
	_gfx.PutPixel(3 + _x, 19 + _y, 138, 77, 0);
	_gfx.PutPixel(4 + _x, 19 + _y, 138, 77, 0);
	_gfx.PutPixel(5 + _x, 19 + _y, 51, 28, 0);
	_gfx.PutPixel(6 + _x, 19 + _y, 138, 77, 0);
	_gfx.PutPixel(7 + _x, 19 + _y, 138, 77, 0);
	_gfx.PutPixel(8 + _x, 19 + _y, 138, 77, 0);
	_gfx.PutPixel(9 + _x, 19 + _y, 138, 77, 0);
	_gfx.PutPixel(10 + _x, 19 + _y, 138, 77, 0);
	_gfx.PutPixel(11 + _x, 19 + _y, 138, 77, 0);
	_gfx.PutPixel(12 + _x, 19 + _y, 138, 77, 0);
	_gfx.PutPixel(13 + _x, 19 + _y, 138, 77, 0);
	_gfx.PutPixel(14 + _x, 19 + _y, 138, 77, 0);
	_gfx.PutPixel(15 + _x, 19 + _y, 138, 77, 0);
	_gfx.PutPixel(16 + _x, 19 + _y, 138, 77, 0);
	_gfx.PutPixel(17 + _x, 19 + _y, 138, 77, 0);
	_gfx.PutPixel(18 + _x, 19 + _y, 123, 69, 0);
	_gfx.PutPixel(19 + _x, 19 + _y, 51, 28, 0);
	_gfx.PutPixel(20 + _x, 19 + _y, 138, 77, 0);
	_gfx.PutPixel(21 + _x, 19 + _y, 138, 77, 0);
	_gfx.PutPixel(22 + _x, 19 + _y, 65, 36, 0);
	_gfx.PutPixel(23 + _x, 19 + _y, 51, 28, 0);
	_gfx.PutPixel(1 + _x, 20 + _y, 51, 28, 0);
	_gfx.PutPixel(2 + _x, 20 + _y, 51, 28, 0);
	_gfx.PutPixel(3 + _x, 20 + _y, 51, 28, 0);
	_gfx.PutPixel(4 + _x, 20 + _y, 51, 28, 0);
	_gfx.PutPixel(5 + _x, 20 + _y, 51, 28, 0);
	_gfx.PutPixel(6 + _x, 20 + _y, 138, 77, 0);
	_gfx.PutPixel(7 + _x, 20 + _y, 138, 77, 0);
	_gfx.PutPixel(8 + _x, 20 + _y, 138, 77, 0);
	_gfx.PutPixel(9 + _x, 20 + _y, 138, 77, 0);
	_gfx.PutPixel(10 + _x, 20 + _y, 138, 77, 0);
	_gfx.PutPixel(11 + _x, 20 + _y, 138, 77, 0);
	_gfx.PutPixel(12 + _x, 20 + _y, 138, 77, 0);
	_gfx.PutPixel(13 + _x, 20 + _y, 138, 77, 0);
	_gfx.PutPixel(14 + _x, 20 + _y, 138, 77, 0);
	_gfx.PutPixel(15 + _x, 20 + _y, 138, 77, 0);
	_gfx.PutPixel(16 + _x, 20 + _y, 138, 77, 0);
	_gfx.PutPixel(17 + _x, 20 + _y, 138, 77, 0);
	_gfx.PutPixel(18 + _x, 20 + _y, 123, 69, 0);
	_gfx.PutPixel(19 + _x, 20 + _y, 51, 28, 0);
	_gfx.PutPixel(20 + _x, 20 + _y, 138, 77, 0);
	_gfx.PutPixel(21 + _x, 20 + _y, 138, 77, 0);
	_gfx.PutPixel(22 + _x, 20 + _y, 65, 36, 0);
	_gfx.PutPixel(23 + _x, 20 + _y, 51, 28, 0);
	_gfx.PutPixel(0 + _x, 21 + _y, 51, 28, 0);
	_gfx.PutPixel(1 + _x, 21 + _y, 138, 77, 0);
	_gfx.PutPixel(2 + _x, 21 + _y, 138, 77, 0);
	_gfx.PutPixel(3 + _x, 21 + _y, 138, 77, 0);
	_gfx.PutPixel(4 + _x, 21 + _y, 138, 77, 0);
	_gfx.PutPixel(5 + _x, 21 + _y, 138, 77, 0);
	_gfx.PutPixel(6 + _x, 21 + _y, 51, 28, 0);
	_gfx.PutPixel(7 + _x, 21 + _y, 51, 28, 0);
	_gfx.PutPixel(8 + _x, 21 + _y, 51, 28, 0);
	_gfx.PutPixel(9 + _x, 21 + _y, 51, 28, 0);
	_gfx.PutPixel(10 + _x, 21 + _y, 51, 28, 0);
	_gfx.PutPixel(11 + _x, 21 + _y, 51, 28, 0);
	_gfx.PutPixel(12 + _x, 21 + _y, 51, 28, 0);
	_gfx.PutPixel(13 + _x, 21 + _y, 51, 28, 0);
	_gfx.PutPixel(14 + _x, 21 + _y, 51, 28, 0);
	_gfx.PutPixel(15 + _x, 21 + _y, 51, 28, 0);
	_gfx.PutPixel(16 + _x, 21 + _y, 51, 28, 0);
	_gfx.PutPixel(17 + _x, 21 + _y, 51, 28, 0);
	_gfx.PutPixel(18 + _x, 21 + _y, 51, 28, 0);
	_gfx.PutPixel(20 + _x, 21 + _y, 51, 28, 0);
	_gfx.PutPixel(21 + _x, 21 + _y, 51, 28, 0);
	_gfx.PutPixel(22 + _x, 21 + _y, 51, 28, 0);
	_gfx.PutPixel(0 + _x, 22 + _y, 51, 28, 0);
	_gfx.PutPixel(1 + _x, 22 + _y, 65, 36, 0);
	_gfx.PutPixel(2 + _x, 22 + _y, 65, 36, 0);
	_gfx.PutPixel(3 + _x, 22 + _y, 65, 36, 0);
	_gfx.PutPixel(4 + _x, 22 + _y, 65, 36, 0);
	_gfx.PutPixel(5 + _x, 22 + _y, 65, 36, 0);
	_gfx.PutPixel(6 + _x, 22 + _y, 51, 28, 0);
	_gfx.PutPixel(1 + _x, 23 + _y, 51, 28, 0);
	_gfx.PutPixel(2 + _x, 23 + _y, 51, 28, 0);
	_gfx.PutPixel(3 + _x, 23 + _y, 51, 28, 0);
	_gfx.PutPixel(4 + _x, 23 + _y, 51, 28, 0);
	_gfx.PutPixel(5 + _x, 23 + _y, 51, 28, 0);
	_gfx.PutPixel(6 + _x, 23 + _y, 51, 28, 0);
}

void Entities::renderDude(Graphics& _gfx, int _x, int _y, int _scale)
{
	_gfx.PutPixel((_scale * 7) + _x,(_scale * 0) + _y, 0, 0, 0);
	_gfx.PutPixel((_scale * 8) + _x,(_scale * 0) + _y, 0, 0, 0);
	_gfx.PutPixel((_scale * 9) + _x,(_scale * 0) + _y, 0, 0, 0);
	_gfx.PutPixel((_scale * 10) + _x,(_scale * 0) + _y, 0, 0, 0);
	_gfx.PutPixel((_scale * 11) + _x,(_scale * 0) + _y, 0, 0, 0);
	_gfx.PutPixel((_scale * 12) + _x,(_scale * 0) + _y, 0, 0, 0);
	_gfx.PutPixel((_scale * 5) + _x,(_scale * 1) + _y, 0, 0, 0);
	_gfx.PutPixel((_scale * 6) + _x,(_scale * 1) + _y, 0, 0, 0);
	_gfx.PutPixel((_scale * 7) + _x,(_scale * 1) + _y, 254, 221, 88);
	_gfx.PutPixel((_scale * 8) + _x,(_scale * 1) + _y, 254, 221, 88);
	_gfx.PutPixel((_scale * 9) + _x,(_scale * 1) + _y, 254, 221, 88);
	_gfx.PutPixel((_scale * 10) + _x,(_scale * 1) + _y, 254, 221, 88);
	_gfx.PutPixel((_scale * 11) + _x,(_scale * 1) + _y, 254, 221, 88);
	_gfx.PutPixel((_scale * 12) + _x,(_scale * 1) + _y, 254, 221, 88);
	_gfx.PutPixel((_scale * 13) + _x,(_scale * 1) + _y, 0, 0, 0);
	_gfx.PutPixel((_scale * 14) + _x,(_scale * 1) + _y, 0, 0, 0);
	_gfx.PutPixel((_scale * 3) + _x,(_scale * 2) + _y, 0, 0, 0);
	_gfx.PutPixel((_scale * 4) + _x,(_scale * 2) + _y, 0, 0, 0);
	_gfx.PutPixel((_scale * 5) + _x,(_scale * 2) + _y, 254, 221, 88);
	_gfx.PutPixel((_scale * 6) + _x,(_scale * 2) + _y, 254, 221, 88);
	_gfx.PutPixel((_scale * 7) + _x,(_scale * 2) + _y, 254, 221, 88);
	_gfx.PutPixel((_scale * 8) + _x,(_scale * 2) + _y, 254, 221, 88);
	_gfx.PutPixel((_scale * 9) + _x,(_scale * 2) + _y, 254, 221, 88);
	_gfx.PutPixel((_scale * 10) + _x,(_scale * 2) + _y, 254, 221, 88);
	_gfx.PutPixel((_scale * 11) + _x,(_scale * 2) + _y, 254, 221, 88);
	_gfx.PutPixel((_scale * 12) + _x,(_scale * 2) + _y, 254, 221, 88);
	_gfx.PutPixel((_scale * 13) + _x,(_scale * 2) + _y, 254, 221, 88);
	_gfx.PutPixel((_scale * 14) + _x,(_scale * 2) + _y, 254, 221, 88);
	_gfx.PutPixel((_scale * 15) + _x,(_scale * 2) + _y, 0, 0, 0);
	_gfx.PutPixel((_scale * 16) + _x,(_scale * 2) + _y, 0, 0, 0);
	_gfx.PutPixel((_scale * 2) + _x,(_scale * 3) + _y, 0, 0, 0);
	_gfx.PutPixel((_scale * 3) + _x,(_scale * 3) + _y, 254, 221, 88);
	_gfx.PutPixel((_scale * 4) + _x,(_scale * 3) + _y, 254, 221, 88);
	_gfx.PutPixel((_scale * 5) + _x,(_scale * 3) + _y, 254, 221, 88);
	_gfx.PutPixel((_scale * 6) + _x,(_scale * 3) + _y, 254, 221, 88);
	_gfx.PutPixel((_scale * 7) + _x,(_scale * 3) + _y, 254, 221, 88);
	_gfx.PutPixel((_scale * 8) + _x,(_scale * 3) + _y, 254, 221, 88);
	_gfx.PutPixel((_scale * 9) + _x,(_scale * 3) + _y, 254, 221, 88);
	_gfx.PutPixel((_scale * 10) + _x,(_scale * 3) + _y, 254, 221, 88);
	_gfx.PutPixel((_scale * 11) + _x,(_scale * 3) + _y, 254, 221, 88);
	_gfx.PutPixel((_scale * 12) + _x,(_scale * 3) + _y, 254, 221, 88);
	_gfx.PutPixel((_scale * 13) + _x,(_scale * 3) + _y, 254, 221, 88);
	_gfx.PutPixel((_scale * 14) + _x,(_scale * 3) + _y, 254, 221, 88);
	_gfx.PutPixel((_scale * 15) + _x,(_scale * 3) + _y, 254, 221, 88);
	_gfx.PutPixel((_scale * 16) + _x,(_scale * 3) + _y, 254, 221, 88);
	_gfx.PutPixel((_scale * 17) + _x,(_scale * 3) + _y, 0, 0, 0);
	_gfx.PutPixel((_scale * 2) + _x,(_scale * 4) + _y, 0, 0, 0);
	_gfx.PutPixel((_scale * 3) + _x,(_scale * 4) + _y, 254, 221, 88);
	_gfx.PutPixel((_scale * 4) + _x,(_scale * 4) + _y, 254, 221, 88);
	_gfx.PutPixel((_scale * 5) + _x,(_scale * 4) + _y, 254, 221, 88);
	_gfx.PutPixel((_scale * 6) + _x,(_scale * 4) + _y, 254, 221, 88);
	_gfx.PutPixel((_scale * 7) + _x,(_scale * 4) + _y, 254, 221, 88);
	_gfx.PutPixel((_scale * 8) + _x,(_scale * 4) + _y, 254, 221, 88);
	_gfx.PutPixel((_scale * 9) + _x,(_scale * 4) + _y, 254, 221, 88);
	_gfx.PutPixel((_scale * 10) + _x,(_scale * 4) + _y, 254, 221, 88);
	_gfx.PutPixel((_scale * 11) + _x,(_scale * 4) + _y, 254, 221, 88);
	_gfx.PutPixel((_scale * 12) + _x,(_scale * 4) + _y, 254, 221, 88);
	_gfx.PutPixel((_scale * 13) + _x,(_scale * 4) + _y, 254, 221, 88);
	_gfx.PutPixel((_scale * 14) + _x,(_scale * 4) + _y, 254, 221, 88);
	_gfx.PutPixel((_scale * 15) + _x,(_scale * 4) + _y, 254, 221, 88);
	_gfx.PutPixel((_scale * 16) + _x,(_scale * 4) + _y, 254, 221, 88);
	_gfx.PutPixel((_scale * 17) + _x,(_scale * 4) + _y, 0, 0, 0);
	_gfx.PutPixel((_scale * 1) + _x,(_scale * 5) + _y, 0, 0, 0);
	_gfx.PutPixel((_scale * 2) + _x,(_scale * 5) + _y, 254, 221, 88);
	_gfx.PutPixel((_scale * 3) + _x,(_scale * 5) + _y, 0, 0, 0);
	_gfx.PutPixel((_scale * 4) + _x,(_scale * 5) + _y, 0, 0, 0);
	_gfx.PutPixel((_scale * 5) + _x,(_scale * 5) + _y, 254, 221, 88);
	_gfx.PutPixel((_scale * 6) + _x,(_scale * 5) + _y, 254, 221, 88);
	_gfx.PutPixel((_scale * 7) + _x,(_scale * 5) + _y, 254, 221, 88);
	_gfx.PutPixel((_scale * 8) + _x,(_scale * 5) + _y, 254, 221, 88);
	_gfx.PutPixel((_scale * 9) + _x,(_scale * 5) + _y, 254, 221, 88);
	_gfx.PutPixel((_scale * 10) + _x,(_scale * 5) + _y, 254, 221, 88);
	_gfx.PutPixel((_scale * 11) + _x,(_scale * 5) + _y, 0, 0, 0);
	_gfx.PutPixel((_scale * 12) + _x,(_scale * 5) + _y, 0, 0, 0);
	_gfx.PutPixel((_scale * 13) + _x,(_scale * 5) + _y, 0, 0, 0);
	_gfx.PutPixel((_scale * 14) + _x,(_scale * 5) + _y, 0, 0, 0);
	_gfx.PutPixel((_scale * 15) + _x,(_scale * 5) + _y, 254, 221, 88);
	_gfx.PutPixel((_scale * 16) + _x,(_scale * 5) + _y, 254, 221, 88);
	_gfx.PutPixel((_scale * 17) + _x,(_scale * 5) + _y, 254, 221, 88);
	_gfx.PutPixel((_scale * 18) + _x,(_scale * 5) + _y, 0, 0, 0);
	_gfx.PutPixel((_scale * 1) + _x,(_scale * 6) + _y, 0, 0, 0);
	_gfx.PutPixel((_scale * 2) + _x,(_scale * 6) + _y, 0, 0, 0);
	_gfx.PutPixel((_scale * 3) + _x,(_scale * 6) + _y, 255, 255, 255);
	_gfx.PutPixel((_scale * 4) + _x,(_scale * 6) + _y, 0, 0, 0);
	_gfx.PutPixel((_scale * 5) + _x,(_scale * 6) + _y, 0, 0, 0);
	_gfx.PutPixel((_scale * 6) + _x,(_scale * 6) + _y, 254, 221, 88);
	_gfx.PutPixel((_scale * 7) + _x,(_scale * 6) + _y, 254, 221, 88);
	_gfx.PutPixel((_scale * 8) + _x,(_scale * 6) + _y, 254, 221, 88);
	_gfx.PutPixel((_scale * 9) + _x,(_scale * 6) + _y, 254, 221, 88);
	_gfx.PutPixel((_scale * 10) + _x,(_scale * 6) + _y, 0, 0, 0);
	_gfx.PutPixel((_scale * 11) + _x,(_scale * 6) + _y, 255, 255, 255);
	_gfx.PutPixel((_scale * 12) + _x,(_scale * 6) + _y, 255, 255, 255);
	_gfx.PutPixel((_scale * 13) + _x,(_scale * 6) + _y, 0, 0, 0);
	_gfx.PutPixel((_scale * 14) + _x,(_scale * 6) + _y, 0, 0, 0);
	_gfx.PutPixel((_scale * 15) + _x,(_scale * 6) + _y, 0, 0, 0);
	_gfx.PutPixel((_scale * 16) + _x,(_scale * 6) + _y, 254, 221, 88);
	_gfx.PutPixel((_scale * 17) + _x,(_scale * 6) + _y, 254, 221, 88);
	_gfx.PutPixel((_scale * 18) + _x,(_scale * 6) + _y, 0, 0, 0);
	_gfx.PutPixel((_scale * 0) + _x,(_scale * 7) + _y, 0, 0, 0);
	_gfx.PutPixel((_scale * 1) + _x,(_scale * 7) + _y, 0, 0, 0);
	_gfx.PutPixel((_scale * 2) + _x,(_scale * 7) + _y, 255, 255, 255);
	_gfx.PutPixel((_scale * 3) + _x,(_scale * 7) + _y, 255, 255, 255);
	_gfx.PutPixel((_scale * 4) + _x,(_scale * 7) + _y, 0, 0, 0);
	_gfx.PutPixel((_scale * 5) + _x,(_scale * 7) + _y, 0, 0, 0);
	_gfx.PutPixel((_scale * 6) + _x,(_scale * 7) + _y, 254, 221, 88);
	_gfx.PutPixel((_scale * 7) + _x,(_scale * 7) + _y, 254, 221, 88);
	_gfx.PutPixel((_scale * 8) + _x,(_scale * 7) + _y, 254, 221, 88);
	_gfx.PutPixel((_scale * 9) + _x,(_scale * 7) + _y, 254, 221, 88);
	_gfx.PutPixel((_scale * 10) + _x,(_scale * 7) + _y, 0, 0, 0);
	_gfx.PutPixel((_scale * 11) + _x,(_scale * 7) + _y, 255, 255, 255);
	_gfx.PutPixel((_scale * 12) + _x,(_scale * 7) + _y, 255, 255, 255);
	_gfx.PutPixel((_scale * 13) + _x,(_scale * 7) + _y, 0, 0, 0);
	_gfx.PutPixel((_scale * 14) + _x,(_scale * 7) + _y, 0, 0, 0);
	_gfx.PutPixel((_scale * 15) + _x,(_scale * 7) + _y, 0, 0, 0);
	_gfx.PutPixel((_scale * 16) + _x,(_scale * 7) + _y, 254, 221, 88);
	_gfx.PutPixel((_scale * 17) + _x,(_scale * 7) + _y, 254, 221, 88);
	_gfx.PutPixel((_scale * 18) + _x,(_scale * 7) + _y, 254, 221, 88);
	_gfx.PutPixel((_scale * 19) + _x,(_scale * 7) + _y, 0, 0, 0);
	_gfx.PutPixel((_scale * 0) + _x,(_scale * 8) + _y, 0, 0, 0);
	_gfx.PutPixel((_scale * 1) + _x,(_scale * 8) + _y, 0, 0, 0);
	_gfx.PutPixel((_scale * 2) + _x,(_scale * 8) + _y, 255, 255, 255);
	_gfx.PutPixel((_scale * 3) + _x,(_scale * 8) + _y, 255, 255, 255);
	_gfx.PutPixel((_scale * 4) + _x,(_scale * 8) + _y, 255, 255, 255);
	_gfx.PutPixel((_scale * 5) + _x,(_scale * 8) + _y, 0, 0, 0);
	_gfx.PutPixel((_scale * 6) + _x,(_scale * 8) + _y, 254, 221, 88);
	_gfx.PutPixel((_scale * 7) + _x,(_scale * 8) + _y, 254, 221, 88);
	_gfx.PutPixel((_scale * 8) + _x,(_scale * 8) + _y, 254, 221, 88);
	_gfx.PutPixel((_scale * 9) + _x,(_scale * 8) + _y, 254, 221, 88);
	_gfx.PutPixel((_scale * 10) + _x,(_scale * 8) + _y, 0, 0, 0);
	_gfx.PutPixel((_scale * 11) + _x,(_scale * 8) + _y, 255, 255, 255);
	_gfx.PutPixel((_scale * 12) + _x,(_scale * 8) + _y, 255, 255, 255);
	_gfx.PutPixel((_scale * 13) + _x,(_scale * 8) + _y, 255, 255, 255);
	_gfx.PutPixel((_scale * 14) + _x,(_scale * 8) + _y, 255, 255, 255);
	_gfx.PutPixel((_scale * 15) + _x,(_scale * 8) + _y, 0, 0, 0);
	_gfx.PutPixel((_scale * 16) + _x,(_scale * 8) + _y, 254, 221, 88);
	_gfx.PutPixel((_scale * 17) + _x,(_scale * 8) + _y, 254, 221, 88);
	_gfx.PutPixel((_scale * 18) + _x,(_scale * 8) + _y, 254, 221, 88);
	_gfx.PutPixel((_scale * 19) + _x,(_scale * 8) + _y, 0, 0, 0);
	_gfx.PutPixel((_scale * 0) + _x,(_scale * 9) + _y, 0, 0, 0);
	_gfx.PutPixel((_scale * 1) + _x,(_scale * 9) + _y, 254, 221, 88);
	_gfx.PutPixel((_scale * 2) + _x,(_scale * 9) + _y, 0, 0, 0);
	_gfx.PutPixel((_scale * 3) + _x,(_scale * 9) + _y, 0, 0, 0);
	_gfx.PutPixel((_scale * 4) + _x,(_scale * 9) + _y, 0, 0, 0);
	_gfx.PutPixel((_scale * 5) + _x,(_scale * 9) + _y, 0, 0, 0);
	_gfx.PutPixel((_scale * 6) + _x,(_scale * 9) + _y, 254, 221, 88);
	_gfx.PutPixel((_scale * 7) + _x,(_scale * 9) + _y, 254, 221, 88);
	_gfx.PutPixel((_scale * 8) + _x,(_scale * 9) + _y, 254, 221, 88);
	_gfx.PutPixel((_scale * 9) + _x,(_scale * 9) + _y, 254, 221, 88);
	_gfx.PutPixel((_scale * 10) + _x,(_scale * 9) + _y, 254, 221, 88);
	_gfx.PutPixel((_scale * 11) + _x,(_scale * 9) + _y, 0, 0, 0);
	_gfx.PutPixel((_scale * 12) + _x,(_scale * 9) + _y, 0, 0, 0);
	_gfx.PutPixel((_scale * 13) + _x,(_scale * 9) + _y, 0, 0, 0);
	_gfx.PutPixel((_scale * 14) + _x,(_scale * 9) + _y, 0, 0, 0);
	_gfx.PutPixel((_scale * 15) + _x,(_scale * 9) + _y, 254, 221, 88);
	_gfx.PutPixel((_scale * 16) + _x,(_scale * 9) + _y, 254, 221, 88);
	_gfx.PutPixel((_scale * 17) + _x,(_scale * 9) + _y, 254, 221, 88);
	_gfx.PutPixel((_scale * 18) + _x,(_scale * 9) + _y, 254, 221, 88);
	_gfx.PutPixel((_scale * 19) + _x,(_scale * 9) + _y, 0, 0, 0);
	_gfx.PutPixel((_scale * 0) + _x,(_scale * 10) + _y, 0, 0, 0);
	_gfx.PutPixel((_scale * 1) + _x,(_scale * 10) + _y, 254, 221, 88);
	_gfx.PutPixel((_scale * 2) + _x,(_scale * 10) + _y, 254, 221, 88);
	_gfx.PutPixel((_scale * 3) + _x,(_scale * 10) + _y, 254, 221, 88);
	_gfx.PutPixel((_scale * 4) + _x,(_scale * 10) + _y, 254, 221, 88);
	_gfx.PutPixel((_scale * 5) + _x,(_scale * 10) + _y, 254, 221, 88);
	_gfx.PutPixel((_scale * 6) + _x,(_scale * 10) + _y, 254, 221, 88);
	_gfx.PutPixel((_scale * 7) + _x,(_scale * 10) + _y, 254, 221, 88);
	_gfx.PutPixel((_scale * 8) + _x,(_scale * 10) + _y, 254, 221, 88);
	_gfx.PutPixel((_scale * 9) + _x,(_scale * 10) + _y, 254, 221, 88);
	_gfx.PutPixel((_scale * 10) + _x,(_scale * 10) + _y, 254, 221, 88);
	_gfx.PutPixel((_scale * 11) + _x,(_scale * 10) + _y, 254, 221, 88);
	_gfx.PutPixel((_scale * 12) + _x,(_scale * 10) + _y, 254, 221, 88);
	_gfx.PutPixel((_scale * 13) + _x,(_scale * 10) + _y, 254, 221, 88);
	_gfx.PutPixel((_scale * 14) + _x,(_scale * 10) + _y, 254, 221, 88);
	_gfx.PutPixel((_scale * 15) + _x,(_scale * 10) + _y, 254, 221, 88);
	_gfx.PutPixel((_scale * 16) + _x,(_scale * 10) + _y, 254, 221, 88);
	_gfx.PutPixel((_scale * 17) + _x,(_scale * 10) + _y, 254, 221, 88);
	_gfx.PutPixel((_scale * 18) + _x,(_scale * 10) + _y, 254, 221, 88);
	_gfx.PutPixel((_scale * 19) + _x,(_scale * 10) + _y, 0, 0, 0);
	_gfx.PutPixel((_scale * 0) + _x,(_scale * 11) + _y, 0, 0, 0);
	_gfx.PutPixel((_scale * 1) + _x,(_scale * 11) + _y, 254, 221, 88);
	_gfx.PutPixel((_scale * 2) + _x,(_scale * 11) + _y, 254, 221, 88);
	_gfx.PutPixel((_scale * 3) + _x,(_scale * 11) + _y, 254, 221, 88);
	_gfx.PutPixel((_scale * 4) + _x,(_scale * 11) + _y, 254, 221, 88);
	_gfx.PutPixel((_scale * 5) + _x,(_scale * 11) + _y, 254, 221, 88);
	_gfx.PutPixel((_scale * 6) + _x,(_scale * 11) + _y, 254, 221, 88);
	_gfx.PutPixel((_scale * 7) + _x,(_scale * 11) + _y, 20, 14, 18);
	_gfx.PutPixel((_scale * 8) + _x,(_scale * 11) + _y, 18, 11, 14);
	_gfx.PutPixel((_scale * 9) + _x,(_scale * 11) + _y, 18, 12, 14);
	_gfx.PutPixel((_scale * 10) + _x,(_scale * 11) + _y, 18, 12, 14);
	_gfx.PutPixel((_scale * 11) + _x,(_scale * 11) + _y, 21, 13, 16);
	_gfx.PutPixel((_scale * 12) + _x,(_scale * 11) + _y, 24, 11, 15);
	_gfx.PutPixel((_scale * 13) + _x,(_scale * 11) + _y, 0, 0, 0);
	_gfx.PutPixel((_scale * 14) + _x,(_scale * 11) + _y, 254, 221, 88);
	_gfx.PutPixel((_scale * 15) + _x,(_scale * 11) + _y, 254, 221, 88);
	_gfx.PutPixel((_scale * 16) + _x,(_scale * 11) + _y, 254, 221, 88);
	_gfx.PutPixel((_scale * 17) + _x,(_scale * 11) + _y, 254, 221, 88);
	_gfx.PutPixel((_scale * 18) + _x,(_scale * 11) + _y, 254, 221, 88);
	_gfx.PutPixel((_scale * 19) + _x,(_scale * 11) + _y, 0, 0, 0);
	_gfx.PutPixel((_scale * 0) + _x,(_scale * 12) + _y, 0, 0, 0);
	_gfx.PutPixel((_scale * 1) + _x,(_scale * 12) + _y, 254, 221, 88);
	_gfx.PutPixel((_scale * 2) + _x,(_scale * 12) + _y, 254, 221, 88);
	_gfx.PutPixel((_scale * 3) + _x,(_scale * 12) + _y, 254, 221, 88);
	_gfx.PutPixel((_scale * 4) + _x,(_scale * 12) + _y, 254, 221, 88);
	_gfx.PutPixel((_scale * 5) + _x,(_scale * 12) + _y, 254, 221, 88);
	_gfx.PutPixel((_scale * 6) + _x,(_scale * 12) + _y, 23, 9, 23);
	_gfx.PutPixel((_scale * 7) + _x,(_scale * 12) + _y, 135, 26, 68);
	_gfx.PutPixel((_scale * 8) + _x,(_scale * 12) + _y, 135, 26, 68);
	_gfx.PutPixel((_scale * 9) + _x,(_scale * 12) + _y, 135, 26, 68);
	_gfx.PutPixel((_scale * 10) + _x,(_scale * 12) + _y, 135, 26, 68);
	_gfx.PutPixel((_scale * 11) + _x,(_scale * 12) + _y, 135, 26, 68);
	_gfx.PutPixel((_scale * 12) + _x,(_scale * 12) + _y, 135, 26, 68);
	_gfx.PutPixel((_scale * 13) + _x,(_scale * 12) + _y, 135, 26, 68);
	_gfx.PutPixel((_scale * 14) + _x,(_scale * 12) + _y, 0, 0, 0);
	_gfx.PutPixel((_scale * 15) + _x,(_scale * 12) + _y, 254, 221, 88);
	_gfx.PutPixel((_scale * 16) + _x,(_scale * 12) + _y, 254, 221, 88);
	_gfx.PutPixel((_scale * 17) + _x,(_scale * 12) + _y, 254, 221, 88);
	_gfx.PutPixel((_scale * 18) + _x,(_scale * 12) + _y, 254, 221, 88);
	_gfx.PutPixel((_scale * 19) + _x,(_scale * 12) + _y, 0, 0, 0);
	_gfx.PutPixel((_scale * 1) + _x,(_scale * 13) + _y, 0, 0, 0);
	_gfx.PutPixel((_scale * 2) + _x,(_scale * 13) + _y, 254, 221, 88);
	_gfx.PutPixel((_scale * 3) + _x,(_scale * 13) + _y, 254, 221, 88);
	_gfx.PutPixel((_scale * 4) + _x,(_scale * 13) + _y, 254, 221, 88);
	_gfx.PutPixel((_scale * 5) + _x,(_scale * 13) + _y, 0, 0, 0);
	_gfx.PutPixel((_scale * 6) + _x,(_scale * 13) + _y, 135, 26, 68);
	_gfx.PutPixel((_scale * 7) + _x,(_scale * 13) + _y, 135, 26, 68);
	_gfx.PutPixel((_scale * 8) + _x,(_scale * 13) + _y, 135, 26, 68);
	_gfx.PutPixel((_scale * 9) + _x,(_scale * 13) + _y, 135, 26, 68);
	_gfx.PutPixel((_scale * 10) + _x,(_scale * 13) + _y, 135, 26, 68);
	_gfx.PutPixel((_scale * 11) + _x,(_scale * 13) + _y, 135, 26, 68);
	_gfx.PutPixel((_scale * 12) + _x,(_scale * 13) + _y, 135, 26, 68);
	_gfx.PutPixel((_scale * 13) + _x,(_scale * 13) + _y, 135, 26, 68);
	_gfx.PutPixel((_scale * 14) + _x,(_scale * 13) + _y, 135, 26, 68);
	_gfx.PutPixel((_scale * 15) + _x,(_scale * 13) + _y, 0, 0, 0);
	_gfx.PutPixel((_scale * 16) + _x,(_scale * 13) + _y, 254, 221, 88);
	_gfx.PutPixel((_scale * 17) + _x,(_scale * 13) + _y, 254, 221, 88);
	_gfx.PutPixel((_scale * 18) + _x,(_scale * 13) + _y, 0, 0, 0);
	_gfx.PutPixel((_scale * 1) + _x,(_scale * 14) + _y, 0, 0, 0);
	_gfx.PutPixel((_scale * 2) + _x,(_scale * 14) + _y, 254, 221, 88);
	_gfx.PutPixel((_scale * 3) + _x,(_scale * 14) + _y, 254, 221, 88);
	_gfx.PutPixel((_scale * 4) + _x,(_scale * 14) + _y, 0, 0, 0);
	_gfx.PutPixel((_scale * 5) + _x,(_scale * 14) + _y, 135, 26, 68);
	_gfx.PutPixel((_scale * 6) + _x,(_scale * 14) + _y, 135, 26, 68);
	_gfx.PutPixel((_scale * 7) + _x,(_scale * 14) + _y, 135, 26, 68);
	_gfx.PutPixel((_scale * 8) + _x,(_scale * 14) + _y, 135, 26, 68);
	_gfx.PutPixel((_scale * 9) + _x,(_scale * 14) + _y, 251, 192, 224);
	_gfx.PutPixel((_scale * 10) + _x,(_scale * 14) + _y, 251, 192, 224);
	_gfx.PutPixel((_scale * 11) + _x,(_scale * 14) + _y, 251, 192, 224);
	_gfx.PutPixel((_scale * 12) + _x,(_scale * 14) + _y, 251, 192, 224);
	_gfx.PutPixel((_scale * 13) + _x,(_scale * 14) + _y, 135, 26, 68);
	_gfx.PutPixel((_scale * 14) + _x,(_scale * 14) + _y, 135, 26, 68);
	_gfx.PutPixel((_scale * 15) + _x,(_scale * 14) + _y, 0, 0, 0);
	_gfx.PutPixel((_scale * 16) + _x,(_scale * 14) + _y, 254, 221, 88);
	_gfx.PutPixel((_scale * 17) + _x,(_scale * 14) + _y, 254, 221, 88);
	_gfx.PutPixel((_scale * 18) + _x,(_scale * 14) + _y, 0, 0, 0);
	_gfx.PutPixel((_scale * 2) + _x,(_scale * 15) + _y, 0, 0, 0);
	_gfx.PutPixel((_scale * 3) + _x,(_scale * 15) + _y, 254, 221, 88);
	_gfx.PutPixel((_scale * 4) + _x,(_scale * 15) + _y, 0, 0, 0);
	_gfx.PutPixel((_scale * 5) + _x,(_scale * 15) + _y, 135, 26, 68);
	_gfx.PutPixel((_scale * 6) + _x,(_scale * 15) + _y, 135, 26, 68);
	_gfx.PutPixel((_scale * 7) + _x,(_scale * 15) + _y, 135, 26, 68);
	_gfx.PutPixel((_scale * 8) + _x,(_scale * 15) + _y, 251, 192, 224);
	_gfx.PutPixel((_scale * 9) + _x,(_scale * 15) + _y, 251, 192, 224);
	_gfx.PutPixel((_scale * 10) + _x,(_scale * 15) + _y, 251, 192, 224);
	_gfx.PutPixel((_scale * 11) + _x,(_scale * 15) + _y, 251, 192, 224);
	_gfx.PutPixel((_scale * 12) + _x,(_scale * 15) + _y, 251, 192, 224);
	_gfx.PutPixel((_scale * 13) + _x,(_scale * 15) + _y, 251, 192, 224);
	_gfx.PutPixel((_scale * 14) + _x,(_scale * 15) + _y, 135, 26, 68);
	_gfx.PutPixel((_scale * 15) + _x,(_scale * 15) + _y, 0, 0, 0);
	_gfx.PutPixel((_scale * 16) + _x,(_scale * 15) + _y, 254, 221, 88);
	_gfx.PutPixel((_scale * 17) + _x,(_scale * 15) + _y, 0, 0, 0);
	_gfx.PutPixel((_scale * 2) + _x,(_scale * 16) + _y, 0, 0, 0);
	_gfx.PutPixel((_scale * 3) + _x,(_scale * 16) + _y, 254, 221, 88);
	_gfx.PutPixel((_scale * 4) + _x,(_scale * 16) + _y, 0, 0, 0);
	_gfx.PutPixel((_scale * 5) + _x,(_scale * 16) + _y, 135, 26, 68);
	_gfx.PutPixel((_scale * 6) + _x,(_scale * 16) + _y, 135, 26, 68);
	_gfx.PutPixel((_scale * 7) + _x,(_scale * 16) + _y, 135, 26, 68);
	_gfx.PutPixel((_scale * 8) + _x,(_scale * 16) + _y, 251, 192, 224);
	_gfx.PutPixel((_scale * 9) + _x,(_scale * 16) + _y, 251, 192, 224);
	_gfx.PutPixel((_scale * 10) + _x,(_scale * 16) + _y, 251, 192, 224);
	_gfx.PutPixel((_scale * 11) + _x,(_scale * 16) + _y, 251, 192, 224);
	_gfx.PutPixel((_scale * 12) + _x,(_scale * 16) + _y, 251, 192, 224);
	_gfx.PutPixel((_scale * 13) + _x,(_scale * 16) + _y, 251, 192, 224);
	_gfx.PutPixel((_scale * 14) + _x,(_scale * 16) + _y, 135, 26, 68);
	_gfx.PutPixel((_scale * 15) + _x,(_scale * 16) + _y, 0, 0, 0);
	_gfx.PutPixel((_scale * 16) + _x,(_scale * 16) + _y, 254, 221, 88);
	_gfx.PutPixel((_scale * 17) + _x,(_scale * 16) + _y, 0, 0, 0);
	_gfx.PutPixel((_scale * 3) + _x,(_scale * 17) + _y, 0, 0, 0);
	_gfx.PutPixel((_scale * 4) + _x,(_scale * 17) + _y, 0, 0, 0);
	_gfx.PutPixel((_scale * 5) + _x,(_scale * 17) + _y, 0, 0, 0);
	_gfx.PutPixel((_scale * 6) + _x,(_scale * 17) + _y, 0, 0, 0);
	_gfx.PutPixel((_scale * 7) + _x,(_scale * 17) + _y, 0, 0, 0);
	_gfx.PutPixel((_scale * 8) + _x,(_scale * 17) + _y, 0, 0, 0);
	_gfx.PutPixel((_scale * 9) + _x,(_scale * 17) + _y, 0, 0, 0);
	_gfx.PutPixel((_scale * 10) + _x,(_scale * 17) + _y, 0, 0, 0);
	_gfx.PutPixel((_scale * 11) + _x,(_scale * 17) + _y, 0, 0, 0);
	_gfx.PutPixel((_scale * 12) + _x,(_scale * 17) + _y, 0, 0, 0);
	_gfx.PutPixel((_scale * 13) + _x,(_scale * 17) + _y, 0, 0, 0);
	_gfx.PutPixel((_scale * 14) + _x,(_scale * 17) + _y, 0, 0, 0);
	_gfx.PutPixel((_scale * 15) + _x,(_scale * 17) + _y, 0, 0, 0);
	_gfx.PutPixel((_scale * 16) + _x,(_scale * 17) + _y, 0, 0, 0);
	_gfx.PutPixel((_scale * 5) + _x,(_scale * 18) + _y, 0, 0, 0);
	_gfx.PutPixel((_scale * 6) + _x,(_scale * 18) + _y, 0, 0, 0);
	_gfx.PutPixel((_scale * 7) + _x,(_scale * 18) + _y, 254, 221, 88);
	_gfx.PutPixel((_scale * 8) + _x,(_scale * 18) + _y, 254, 221, 88);
	_gfx.PutPixel((_scale * 9) + _x,(_scale * 18) + _y, 254, 221, 88);
	_gfx.PutPixel((_scale * 10) + _x,(_scale * 18) + _y, 254, 221, 88);
	_gfx.PutPixel((_scale * 11) + _x,(_scale * 18) + _y, 254, 221, 88);
	_gfx.PutPixel((_scale * 12) + _x,(_scale * 18) + _y, 254, 221, 88);
	_gfx.PutPixel((_scale * 13) + _x,(_scale * 18) + _y, 0, 0, 0);
	_gfx.PutPixel((_scale * 14) + _x,(_scale * 18) + _y, 0, 0, 0);
	_gfx.PutPixel((_scale * 7) + _x,(_scale * 19) + _y, 0, 0, 0);
	_gfx.PutPixel((_scale * 8) + _x,(_scale * 19) + _y, 0, 0, 0);
	_gfx.PutPixel((_scale * 9) + _x,(_scale * 19) + _y, 0, 0, 0);
	_gfx.PutPixel((_scale * 10) + _x,(_scale * 19) + _y, 0, 0, 0);
	_gfx.PutPixel((_scale * 11) + _x,(_scale * 19) + _y, 0, 0, 0);
	_gfx.PutPixel((_scale * 12) + _x,(_scale * 19) + _y, 0, 0, 0);
}