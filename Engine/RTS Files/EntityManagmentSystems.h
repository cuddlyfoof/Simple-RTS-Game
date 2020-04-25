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
	//Main Update function *************
	void update(EntStruct&, const float);
	
	//*************** Main Render Function
	void render(Graphics&, EntStruct&);
	//*************** Depricated / not yet implemented
	//void stopDudes(std::vector<Vector4>&, std::vector<Vector4>&, float);
	//void updatePoosPosition();

	//Assistive Systems
	//Functions************************************************************	
	void moveSelectedDudes(std::vector<Vector6>&, std::vector<Vector6>&, int, int);
	void addEntityToQueue(EntStruct&, int, int, int);
	void selectEntities(MainWindow&, EntStruct&, int, int);
	void deselectEntities(EntStruct&);
	void addEntity(EntStruct& , int, int, int);
	void removeEntity(EntStruct&, const int, const int);
	void selectVector6(MainWindow&, std::vector<Vector6>&, std::vector<Vector6>&, const int, const int);
	void selectVector2(MainWindow&, std::vector<Vector2>&, std::vector<Vector2>&, const int, const int);
	//*************** Position Stuffs:	
	void runCollisions(EntStruct&, const float);
	void collisionCheck(std::vector<Vector6>&, std::vector<Vector6>&, const float);
	void updatePositions(std::vector<Vector6>&, std::vector<Vector6>&, const float);
	
private:	
	void trackHealth(EntStruct&, const float);
	void attackRangeCheck(std::vector<Vector6>&, std::vector<Vector6>&);
	void checkBuildingQueue(EntStruct&);

	//Position Stuffs
	void applySpeedLimit(Vector6&, const float);
	void applyFriction(Vector6&, const float);

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