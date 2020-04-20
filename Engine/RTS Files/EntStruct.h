#pragma once

#include<vector>
#include"Vector6.h"
#include"Vector2.h"
#include"Dude.h"
#include"Hive.h"
#include"Poo.h"
#include"HealthEntity.h"
#include"EntityInQueue.h"

struct EntStruct
{
	EntStruct();
	//Vector6 Struct arrays****
	//Units *******************
	std::vector<Vector6> staticDudesPos;
	std::vector<Vector6> movingDudesPos;
	std::vector<Vector6> staticSelectedDudesPos;
	std::vector<Vector6> movingSelectedDudesPos;
	std::vector<Vector6> poosPos;
	//Vector2 Buildings *******
	std::vector<Vector2> dudeHivesPos;
	std::vector<Vector2> selectedDudeHivesPos;
	std::vector<Vector2> pooHivesPos;

	//Metric Vectors
	std::vector<HealthEntity> healthTracker;
	std::vector<EntityInQueue> queuedEntities;

	//Units Values
	std::vector<Dude> dudes;
	std::vector<Poo> poos;
	//Buildings Values
	std::vector<Hive> dudeHives;
	std::vector<Hive> pooHives;
};