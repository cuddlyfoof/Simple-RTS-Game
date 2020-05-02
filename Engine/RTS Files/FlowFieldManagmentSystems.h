#pragma once
#include <cstdint>
#include "../Graphics.h"
#include "Dude.h"
#include <array>
#include <vector>




class FlowFieldManagmentSystems
{
public:

	static constexpr int kFieldWidth = 10;
	static constexpr int kCostMapHeight = (int)(Graphics::ScreenHeight / Dude::diameter);
	static constexpr int kCostMapWidth = (int)(Graphics::ScreenWidth / Dude::diameter);

	static constexpr int kFieldSize = kFieldWidth * kFieldWidth;
	static constexpr int kFieldsHeight = kCostMapHeight / kFieldWidth;
	static constexpr int kFieldsWidth = kCostMapWidth / kFieldWidth;

	struct CostField {
		std::array<std::uint8_t, (kFieldSize)> nodes;
		//CostField() { nodes.fill(1); };
	};
	struct CostFields {
		std::array<CostField, (kFieldsHeight* kFieldsWidth)> fields;
	};

	struct Field {		
		std::array<unsigned short, (kFieldSize)> nodes;
		Field() { nodes.fill(65535); };
	};
	struct Fields {
		std::array<Field, (kFieldsHeight * kFieldsWidth)> fields;
	};

private:

	std::vector<std::tuple<unsigned short, unsigned short, unsigned short>> getNeighbors(unsigned int, unsigned int, unsigned int, unsigned int);
	unsigned int get2DID(unsigned int, unsigned int, unsigned int);
	unsigned int getFieldID(unsigned int, unsigned int);
	unsigned int getNodeID(unsigned int, unsigned int);

	//unsigned int getValueByIndex();
	//Node Arrays
	//std::array<std::array<std::uint8_t, kCostMapWidth>, kCostMapHeight> costMap;
	//Fields costMap;
	// 4D arrays be wack
	CostFields costFields;
	Fields integrationFields;

public:

	FlowFieldManagmentSystems();
	void render(Graphics&);
	void resetIntegrationField();
	void adjustIntegraionFields(int, int, unsigned int);
	void adjustCostMap(int, int, std::uint8_t);
	void calculateIntegrationField(unsigned int, unsigned int);
	void calculateVectorField(std::uint8_t[kFieldWidth][kFieldWidth]);


};