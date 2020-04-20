#pragma once

struct Dude
{
	Dude(int);
	const int posID = 0;
	static constexpr float speed = 300.0f;
	static constexpr float acceleration = 40.0f;
	static constexpr float diameter = 20.0f;
	static constexpr float radius = (diameter / 2);
	static constexpr float attackRadius = 40.0f;
	static constexpr float entNum = 0;
};