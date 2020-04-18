#pragma once


struct Poo
{
	Poo(int);
	const int posID = 0;
	static constexpr float speed = 27.0f;
	static constexpr float acceleration = 4.2f;
	static constexpr float diameter = 20.0f;
	static constexpr float radius = (diameter / 2);
};