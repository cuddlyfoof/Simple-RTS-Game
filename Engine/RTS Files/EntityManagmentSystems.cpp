#include "EntityManagmentSystems.h"
#include "../Graphics.h"
#include <cmath>
#include "../Game.h"

#define DUDE 0
#define POO 2
#define DUDEHIVE 1
#define POOHIVE 3

EntityManagmentSystems::EntityManagmentSystems()
{
}

EntityManagmentSystems::EntityManagmentSystems(EntStruct& _ents)
{
	addEntity(_ents, DUDEHIVE, 100, 450);
	addEntity(_ents, POOHIVE, 1340, 450);
	addEntity(_ents, POO, 1200, 450);
}

void EntityManagmentSystems::moveSelectedDudes(std::vector<Vector6>& _static, std::vector<Vector6>& _moving, int _x, int _y)
{
	for (auto dude : _static)
	{
		_moving.emplace_back(std::move(dude));
	}
	for (auto& dude : _moving)
	{
		dude.dx = (float)_x;
		dude.dy = (float)_y;
	}
	_static.clear();
}

void EntityManagmentSystems::addEntityToQueue(EntStruct& _ents, int _entNum, int _x, int _y)
{
	switch (_entNum)
	{
	//Add Dude : 0
	case 0 :
		if (resources >= 50)
		{
			if (_ents.selectedDudeHivesPos.size() > 0)
			{
				addEntity(_ents, _entNum, _ents.selectedDudeHivesPos.back().x, _ents.selectedDudeHivesPos.back().y);
				resources -= 50;
			}
		}
		break;
	//Add Hive : 1
	case 1 :
		if (resources >= 200)
		{			
			if (_ents.staticSelectedDudesPos.size() > 0)
			{
				_ents.staticSelectedDudesPos.back().dx = (float)_x;
				_ents.staticSelectedDudesPos.back().dy = (float)_y;
				_ents.queuedEntities.emplace_back(uuid, _ents.staticSelectedDudesPos.back().id, _x, _y, _entNum);
				_ents.movingSelectedDudesPos.emplace_back(std::move(_ents.staticSelectedDudesPos.back()));
				_ents.staticSelectedDudesPos.pop_back();
				resources -= 200;
				uuid++;
			}
			else if (_ents.movingSelectedDudesPos.size() > 0)
			{
				_ents.movingSelectedDudesPos.back().dx = _x;
				_ents.movingSelectedDudesPos.back().dy = _y;
				_ents.queuedEntities.emplace_back(uuid, _ents.staticSelectedDudesPos[0].id, _x, _y, _entNum);
				resources -= 200;
				uuid++;
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

void EntityManagmentSystems::checkEntityQueue(EntStruct& _ents)
{
	auto doCirclesOverlap = [](float x1, float y1, float r1, float x2, float y2, float r2)
	{
		return (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2) <= (r1 + r2) * (r1 + r2);
	};

	float buildingRadius = 0.0f;
	bool builderHasArrived = false;

	for (auto it{ _ents.queuedEntities.begin()}; it != _ents.queuedEntities.end();)
	{
		switch (it->entNum)
		{
		case 1 :
			buildingRadius = Hive::radius;
			break;
		default:
			break;
		}
		for (auto dude : _ents.movingSelectedDudesPos)
		{
			if (doCirclesOverlap(dude.x, dude.y, Dude::radius, it->x, it->y, buildingRadius) && dude.id == it->builderUuid)
			{
				builderHasArrived = true;
				break;
			}
		}
		if (builderHasArrived)
		{
			switch (it->entNum)
			{
			case 1:
				_ents.dudeHivesPos.emplace_back(it->x, it->y, it->uuid);
				_ents.dudeHives.emplace_back(it->uuid);
				it = _ents.queuedEntities.erase(it);
			default:
				break;
			}
		}
		else
		{
			it++;
		}
	}
}

void EntityManagmentSystems::addEntity(EntStruct& _entStruct, int _entNum, int _x, int _y)
{	
	switch (_entNum)
	{
	//Units
	case DUDE :
		_entStruct.staticDudesPos.emplace_back(_x, _y, uuid);
		_entStruct.dudes.emplace_back(uuid);
		break;
	case POO :
		_entStruct.poosPos.emplace_back(_x, _y, uuid);
		_entStruct.poos.emplace_back(uuid);
		break;
	//Buildings
	case DUDEHIVE:
		_entStruct.dudeHivesPos.emplace_back(_x, _y, uuid);
		_entStruct.dudeHives.emplace_back(uuid);
		break;
	case POOHIVE:
		_entStruct.pooHivesPos.emplace_back(_x, _y, uuid);
		_entStruct.pooHives.emplace_back(uuid);
		break;
	default:
		break;
	}
	uuid++;
}

void EntityManagmentSystems::removeEntity(EntStruct& _entStruct, const int _entNum, const int _uuid)
{
	auto checkVector6Uuid = [&_uuid](std::vector<Vector6>& _ents) 
	{
		for (auto it{ _ents.begin() }; it != _ents.end();) 
		{
			if (it->id == _uuid)
			{
				it = _ents.erase(it);
				break;
			}
			else
			{
				it++;
			}
		}
	};

	auto checkVector2Uuid = [&_uuid](std::vector<Vector2>& _ents)
	{
		for (auto it{ _ents.begin() }; it != _ents.end();)
		{
			if (it->id == _uuid)
			{
				it = _ents.erase(it);
				break;
			}
			else
			{
				it++;
			}
		}
	};

	switch (_entNum)
	{
	//Units ***************************************************
	case DUDE :
		checkVector6Uuid(_entStruct.staticSelectedDudesPos);
		checkVector6Uuid(_entStruct.movingSelectedDudesPos);
		checkVector6Uuid(_entStruct.staticDudesPos);
		checkVector6Uuid(_entStruct.movingDudesPos);
		for (auto it{ _entStruct.dudes.begin() }; it != _entStruct.dudes.end();)
		{
			if (it->posID == _uuid)
			{
				it = _entStruct.dudes.erase(it);
				break;
			}
			else
			{
				it++;
			}
		}
		break;
	case POO:
		checkVector6Uuid(_entStruct.poosPos);
		for (auto it{ _entStruct.poos.begin() }; it != _entStruct.poos.end();)
		{
			if (it->posID == _uuid)
			{
				it = _entStruct.poos.erase(it);
				break;
			}
			else
			{
				it++;
			}
		}
		break;
	//Buildings *******************************************
	case DUDEHIVE:
		checkVector2Uuid(_entStruct.dudeHivesPos);
		for (auto it{ _entStruct.dudeHives.begin() }; it != _entStruct.dudeHives.end();)
		{
			if (it->posID == _uuid)
			{
				it = _entStruct.dudeHives.erase(it);
				break;
			}
			else
			{
				it++;
			}
		}
		break;
	case POOHIVE:
		checkVector2Uuid(_entStruct.pooHivesPos);
		for (auto it{ _entStruct.pooHives.begin() }; it != _entStruct.pooHives.end();)
		{
			if (it->posID == _uuid)
			{
				it = _entStruct.pooHives.erase(it);
				break;
			}
			else
			{
				it++;
			}
		}
		break;
	default:
		break;
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

void EntityManagmentSystems::updatePositions(std::vector<Vector6>& _entsFrom, std::vector<Vector6>& _entsTo, const float _dt)
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
			it->x += it->vX * _dt;
			it->y += it->vY * _dt;
			it++;
		}		
	}
}

void EntityManagmentSystems::collisionCheck(std::vector<Vector6>& ents1, std::vector<Vector6>& ents2, const float _dt)
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

					it1->x += it1->vX * _dt;
					it1->y += it1->vY * _dt;

					it2->x += it2->vX * _dt;
					it2->y += it2->vY * _dt;
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

void EntityManagmentSystems::update(EntStruct& _ents, const float _dt)
{	
	//move Dudes
	updatePositions(_ents.movingDudesPos, _ents.staticDudesPos, _dt);
	updatePositions(_ents.movingSelectedDudesPos, _ents.staticSelectedDudesPos, _dt);
	runCollisions(_ents, _dt);

	//Metrics

	trackHealth(_ents, _dt);

	//building check
	checkEntityQueue(_ents);
}

void EntityManagmentSystems::selectEntities(MainWindow& _wnd, EntStruct& _ents, int _x, int _y)
{	
	selectVector6(_wnd, _ents.staticDudesPos, _ents.staticSelectedDudesPos, _x, _y);
	selectVector6(_wnd, _ents.movingDudesPos, _ents.movingSelectedDudesPos, _x, _y);
	selectVector2(_wnd, _ents.dudeHivesPos, _ents.selectedDudeHivesPos, _x, _y);
}

void EntityManagmentSystems::selectVector6(MainWindow& _wnd, std::vector<Vector6>& _entsFrom, std::vector<Vector6>& _entsTo, const int x, const int y)
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

void EntityManagmentSystems::selectVector2(MainWindow& _wnd, std::vector<Vector2>& _entsFrom, std::vector<Vector2>& _entsTo, const int x, const int y)
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

void EntityManagmentSystems::trackHealth(EntStruct& _ents, const float _dt)
{
	for (auto it{ _ents.healthTracker.begin() }; it != _ents.healthTracker.end();)
	{
		if (it->health <= 0.0f)
		{
			removeEntity(_ents, it->entNum, it->uuid);
			it = _ents.healthTracker.erase(it);
		}
		else
		{
			it->health -= it->damageTaking * _dt;
			it++;
		}
	}
}

void EntityManagmentSystems::attackRangeCheck(std::vector<Vector6>& _atackeingEnt, std::vector<Vector6>& _entTakingDamage)
{
	auto doCirclesOverlap = [](float x1, float y1, float r1, float x2, float y2, float r2)
	{
		return std::fabs((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2)) <= (r1 + r2) * (r1 + r2);
	};

	

}

void EntityManagmentSystems::runCollisions(EntStruct& _ents, const float _dt)
{
	//All the Collision Checks
	//total entities to check : 4
	//movingSelectedDudesPos
	collisionCheck(_ents.movingSelectedDudesPos, _ents.movingSelectedDudesPos, _dt);
	collisionCheck(_ents.movingSelectedDudesPos, _ents.movingDudesPos, _dt);
	collisionCheck(_ents.movingSelectedDudesPos, _ents.staticDudesPos, _dt);
	collisionCheck(_ents.movingSelectedDudesPos, _ents.staticSelectedDudesPos, _dt);
	//movingDudesPos
	collisionCheck(_ents.movingDudesPos, _ents.movingDudesPos, _dt);
	collisionCheck(_ents.movingDudesPos, _ents.staticDudesPos, _dt);
	collisionCheck(_ents.movingDudesPos, _ents.staticSelectedDudesPos, _dt);
	//staticDudesPos
	collisionCheck(_ents.staticDudesPos, _ents.staticDudesPos, _dt);
	collisionCheck(_ents.staticDudesPos, _ents.staticSelectedDudesPos, _dt);
	//staticSelectedDudesPos
	collisionCheck(_ents.staticSelectedDudesPos, _ents.staticSelectedDudesPos, _dt);
}

void EntityManagmentSystems::deselectEntities(EntStruct& _ents)
{
	for (auto dude : _ents.movingSelectedDudesPos)
	{
		_ents.movingDudesPos.emplace_back(std::move(dude));
	}
	for (auto dude : _ents.staticSelectedDudesPos)
	{
		_ents.staticDudesPos.emplace_back(std::move(dude));
	}
	for (auto hive : _ents.selectedDudeHivesPos)
	{
		_ents.dudeHivesPos.emplace_back(std::move(hive));
	}
	_ents.movingSelectedDudesPos.clear();
	_ents.staticSelectedDudesPos.clear();
	_ents.selectedDudeHivesPos.clear();
}

void EntityManagmentSystems::applySpeedLimit(Vector6& _ent, const float limit)
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

void EntityManagmentSystems::applyFriction(Vector6& _ent, const float friction)
{
	_ent.vX += (_ent.vX * friction) * -1.0f;
	_ent.vY += (_ent.vY * friction) * -1.0f;
}

void EntityManagmentSystems::render(Graphics& _gfx, EntStruct& _ents)
{
	for (auto dude : _ents.staticDudesPos)
	{
		renderDude(_gfx, (int)dude.x, (int)dude.y, 1);
	}
	for (auto dude : _ents.movingDudesPos)
	{
		renderDude(_gfx, (int)dude.x, (int)dude.y, 1);
	}
	for (auto dude : _ents.staticSelectedDudesPos)
	{
		renderSelectedDude(_gfx, (int)dude.x, (int)dude.y, 1);
	}
	for (auto dude : _ents.movingSelectedDudesPos)
	{
		renderSelectedDude(_gfx, (int)dude.x, (int)dude.y, 1);
	}
	for (auto hive : _ents.dudeHivesPos)
	{
		renderDude(_gfx, (int)hive.x, (int)hive.y, 3);
	}
	for (auto hive : _ents.selectedDudeHivesPos)
	{
		renderSelectedDude(_gfx, (int)hive.x, (int)hive.y, 3);
	}
	for (auto poo : _ents.poosPos)
	{
		renderPoo(_gfx, (int)poo.x, (int)poo.y, 1);
	}
	for (auto hive : _ents.pooHivesPos)
	{
		renderPoo(_gfx, (int)hive.x, (int)hive.y, 3);
	}

	renderResources(_gfx);
}

void EntityManagmentSystems::renderResources(Graphics& _gfx)
{
	for (int _y = 15; _y <= 25; _y++)
	{
		for (int _x = 15; _x <= resources; _x++)
		{
			_gfx.PutPixel(_x, _y, { 255,255,255 });
		}
	}
}

void EntityManagmentSystems::renderSelectedDude(Graphics& _gfx, int _x, int _y, int _scale)
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

void EntityManagmentSystems::renderPoo(Graphics& _gfx, int _x, int _y, int _scale)
{	
	_gfx.PutPixel((14 * _scale) + _x, (0 * _scale) + _y, 138, 77, 0);
	_gfx.PutPixel((7 * _scale) + _x, (1 * _scale) + _y, 138, 77, 0);
	_gfx.PutPixel((13 * _scale) + _x, (1 * _scale) + _y, 138, 77, 0);
	_gfx.PutPixel((20 * _scale) + _x, (1 * _scale) + _y, 138, 77, 0);
	_gfx.PutPixel((6 * _scale) + _x, (2 * _scale) + _y, 138, 77, 0);
	_gfx.PutPixel((13 * _scale) + _x, (2 * _scale) + _y, 138, 77, 0);
	_gfx.PutPixel((20 * _scale) + _x, (2 * _scale) + _y, 138, 77, 0);
	_gfx.PutPixel((6 * _scale) + _x, (3 * _scale) + _y, 138, 77, 0);
	_gfx.PutPixel((6 * _scale) + _x, (4 * _scale) + _y, 138, 77, 0);
	_gfx.PutPixel((14 * _scale) + _x, (4 * _scale) + _y, 138, 77, 0);
	_gfx.PutPixel((21 * _scale) + _x, (4 * _scale) + _y, 138, 77, 0);
	_gfx.PutPixel((7 * _scale) + _x, (5 * _scale) + _y, 138, 77, 0);
	_gfx.PutPixel((13 * _scale) + _x, (5 * _scale) + _y, 138, 77, 0);
	_gfx.PutPixel((21 * _scale) + _x, (5 * _scale) + _y, 138, 77, 0);
	_gfx.PutPixel((7 * _scale) + _x, (6 * _scale) + _y, 138, 77, 0);
	_gfx.PutPixel((20 * _scale) + _x, (6 * _scale) + _y, 138, 77, 0);
	_gfx.PutPixel((6 * _scale) + _x, (7 * _scale) + _y, 138, 77, 0);
	_gfx.PutPixel((14 * _scale) + _x, (7 * _scale) + _y, 51, 28, 0);
	_gfx.PutPixel((15 * _scale) + _x, (7 * _scale) + _y, 51, 28, 0);
	_gfx.PutPixel((20 * _scale) + _x, (7 * _scale) + _y, 138, 77, 0);
	_gfx.PutPixel((12 * _scale) + _x, (8 * _scale) + _y, 51, 28, 0);
	_gfx.PutPixel((13 * _scale) + _x, (8 * _scale) + _y, 51, 28, 0);
	_gfx.PutPixel((14 * _scale) + _x, (8 * _scale) + _y, 51, 28, 0);
	_gfx.PutPixel((7 * _scale) + _x, (9 * _scale) + _y, 138, 77, 0);
	_gfx.PutPixel((11 * _scale) + _x, (9 * _scale) + _y, 51, 28, 0);
	_gfx.PutPixel((12 * _scale) + _x, (9 * _scale) + _y, 102, 57, 0);
	_gfx.PutPixel((13 * _scale) + _x, (9 * _scale) + _y, 138, 77, 0);
	_gfx.PutPixel((14 * _scale) + _x, (9 * _scale) + _y, 138, 77, 0);
	_gfx.PutPixel((15 * _scale) + _x, (9 * _scale) + _y, 51, 28, 0);
	_gfx.PutPixel((21 * _scale) + _x, (9 * _scale) + _y, 138, 77, 0);
	_gfx.PutPixel((10 * _scale) + _x, (10 * _scale) + _y, 51, 28, 0);
	_gfx.PutPixel((11 * _scale) + _x, (10 * _scale) + _y, 51, 28, 0);
	_gfx.PutPixel((12 * _scale) + _x, (10 * _scale) + _y, 102, 57, 0);
	_gfx.PutPixel((13 * _scale) + _x, (10 * _scale) + _y, 138, 77, 0);
	_gfx.PutPixel((14 * _scale) + _x, (10 * _scale) + _y, 138, 77, 0);
	_gfx.PutPixel((15 * _scale) + _x, (10 * _scale) + _y, 51, 28, 0);
	_gfx.PutPixel((20 * _scale) + _x, (10 * _scale) + _y, 138, 77, 0);
	_gfx.PutPixel((9 * _scale) + _x, (11 * _scale) + _y, 51, 28, 0);
	_gfx.PutPixel((10 * _scale) + _x, (11 * _scale) + _y, 138, 77, 0);
	_gfx.PutPixel((11 * _scale) + _x, (11 * _scale) + _y, 138, 77, 0);
	_gfx.PutPixel((12 * _scale) + _x, (11 * _scale) + _y, 51, 28, 0);
	_gfx.PutPixel((13 * _scale) + _x, (11 * _scale) + _y, 51, 28, 0);
	_gfx.PutPixel((14 * _scale) + _x, (11 * _scale) + _y, 51, 28, 0);
	_gfx.PutPixel((15 * _scale) + _x, (11 * _scale) + _y, 51, 28, 0);
	_gfx.PutPixel((16 * _scale) + _x, (11 * _scale) + _y, 51, 28, 0);
	_gfx.PutPixel((9 * _scale) + _x, (12 * _scale) + _y, 51, 28, 0);
	_gfx.PutPixel((10 * _scale) + _x, (12 * _scale) + _y, 138, 77, 0);
	_gfx.PutPixel((11 * _scale) + _x, (12 * _scale) + _y, 138, 77, 0);
	_gfx.PutPixel((12 * _scale) + _x, (12 * _scale) + _y, 111, 62, 0);
	_gfx.PutPixel((13 * _scale) + _x, (12 * _scale) + _y, 102, 57, 0);
	_gfx.PutPixel((14 * _scale) + _x, (12 * _scale) + _y, 102, 57, 0);
	_gfx.PutPixel((15 * _scale) + _x, (12 * _scale) + _y, 102, 57, 0);
	_gfx.PutPixel((16 * _scale) + _x, (12 * _scale) + _y, 51, 28, 0);
	_gfx.PutPixel((9 * _scale) + _x, (13 * _scale) + _y, 51, 28, 0);
	_gfx.PutPixel((10 * _scale) + _x, (13 * _scale) + _y, 109, 61, 0);
	_gfx.PutPixel((11 * _scale) + _x, (13 * _scale) + _y, 138, 77, 0);
	_gfx.PutPixel((12 * _scale) + _x, (13 * _scale) + _y, 138, 77, 0);
	_gfx.PutPixel((13 * _scale) + _x, (13 * _scale) + _y, 138, 77, 0);
	_gfx.PutPixel((14 * _scale) + _x, (13 * _scale) + _y, 138, 77, 0);
	_gfx.PutPixel((15 * _scale) + _x, (13 * _scale) + _y, 138, 77, 0);
	_gfx.PutPixel((16 * _scale) + _x, (13 * _scale) + _y, 51, 28, 0);
	_gfx.PutPixel((5 * _scale) + _x, (14 * _scale) + _y, 51, 28, 0);
	_gfx.PutPixel((7 * _scale) + _x, (14 * _scale) + _y, 51, 28, 0);
	_gfx.PutPixel((8 * _scale) + _x, (14 * _scale) + _y, 51, 28, 0);
	_gfx.PutPixel((9 * _scale) + _x, (14 * _scale) + _y, 51, 28, 0);
	_gfx.PutPixel((10 * _scale) + _x, (14 * _scale) + _y, 51, 28, 0);
	_gfx.PutPixel((11 * _scale) + _x, (14 * _scale) + _y, 138, 77, 0);
	_gfx.PutPixel((12 * _scale) + _x, (14 * _scale) + _y, 138, 77, 0);
	_gfx.PutPixel((13 * _scale) + _x, (14 * _scale) + _y, 138, 77, 0);
	_gfx.PutPixel((14 * _scale) + _x, (14 * _scale) + _y, 138, 77, 0);
	_gfx.PutPixel((15 * _scale) + _x, (14 * _scale) + _y, 138, 77, 0);
	_gfx.PutPixel((16 * _scale) + _x, (14 * _scale) + _y, 51, 28, 0);
	_gfx.PutPixel((4 * _scale) + _x, (15 * _scale) + _y, 51, 28, 0);
	_gfx.PutPixel((5 * _scale) + _x, (15 * _scale) + _y, 138, 77, 0);
	_gfx.PutPixel((6 * _scale) + _x, (15 * _scale) + _y, 51, 28, 0);
	_gfx.PutPixel((7 * _scale) + _x, (15 * _scale) + _y, 116, 65, 0);
	_gfx.PutPixel((8 * _scale) + _x, (15 * _scale) + _y, 138, 77, 0);
	_gfx.PutPixel((9 * _scale) + _x, (15 * _scale) + _y, 138, 77, 0);
	_gfx.PutPixel((10 * _scale) + _x, (15 * _scale) + _y, 138, 77, 0);
	_gfx.PutPixel((11 * _scale) + _x, (15 * _scale) + _y, 51, 28, 0);
	_gfx.PutPixel((12 * _scale) + _x, (15 * _scale) + _y, 51, 28, 0);
	_gfx.PutPixel((13 * _scale) + _x, (15 * _scale) + _y, 51, 28, 0);
	_gfx.PutPixel((14 * _scale) + _x, (15 * _scale) + _y, 51, 28, 0);
	_gfx.PutPixel((15 * _scale) + _x, (15 * _scale) + _y, 51, 28, 0);
	_gfx.PutPixel((16 * _scale) + _x, (15 * _scale) + _y, 51, 28, 0);
	_gfx.PutPixel((17 * _scale) + _x, (15 * _scale) + _y, 51, 28, 0);
	_gfx.PutPixel((18 * _scale) + _x, (15 * _scale) + _y, 51, 28, 0);
	_gfx.PutPixel((1 * _scale) + _x, (16 * _scale) + _y, 51, 28, 0);
	_gfx.PutPixel((2 * _scale) + _x, (16 * _scale) + _y, 51, 28, 0);
	_gfx.PutPixel((3 * _scale) + _x, (16 * _scale) + _y, 51, 28, 0);
	_gfx.PutPixel((4 * _scale) + _x, (16 * _scale) + _y, 51, 28, 0);
	_gfx.PutPixel((5 * _scale) + _x, (16 * _scale) + _y, 138, 77, 0);
	_gfx.PutPixel((6 * _scale) + _x, (16 * _scale) + _y, 51, 28, 0);
	_gfx.PutPixel((7 * _scale) + _x, (16 * _scale) + _y, 116, 65, 0);
	_gfx.PutPixel((8 * _scale) + _x, (16 * _scale) + _y, 138, 77, 0);
	_gfx.PutPixel((9 * _scale) + _x, (16 * _scale) + _y, 138, 77, 0);
	_gfx.PutPixel((10 * _scale) + _x, (16 * _scale) + _y, 138, 77, 0);
	_gfx.PutPixel((11 * _scale) + _x, (16 * _scale) + _y, 138, 77, 0);
	_gfx.PutPixel((12 * _scale) + _x, (16 * _scale) + _y, 138, 77, 0);
	_gfx.PutPixel((13 * _scale) + _x, (16 * _scale) + _y, 109, 61, 0);
	_gfx.PutPixel((14 * _scale) + _x, (16 * _scale) + _y, 51, 28, 0);
	_gfx.PutPixel((15 * _scale) + _x, (16 * _scale) + _y, 138, 77, 0);
	_gfx.PutPixel((16 * _scale) + _x, (16 * _scale) + _y, 138, 77, 0);
	_gfx.PutPixel((17 * _scale) + _x, (16 * _scale) + _y, 138, 77, 0);
	_gfx.PutPixel((18 * _scale) + _x, (16 * _scale) + _y, 123, 69, 0);
	_gfx.PutPixel((19 * _scale) + _x, (16 * _scale) + _y, 51, 28, 0);
	_gfx.PutPixel((0 * _scale) + _x, (17 * _scale) + _y, 51, 28, 0);
	_gfx.PutPixel((1 * _scale) + _x, (17 * _scale) + _y, 87, 49, 0);
	_gfx.PutPixel((2 * _scale) + _x, (17 * _scale) + _y, 87, 49, 0);
	_gfx.PutPixel((3 * _scale) + _x, (17 * _scale) + _y, 87, 49, 0);
	_gfx.PutPixel((4 * _scale) + _x, (17 * _scale) + _y, 87, 49, 0);
	_gfx.PutPixel((5 * _scale) + _x, (17 * _scale) + _y, 51, 28, 0);
	_gfx.PutPixel((6 * _scale) + _x, (17 * _scale) + _y, 51, 28, 0);
	_gfx.PutPixel((7 * _scale) + _x, (17 * _scale) + _y, 43, 24, 0);
	_gfx.PutPixel((8 * _scale) + _x, (17 * _scale) + _y, 51, 28, 0);
	_gfx.PutPixel((9 * _scale) + _x, (17 * _scale) + _y, 51, 28, 0);
	_gfx.PutPixel((10 * _scale) + _x, (17 * _scale) + _y, 51, 28, 0);
	_gfx.PutPixel((11 * _scale) + _x, (17 * _scale) + _y, 51, 28, 0);
	_gfx.PutPixel((12 * _scale) + _x, (17 * _scale) + _y, 51, 28, 0);
	_gfx.PutPixel((13 * _scale) + _x, (17 * _scale) + _y, 40, 22, 0);
	_gfx.PutPixel((14 * _scale) + _x, (17 * _scale) + _y, 51, 28, 0);
	_gfx.PutPixel((15 * _scale) + _x, (17 * _scale) + _y, 138, 77, 0);
	_gfx.PutPixel((16 * _scale) + _x, (17 * _scale) + _y, 138, 77, 0);
	_gfx.PutPixel((17 * _scale) + _x, (17 * _scale) + _y, 138, 77, 0);
	_gfx.PutPixel((18 * _scale) + _x, (17 * _scale) + _y, 123, 69, 0);
	_gfx.PutPixel((19 * _scale) + _x, (17 * _scale) + _y, 51, 28, 0);
	_gfx.PutPixel((0 * _scale) + _x, (18 * _scale) + _y, 51, 28, 0);
	_gfx.PutPixel((1 * _scale) + _x, (18 * _scale) + _y, 138, 77, 0);
	_gfx.PutPixel((2 * _scale) + _x, (18 * _scale) + _y, 138, 77, 0);
	_gfx.PutPixel((3 * _scale) + _x, (18 * _scale) + _y, 138, 77, 0);
	_gfx.PutPixel((4 * _scale) + _x, (18 * _scale) + _y, 138, 77, 0);
	_gfx.PutPixel((5 * _scale) + _x, (18 * _scale) + _y, 51, 28, 0);
	_gfx.PutPixel((6 * _scale) + _x, (18 * _scale) + _y, 51, 28, 0);
	_gfx.PutPixel((7 * _scale) + _x, (18 * _scale) + _y, 51, 28, 0);
	_gfx.PutPixel((8 * _scale) + _x, (18 * _scale) + _y, 51, 28, 0);
	_gfx.PutPixel((9 * _scale) + _x, (18 * _scale) + _y, 51, 28, 0);
	_gfx.PutPixel((10 * _scale) + _x, (18 * _scale) + _y, 51, 28, 0);
	_gfx.PutPixel((11 * _scale) + _x, (18 * _scale) + _y, 51, 28, 0);
	_gfx.PutPixel((12 * _scale) + _x, (18 * _scale) + _y, 51, 28, 0);
	_gfx.PutPixel((13 * _scale) + _x, (18 * _scale) + _y, 51, 28, 0);
	_gfx.PutPixel((14 * _scale) + _x, (18 * _scale) + _y, 51, 28, 0);
	_gfx.PutPixel((15 * _scale) + _x, (18 * _scale) + _y, 138, 77, 0);
	_gfx.PutPixel((16 * _scale) + _x, (18 * _scale) + _y, 138, 77, 0);
	_gfx.PutPixel((17 * _scale) + _x, (18 * _scale) + _y, 138, 77, 0);
	_gfx.PutPixel((18 * _scale) + _x, (18 * _scale) + _y, 123, 69, 0);
	_gfx.PutPixel((19 * _scale) + _x, (18 * _scale) + _y, 51, 28, 0);
	_gfx.PutPixel((20 * _scale) + _x, (18 * _scale) + _y, 51, 28, 0);
	_gfx.PutPixel((21 * _scale) + _x, (18 * _scale) + _y, 51, 28, 0);
	_gfx.PutPixel((22 * _scale) + _x, (18 * _scale) + _y, 51, 28, 0);
	_gfx.PutPixel((0 * _scale) + _x, (19 * _scale) + _y, 51, 28, 0);
	_gfx.PutPixel((1 * _scale) + _x, (19 * _scale) + _y, 138, 77, 0);
	_gfx.PutPixel((2 * _scale) + _x, (19 * _scale) + _y, 138, 77, 0);
	_gfx.PutPixel((3 * _scale) + _x, (19 * _scale) + _y, 138, 77, 0);
	_gfx.PutPixel((4 * _scale) + _x, (19 * _scale) + _y, 138, 77, 0);
	_gfx.PutPixel((5 * _scale) + _x, (19 * _scale) + _y, 51, 28, 0);
	_gfx.PutPixel((6 * _scale) + _x, (19 * _scale) + _y, 138, 77, 0);
	_gfx.PutPixel((7 * _scale) + _x, (19 * _scale) + _y, 138, 77, 0);
	_gfx.PutPixel((8 * _scale) + _x, (19 * _scale) + _y, 138, 77, 0);
	_gfx.PutPixel((9 * _scale) + _x, (19 * _scale) + _y, 138, 77, 0);
	_gfx.PutPixel((10 * _scale) + _x, (19 * _scale) + _y, 138, 77, 0);
	_gfx.PutPixel((11 * _scale) + _x, (19 * _scale) + _y, 138, 77, 0);
	_gfx.PutPixel((12 * _scale) + _x, (19 * _scale) + _y, 138, 77, 0);
	_gfx.PutPixel((13 * _scale) + _x, (19 * _scale) + _y, 138, 77, 0);
	_gfx.PutPixel((14 * _scale) + _x, (19 * _scale) + _y, 138, 77, 0);
	_gfx.PutPixel((15 * _scale) + _x, (19 * _scale) + _y, 138, 77, 0);
	_gfx.PutPixel((16 * _scale) + _x, (19 * _scale) + _y, 138, 77, 0);
	_gfx.PutPixel((17 * _scale) + _x, (19 * _scale) + _y, 138, 77, 0);
	_gfx.PutPixel((18 * _scale) + _x, (19 * _scale) + _y, 123, 69, 0);
	_gfx.PutPixel((19 * _scale) + _x, (19 * _scale) + _y, 51, 28, 0);
	_gfx.PutPixel((20 * _scale) + _x, (19 * _scale) + _y, 138, 77, 0);
	_gfx.PutPixel((21 * _scale) + _x, (19 * _scale) + _y, 138, 77, 0);
	_gfx.PutPixel((22 * _scale) + _x, (19 * _scale) + _y, 65, 36, 0);
	_gfx.PutPixel((23 * _scale) + _x, (19 * _scale) + _y, 51, 28, 0);
	_gfx.PutPixel((1 * _scale) + _x, (20 * _scale) + _y, 51, 28, 0);
	_gfx.PutPixel((2 * _scale) + _x, (20 * _scale) + _y, 51, 28, 0);
	_gfx.PutPixel((3 * _scale) + _x, (20 * _scale) + _y, 51, 28, 0);
	_gfx.PutPixel((4 * _scale) + _x, (20 * _scale) + _y, 51, 28, 0);
	_gfx.PutPixel((5 * _scale) + _x, (20 * _scale) + _y, 51, 28, 0);
	_gfx.PutPixel((6 * _scale) + _x, (20 * _scale) + _y, 138, 77, 0);
	_gfx.PutPixel((7 * _scale) + _x, (20 * _scale) + _y, 138, 77, 0);
	_gfx.PutPixel((8 * _scale) + _x, (20 * _scale) + _y, 138, 77, 0);
	_gfx.PutPixel((9 * _scale) + _x, (20 * _scale) + _y, 138, 77, 0);
	_gfx.PutPixel((10 * _scale) + _x, (20 * _scale) + _y, 138, 77, 0);
	_gfx.PutPixel((11 * _scale) + _x, (20 * _scale) + _y, 138, 77, 0);
	_gfx.PutPixel((12 * _scale) + _x, (20 * _scale) + _y, 138, 77, 0);
	_gfx.PutPixel((13 * _scale) + _x, (20 * _scale) + _y, 138, 77, 0);
	_gfx.PutPixel((14 * _scale) + _x, (20 * _scale) + _y, 138, 77, 0);
	_gfx.PutPixel((15 * _scale) + _x, (20 * _scale) + _y, 138, 77, 0);
	_gfx.PutPixel((16 * _scale) + _x, (20 * _scale) + _y, 138, 77, 0);
	_gfx.PutPixel((17 * _scale) + _x, (20 * _scale) + _y, 138, 77, 0);
	_gfx.PutPixel((18 * _scale) + _x, (20 * _scale) + _y, 123, 69, 0);
	_gfx.PutPixel((19 * _scale) + _x, (20 * _scale) + _y, 51, 28, 0);
	_gfx.PutPixel((20 * _scale) + _x, (20 * _scale) + _y, 138, 77, 0);
	_gfx.PutPixel((21 * _scale) + _x, (20 * _scale) + _y, 138, 77, 0);
	_gfx.PutPixel((22 * _scale) + _x, (20 * _scale) + _y, 65, 36, 0);
	_gfx.PutPixel((23 * _scale) + _x, (20 * _scale) + _y, 51, 28, 0);
	_gfx.PutPixel((0 * _scale) + _x, (21 * _scale) + _y, 51, 28, 0);
	_gfx.PutPixel((1 * _scale) + _x, (21 * _scale) + _y, 138, 77, 0);
	_gfx.PutPixel((2 * _scale) + _x, (21 * _scale) + _y, 138, 77, 0);
	_gfx.PutPixel((3 * _scale) + _x, (21 * _scale) + _y, 138, 77, 0);
	_gfx.PutPixel((4 * _scale) + _x, (21 * _scale) + _y, 138, 77, 0);
	_gfx.PutPixel((5 * _scale) + _x, (21 * _scale) + _y, 138, 77, 0);
	_gfx.PutPixel((6 * _scale) + _x, (21 * _scale) + _y, 51, 28, 0);
	_gfx.PutPixel((7 * _scale) + _x, (21 * _scale) + _y, 51, 28, 0);
	_gfx.PutPixel((8 * _scale) + _x, (21 * _scale) + _y, 51, 28, 0);
	_gfx.PutPixel((9 * _scale) + _x, (21 * _scale) + _y, 51, 28, 0);
	_gfx.PutPixel((10 * _scale) + _x, (21 * _scale) + _y, 51, 28, 0);
	_gfx.PutPixel((11 * _scale) + _x, (21 * _scale) + _y, 51, 28, 0);
	_gfx.PutPixel((12 * _scale) + _x, (21 * _scale) + _y, 51, 28, 0);
	_gfx.PutPixel((13 * _scale) + _x, (21 * _scale) + _y, 51, 28, 0);
	_gfx.PutPixel((14 * _scale) + _x, (21 * _scale) + _y, 51, 28, 0);
	_gfx.PutPixel((15 * _scale) + _x, (21 * _scale) + _y, 51, 28, 0);
	_gfx.PutPixel((16 * _scale) + _x, (21 * _scale) + _y, 51, 28, 0);
	_gfx.PutPixel((17 * _scale) + _x, (21 * _scale) + _y, 51, 28, 0);
	_gfx.PutPixel((18 * _scale) + _x, (21 * _scale) + _y, 51, 28, 0);
	_gfx.PutPixel((20 * _scale) + _x, (21 * _scale) + _y, 51, 28, 0);
	_gfx.PutPixel((21 * _scale) + _x, (21 * _scale) + _y, 51, 28, 0);
	_gfx.PutPixel((22 * _scale) + _x, (21 * _scale) + _y, 51, 28, 0);
	_gfx.PutPixel((0 * _scale) + _x, (22 * _scale) + _y, 51, 28, 0);
	_gfx.PutPixel((1 * _scale) + _x, (22 * _scale) + _y, 65, 36, 0);
	_gfx.PutPixel((2 * _scale) + _x, (22 * _scale) + _y, 65, 36, 0);
	_gfx.PutPixel((3 * _scale) + _x, (22 * _scale) + _y, 65, 36, 0);
	_gfx.PutPixel((4 * _scale) + _x, (22 * _scale) + _y, 65, 36, 0);
	_gfx.PutPixel((5 * _scale) + _x, (22 * _scale) + _y, 65, 36, 0);
	_gfx.PutPixel((6 * _scale) + _x, (22 * _scale) + _y, 51, 28, 0);
	_gfx.PutPixel((1 * _scale) + _x, (23 * _scale) + _y, 51, 28, 0);
	_gfx.PutPixel((2 * _scale) + _x, (23 * _scale) + _y, 51, 28, 0);
	_gfx.PutPixel((3 * _scale) + _x, (23 * _scale) + _y, 51, 28, 0);
	_gfx.PutPixel((4 * _scale) + _x, (23 * _scale) + _y, 51, 28, 0);
	_gfx.PutPixel((5 * _scale) + _x, (23 * _scale) + _y, 51, 28, 0);
	_gfx.PutPixel((6 * _scale) + _x, (23 * _scale) + _y, 51, 28, 0);
}

void EntityManagmentSystems::renderDude(Graphics& _gfx, int _x, int _y, int _scale)
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