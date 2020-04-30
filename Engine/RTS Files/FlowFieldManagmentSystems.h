#pragma once
#include <cstdint>
#include "../Graphics.h"
#include "Dude.h"
#include <array>
#include <vector>




class FlowFieldManagmentSystems
{
public:

	static constexpr int kIntFieldSize = 10;
	static constexpr int kCostMapWidth = (int)(Graphics::ScreenWidth / Dude::diameter);
	static constexpr int kCostMapHeight = (int)(Graphics::ScreenHeight / Dude::diameter);
	static constexpr int kIntFieldWidth = kCostMapWidth / kIntFieldSize;
	static constexpr int kIntFieldHeight = kCostMapHeight / kIntFieldSize;

	struct Field {		
		std::array<std::uint8_t, (kIntFieldSize * kIntFieldSize)> nodes;
		Field() { nodes.fill(1); };
	};
	struct Fields {
		std::array<Field, (kIntFieldHeight * kIntFieldWidth)> fields;
	};

private:

	//Node Arrays
	std::array<std::array<std::uint8_t, kCostMapWidth>, kCostMapHeight> costMap;
	// 4D arrays be wack
	Fields integrationFields;

public:

	FlowFieldManagmentSystems();
	void adjustCostMap(std::array<std::array<std::uint8_t, kCostMapWidth>, kCostMapHeight>, int, int, std::uint8_t);
	void calculateIntegrationField(std::uint8_t[kIntFieldSize][kIntFieldSize]);
	void calculateVectorField(std::uint8_t[kIntFieldSize][kIntFieldSize]);


};