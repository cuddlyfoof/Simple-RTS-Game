#pragma once

struct Hive
{
	Hive(int);
	const int posID = 0;
	static constexpr float diameter = 20.0f;
	static constexpr float radius = (diameter / 2);
	bool inBuildQueue = true;
};