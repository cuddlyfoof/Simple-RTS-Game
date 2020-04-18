#pragma once
#include "Vector4.h"


class Poo
{
public:
	Poo(Vector4*);
	static constexpr int speed = 3;

private:
	Vector4* posID;
};