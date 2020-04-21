#pragma once

struct HealthEntity
{
	HealthEntity(int, int, float, float);
	int uuid = 0;
	int entNum = 0;
	float health = 0.0f;
	float damageTaking = 0.0f;
};