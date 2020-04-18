#pragma once


struct Vector6
{
	Vector6(float, float, int);
	Vector6(float, float, float, float, int);
	Vector6(float, float, float, float, float, float, int);
	float x = 100.0f;
	float y = 100.0f;
	float dx = 100.0f;
	float dy = 100.0f;
	float vX = 0.0f;
	float vY = 0.0f;
	int id = 0;
};