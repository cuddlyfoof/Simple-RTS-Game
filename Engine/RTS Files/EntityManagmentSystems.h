#pragma once

#include <vector>
#include <numeric>
#include "Vector6.h"
#include "Vector2.h"
#include "EntityInQueue.h"
#include "Dude.h"
#include "Poo.h"
#include "Hive.h"
#include "HealthEntity.h"
#include "../Graphics.h"
#include "../MainWindow.h"
#include "EntStruct.h"

class EntityManagmentSystems
{
public:
	//Main Systems
	EntityManagmentSystems();
	EntityManagmentSystems(EntStruct&);
	void moveSelectedDudes(std::vector<Vector6>&, std::vector<Vector6>&, int, int);
	void addEntityToQueue(EntStruct&, int,int,int);
	void update(EntStruct&, const float);
	void selectEntities(MainWindow&, EntStruct&, int, int);
	void deselectEntities(EntStruct&);
	//*************** Render stuffs
	void render(Graphics&, EntStruct&);
	//*************** Depricated / not yet implemented
	//void stopDudes(std::vector<Vector4>&, std::vector<Vector4>&, float);
	//void updatePoosPosition();

	//Assistive Systems
	//Functions************************************************************	
	void addVector6Entity(EntStruct& ,std::vector<Vector6>&, int, int, int);
	void addVector2Entity(EntStruct& ,std::vector<Vector2>&, int, int, int);
	void selectVector6(MainWindow&, std::vector<Vector6>&, std::vector<Vector6>&, const int, const int);
	void selectVector2(MainWindow&, std::vector<Vector2>&, std::vector<Vector2>&, const int, const int);
	void attackRangeCheck(std::vector<Vector6>&, std::vector<Vector6>&);
	//*************** Position Stuffs:	
	void runCollisions(EntStruct&, const float);
	void collisionCheck(std::vector<Vector6>&, std::vector<Vector6>&, const float);
	void updatePositions(std::vector<Vector6>&, std::vector<Vector6>&, const float);
	void applySpeedLimit(Vector6&, const float);
	void applyFriction(Vector6&, const float);
	
private:
	void checkEntityQueue(EntStruct&);
	//*************** Render stuffs:
	void renderResources(Graphics&);
	void renderSelectedDude(Graphics&, int, int, int);
	void renderPoo(Graphics&, int, int, int);
	void renderDude(Graphics&, int, int, int);
	//*************** Depricated / not yet implemented
	//bool boxCollisionCheck(const int, const int, const int, const int, const int, const int);

	//Variables************************************************************
	int uuid = 1;
	static constexpr float minSpeed = 1.2;
	int resources = 1000;
	

	//****************** Not Used yet
	//std::vector<Vector6> poosPos;
};