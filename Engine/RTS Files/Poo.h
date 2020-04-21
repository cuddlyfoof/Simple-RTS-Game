#pragma once


struct Poo
{
	Poo(int);
	int posID;
	static constexpr float speed = 27.0f;
	static constexpr float acceleration = 4.2f;
	static constexpr float diameter = 20.0f;
	static constexpr float radius = (diameter / 2);
	static constexpr float baseDamage = 15.0f;
	static constexpr float attackSpeed = 0.2f;
	static constexpr float attackRadius = 40.0f;
	static constexpr float maxHealth = 50.0f;
	float health = maxHealth;
	static constexpr float entNum = 2;
};