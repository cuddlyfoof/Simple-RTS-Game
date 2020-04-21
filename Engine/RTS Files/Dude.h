#pragma once

struct Dude
{
	Dude(int);
	int posID = 0;
	static constexpr float speed = 300.0f;
	static constexpr float acceleration = 40.0f;
	static constexpr float diameter = 20.0f;
	static constexpr float radius = (diameter / 2.0f);
	static constexpr float baseDamage = 15.0f;
	static constexpr float attackSpeed = 0.2f;
	static constexpr float attackRadius = 40.0f;
	static constexpr float maxHealth = 100.0f;
	float health = maxHealth;
	static constexpr int entNum = 0;
};