#pragma once

struct Hive
{
	Hive(int);
	int posID = 0;
	static constexpr float diameter = 60.0f;
	static constexpr float radius = (diameter / 2);
	static constexpr float entNum = 1;
};