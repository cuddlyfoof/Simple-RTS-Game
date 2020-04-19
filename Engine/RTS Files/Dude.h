#pragma once

struct Dude
{
	Dude(int);
	const int posID = 0;
	static constexpr float speed = 5.0f;
	static constexpr float acceleration = 4.2f;
	static constexpr float diameter = 20.0f;
	static constexpr float radius = (diameter / 2);
	static constexpr float attackRadius = 40.0f;
	static constexpr float entNum = 0;
};