#include "Vector6.h"

Vector6::Vector6(float x, float y, int id) 
	:
	x(x),
	y(y),
	dx(x),
	dy(y),
	vX(0.0f),
	vY(0.0f),
	id(id)
{
}

Vector6::Vector6(float x, float y, float dx, float dy, int id)
	:
	x(x),
	y(y),
	dx(dx),
	dy(dy),
	vX(0.0f),
	vY(0.0f),
	id(id)
{
}

Vector6::Vector6(float x, float y, float dx, float dy, float vX, float vY, int id)
	:
	x(x),
	y(y),
	dx(dx),
	dy(dy),
	vX(vX),
	vY(vY),
	id(id)
{
}