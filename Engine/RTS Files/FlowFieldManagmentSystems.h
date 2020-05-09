#pragma once
#include <cstdint>
#include "../Graphics.h"
#include "Dude.h"
#include <array>
#include <vector>
#include "EntStruct.h"




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

	struct Node
	{
		Node* parent;
		unsigned int x, y;
		unsigned int distanceTraveled;
		unsigned int distanceFromGoal;
	};

private:

	unsigned int get2DID(unsigned int, unsigned int, unsigned int);
	unsigned int getFieldID(unsigned int, unsigned int);
	unsigned int getNodeID(unsigned int, unsigned int);
	unsigned int getCostMapValueAtNode(std::array<unsigned int, 5>);

	std::vector<std::array<unsigned int, 5>> getNeighbors(std::array<unsigned int, 5>);
	std::vector<Node> getNeighbors(Node&);

	void calculateVectorField(std::uint8_t[kFieldWidth][kFieldWidth]);
	

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
	void resetIntegrationField(unsigned int);
	void resetIntegrationFields();
	void adjustIntegraionFields(int, int, unsigned int);
	void adjustCostMap(int, int, std::uint8_t);
	void aStarIntegrationFields( EntStruct&, unsigned int, unsigned int);
	void calculateIntegrationField(unsigned int, unsigned int);
};