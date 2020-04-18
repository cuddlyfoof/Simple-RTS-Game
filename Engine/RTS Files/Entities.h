#pragma once

#include <vector>
#include "Vector6.h"
#include "Vector2.h"
#include "EntityInQueue.h"
#include "Dude.h"
#include "Hive.h"
#include "../Graphics.h"
#include "../MainWindow.h"
#include <numeric>

class Entities
{
public:
	Entities();
	~Entities();
	void moveSelectedDudes(int, int);
	void addEntityToQueue(int,int,int);	
	void update();
	void selectEntities(MainWindow&, int, int);
	void deselectEntities();
	//*************** Render stuffs
	void render(Graphics&);
	//*************** Depricated / not yet implemented
	//void stopDudes(std::vector<Vector4>&, std::vector<Vector4>&, float);
	//void updatePoosPosition();

private:
	//Functions************************************************************
	void checkEntityQueue();
	void addVector6Entity(std::vector<Vector6>&, int, int, int);
	void addVector2Entity(std::vector<Vector2>&, int, int, int);
	void selectVector6(MainWindow&, std::vector<Vector6>&, std::vector<Vector6>&, const int, const int);
	void selectVector2(MainWindow&, std::vector<Vector2>&, std::vector<Vector2>&, const int, const int);
	void collisionCheck(std::vector<Vector6>&, std::vector<Vector6>&);
	void updatePositions(std::vector<Vector6>&, std::vector<Vector6>&);
	//*************** Math Stuffs:	
	void applySpeedLimit(Vector6&, const float);
	void applyFriction(Vector6&, const float);
	//*************** Render stuffs:
	void renderSelectedDude(Graphics&, int, int, int);
	void renderPoo(Graphics&, int, int, int);
	void renderDude(Graphics&, int, int, int);
	//*************** Depricated / not yet implemented
	//bool boxCollisionCheck(const int, const int, const int, const int, const int, const int);

	//Variables************************************************************
	int uuid = 1;
	const float minSpeed = 1.2;
	int resources = 1000;
	//Vector6 Struct arrays****
	//Units *******************
	std::vector<Vector6> staticDudesPos;
	std::vector<Vector6> movingDudesPos;
	std::vector<Vector6> staticSelectedDudesPos;
	std::vector<Vector6> movingSelectedDudesPos;
	//Vector2 Buildings *******
	std::vector<Vector2> hivesPos;
	std::vector<Vector2> selectedHivesPos;

	//Unit and building Vectors
	std::vector<EntityInQueue> queuedEntities;
	std::vector<Dude> dudes;
	std::vector<Hive> hives;

	//****************** Not Used yet
	//std::vector<Vector6> poosPos;
};