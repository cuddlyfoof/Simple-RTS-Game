#pragma once

struct EntityInQueue
{
	EntityInQueue(int, int, float, float);
	int uuid = 0;
	int builderUuid = 0;
	float x = 100.0f;
	float y = 100.0f;
};