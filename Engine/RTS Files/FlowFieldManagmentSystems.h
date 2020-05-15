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

	class Node {
	public:
		int idx;     // index in the flattened grid
		float cost;  // cost of traversing this pixel

		Node(int i, float c) : idx(i), cost(c) {}
	};

	friend bool operator<(const Node& n1, const Node& n2) {
		return n1.cost > n2.cost;
	}

	friend bool operator==(const Node& n1, const Node& n2) {
		return n1.idx == n2.idx;
	}

	/*struct Node
	{
		std::unique_ptr<Node> parent;
		unsigned int x, y;
		unsigned int distanceTraveled;
		unsigned int distanceFromGoal;
	};*/

private:

	unsigned int get2DID(unsigned int, unsigned int, unsigned int);
	unsigned int getFieldID(unsigned int, unsigned int);
	unsigned int getNodeID(unsigned int, unsigned int);
	unsigned int getCostMapValueAtNode(std::array<unsigned int, 5>);
	float linf_norm(int i0, int j0, int i1, int j1);
	float l1_norm(int i0, int j0, int i1, int j1);

	std::vector<std::array<unsigned int, 8>> getNeighbors(std::array<unsigned int, 8>, unsigned int , unsigned int , unsigned int , bool );
	//std::vector<Node> getNeighbors(Node&);
	bool astar(
		const std::array<std::uint8_t, kCostMapHeight* kCostMapWidth>& weights, const int unsigned h, const unsigned int w,
		const int start, const int goal, bool diag_ok,
		std::array<int, kCostMapWidth* kCostMapHeight>& paths);

	void calculateVectorField(std::uint8_t[kFieldWidth][kFieldWidth]);
	

	//unsigned int getValueByIndex();
	//Node Arrays
	//std::array<std::array<std::uint8_t, kCostMapWidth>, kCostMapHeight> costMap;
	//Fields costMap;
	// 4D arrays be wack
	std::array<std::uint8_t, kCostMapHeight* kCostMapWidth> kCostMap;
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
	void calculateIntegrationField(unsigned int);
};