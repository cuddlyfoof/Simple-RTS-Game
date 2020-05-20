#include "FlowFieldManagmentSystems.h"
#include "Dude.h"
#include <cmath>
#include <list>
#include <algorithm>
#include "Vector2.h"
#include <queue>
#include <limits>
//Get neighbor for Flow field part (neighbors are contained to a field)
//std::vector<std::array<unsigned int, 5>> FlowFieldManagmentSystems::getNeighbors(std::array<unsigned int, 8> nbrs, unsigned int nodeIndex, unsigned int w, unsigned int h, bool diag_ok)
//{
//
//	int row = nodeIndex / w;
//	int col = nodeIndex % w;
//	// check bounds and find up to eight neighbors: top to bottom, left to right
//	nbrs[0] = (diag_ok && row > 0 && col > 0) ? nodeIndex - w - 1 : -1;
//	nbrs[1] = (row > 0) ? nodeIndex - w : -1;
//	nbrs[2] = (diag_ok && row > 0 && col + 1 < w) ? nodeIndex - w + 1 : -1;
//	nbrs[3] = (col > 0) ? nodeIndex - 1 : -1;
//	nbrs[4] = (col + 1 < w) ? nodeIndex + 1 : -1;
//	nbrs[5] = (diag_ok && row + 1 < h && col > 0) ? nodeIndex + w - 1 : -1;
//	nbrs[6] = (row + 1 < h) ? nodeIndex + w : -1;
//	nbrs[7] = (diag_ok && row + 1 < h && col + 1 < w) ? nodeIndex + w + 1 : -1;
//
//
//	
//	//// Get west neightbor if it is within the field and is not a wall
//	//if (node[2] > 0 
//	//	&& costFields.fields[get2DID(node[0], node[1], kFieldsWidth)].nodes[get2DID(node[2] - 1, node[3], kFieldWidth)] != 255)
//	//{
//	//	neighbors.push_back({ node[0], node[1], node[2] - 1, node[3], integrationFields.fields[get2DID(node[0], node[1], kFieldsWidth)].nodes[get2DID(node[2] - 1, node[3], kFieldWidth)] });
//	//}
//	//// East
//	//if (node[2] < kFieldWidth - 1
//	//	&& costFields.fields[get2DID(node[0], node[1], kFieldsWidth)].nodes[get2DID(node[2] + 1, node[3], kFieldWidth)] != 255)
//	//{
//	//	neighbors.push_back({ node[0], node[1], node[2] + 1, node[3], integrationFields.fields[get2DID(node[0], node[1], kFieldsWidth)].nodes[get2DID(node[2] + 1, node[3], kFieldWidth)] });
//	//}
//	//// North
//	//if (node[3] > 0 
//	//	&& costFields.fields[get2DID(node[0], node[1], kFieldsWidth)].nodes[get2DID(node[2], node[3] - 1, kFieldWidth)] != 255)
//	//{
//	//	neighbors.push_back({ node[0], node[1], node[2], node[3] - 1, integrationFields.fields[get2DID(node[0], node[1], kFieldsWidth)].nodes[get2DID(node[2], node[3] - 1, kFieldWidth)] });
//	//}
//	//// South
//	//if (node[3] < kFieldWidth -1
//	//	&& costFields.fields[get2DID(node[0], node[1], kFieldsWidth)].nodes[get2DID(node[2], node[3] + 1, kFieldWidth)] != 255)
//	//{
//	//	neighbors.push_back({ node[0], node[1], node[2], node[3] + 1, integrationFields.fields[get2DID(node[0], node[1], kFieldsWidth)].nodes[get2DID(node[2], node[3] + 1, kFieldWidth)] });
//	//}
//
//	//return neighbors;
//}


////Get neigbor for A* part (neighbors are contained to the screen parameters)
//std::vector<FlowFieldManagmentSystems::Node> FlowFieldManagmentSystems::getNeighbors(Node& node)
//{
//	std::vector<FlowFieldManagmentSystems::Node> neighbors;
//
//	// Get west neightbor if it is within the field and is not a wall
//	if (node.x > 0
//		&& costFields.fields[get2DID(std::floor(node.x - 1) / 10, std::floor(node.y / 10), kFieldsWidth)].nodes[get2DID((node.x - 1) % 10, (node.y % 10), kFieldWidth)] != 255)
//	{
//		neighbors.push_back({ nullptr, (node.x - 1), node.y,
//			integrationFields.fields[get2DID(std::floor(node.x - 1) / 10, std::floor(node.y / 10), kFieldsWidth)].nodes[get2DID((node.x - 1) % 10, (node.y % 10), kFieldWidth)], node.distanceFromGoal });
//	}
//	// East
//	if (node.x < kCostMapWidth - 1
//		&& costFields.fields[get2DID(std::floor(node.x + 1) / 10, std::floor(node.y / 10), kFieldsWidth)].nodes[get2DID((node.x + 1) % 10, (node.y % 10), kFieldWidth)] != 255)
//	{
//		neighbors.push_back({ nullptr, (node.x + 1), node.y,
//			integrationFields.fields[get2DID(std::floor(node.x + 1) / 10, std::floor(node.y / 10), kFieldsWidth)].nodes[get2DID((node.x + 1) % 10, (node.y % 10), kFieldWidth)], node.distanceFromGoal });
//	}
//	// North
//	if (node.y > 0
//		&& costFields.fields[get2DID(std::floor(node.x / 10), std::floor(node.y - 1) / 10, kFieldsWidth)].nodes[get2DID((node.x % 10), (node.y - 1) % 10, kFieldWidth)] != 255)
//	{
//		neighbors.push_back({ nullptr, node.x, (node.y - 1),
//			integrationFields.fields[get2DID(std::floor(node.x / 10), std::floor(node.y - 1) / 10, kFieldsWidth)].nodes[get2DID((node.x % 10), (node.y - 1) % 10, kFieldWidth)], node.distanceFromGoal });
//	}
//	// South
//	if (node.y < kCostMapWidth - 1
//		&& costFields.fields[get2DID(std::floor(node.x / 10), std::floor(node.y + 1) / 10, kFieldsWidth)].nodes[get2DID((node.x % 10), (node.y + 1) % 10, kFieldWidth)] != 255)
//	{
//		neighbors.push_back({ nullptr, node.x, (node.y + 1),
//			integrationFields.fields[get2DID(std::floor(node.x / 10), std::floor(node.y + 1) / 10, kFieldsWidth)].nodes[get2DID((node.x % 10), (node.y + 1) % 10, kFieldWidth)], node.distanceFromGoal });
//	}
//	return neighbors;
//}

unsigned int FlowFieldManagmentSystems::get2DID(unsigned int tmp_x, unsigned int tmp_y, unsigned int tmp_w)
{
	return (tmp_y * tmp_w + tmp_x);
}

unsigned int FlowFieldManagmentSystems::getFieldID(unsigned int tmp_x, unsigned int tmp_y)
{
	return get2DID(std::floor(tmp_x / Dude::diameter / kFieldWidth), std::floor(tmp_y / Dude::diameter / kFieldWidth), kFieldsWidth);
}

unsigned int FlowFieldManagmentSystems::getNodeID(unsigned int tmp_x, unsigned int tmp_y)
{
	return get2DID(std::floor((tmp_x / (int)Dude::diameter) % kFieldWidth), std::floor((tmp_y / (int)Dude::diameter) % kFieldWidth), kFieldWidth);
}

unsigned int FlowFieldManagmentSystems::getCostMapValueAtNode(std::array<unsigned int, 5> nodeID)
{
	return costFields.fields[get2DID(nodeID[0], nodeID[1], kFieldsWidth)].nodes[get2DID(nodeID[2], nodeID[3], kFieldWidth)];
}

float FlowFieldManagmentSystems::linf_norm(int i0, int j0, int i1, int j1) {
	return (std::max)(std::abs(i0 - i1), std::abs(j0 - j1));
}

// L_1 norm (manhattan distance)
float FlowFieldManagmentSystems::l1_norm(int i0, int j0, int i1, int j1) {
	return std::abs(i0 - i1) + std::abs(j0 - j1);
}

bool FlowFieldManagmentSystems::astar(
	const std::array<std::uint8_t, kCostMapHeight* kCostMapWidth>& weights, const unsigned int h, const unsigned int w,
	const int start, const int goal, bool diag_ok,
	std::array<int, kCostMapWidth* kCostMapHeight>& paths) {

	constexpr float INF = std::numeric_limits<float>::infinity();

	Node start_node(start, 0.);
	Node goal_node(goal, 0.);

	//auto costs = std::unique_ptr<float[]>(new float[h * w]);
	std::unique_ptr<float[]> costs = std::make_unique<float[]>(h * w);
	//float* costs = new float[(h * w)];

	for (int i = 0; i < h * w; ++i)
		costs[i] = INF;
	costs[start] = 0.;

	std::priority_queue<Node> nodes_to_visit;
	nodes_to_visit.push(start_node);

	auto nbrs  = std::unique_ptr<int[]>(new int[8]);
	//int* nbrs = new int[8];

	bool solution_found = false;
	while (!nodes_to_visit.empty()) {
		// .top() doesn't actually remove the node
		Node cur = nodes_to_visit.top();

		if (cur == goal_node) {
			solution_found = true;
			break;
		}

		nodes_to_visit.pop();

		int row = cur.idx / w;
		int col = cur.idx % w;
		// check bounds and find up to eight neighbors: top to bottom, left to right
		nbrs[0] = (diag_ok && row > 0 && col > 0) ? cur.idx - w - 1 : -1;
		nbrs[1] = (row > 0) ? cur.idx - w : -1;
		nbrs[2] = (diag_ok && row > 0 && col + 1 < w) ? cur.idx - w + 1 : -1;
		nbrs[3] = (col > 0) ? cur.idx - 1 : -1;
		nbrs[4] = (col + 1 < w) ? cur.idx + 1 : -1;
		nbrs[5] = (diag_ok && row + 1 < h && col > 0) ? cur.idx + w - 1 : -1;
		nbrs[6] = (row + 1 < h) ? cur.idx + w : -1;
		nbrs[7] = (diag_ok && row + 1 < h && col + 1 < w) ? cur.idx + w + 1 : -1;

		float heuristic_cost;
		for (int i = 0; i < 8; ++i) {
			if (nbrs[i] >= 0) {
				// the sum of the cost so far and the cost of this move
				float new_cost = costs[cur.idx] + weights[nbrs[i]];
				if (new_cost < costs[nbrs[i]]) {
					// estimate the cost to the goal based on legal moves
					if (diag_ok) {
						heuristic_cost = linf_norm(nbrs[i] / w, nbrs[i] % w,
							goal / w, goal % w);
					}
					else {
						heuristic_cost = l1_norm(nbrs[i] / w, nbrs[i] % w,
							goal / w, goal % w);
					}

					// paths with lower expected cost are explored first
					float priority = new_cost + heuristic_cost;
					nodes_to_visit.push(Node(nbrs[i], priority));

					costs[nbrs[i]] = new_cost;
					paths[nbrs[i]] = cur.idx;
				}
			}
		}
	}

	//delete[] costs;
	//delete[] nbrs;

	return solution_found;
}

FlowFieldManagmentSystems::FlowFieldManagmentSystems()
{
	auto get2DID = [](int x, int y, int w) { return y * w + x; };

	for (int y1 = 0; y1 < kFieldsHeight; y1++)// Screen Fields Row / Height
	{
		for (int x1 = 0; x1 < kFieldsWidth; x1++) // Screen Fields Column / Width
		{
			for (int y2 = 0; y2 < kFieldWidth; y2++)// Field Row / Height
			{
				for (int x2 = 0; x2 < kFieldWidth; x2++)// Field Column / Width
				{
					if ((x1 == 0 && x2 == 0) || (x1 == (kFieldsWidth - 1) && x2 == (kFieldWidth - 1)))
					{
						costFields.fields[get2DID(x1, y1, kFieldsWidth)].nodes[get2DID(x2, y2, kFieldWidth)] = 255;
					}
					else if ((y1 == 0 && y2 == 0) || (y1 == (kFieldsHeight - 1) && y2 == (kFieldWidth - 1)))
					{
						costFields.fields[get2DID(x1, y1, kFieldsWidth)].nodes[get2DID(x2, y2, kFieldWidth)] = 255;
					}
					else
					{
						costFields.fields[get2DID(x1, y1, kFieldsWidth)].nodes[get2DID(x2, y2, kFieldWidth)] = 1;
					}
					
				}// Field Column / Width
			}// Field Row / Height
		}// Screen Fields Column / Width
	}// Screen Fields Row / Height

	newIntegrationFields.fill(65535);
	newCostMap.fill(1);
	for (auto it{newCostMap.begin()}; it != newCostMap.end(); it++)
	{
		unsigned int index = (it - newCostMap.begin());
		unsigned int yOff = std::floor(index / kCostMapWidth);
		unsigned int xOff = index % kCostMapWidth;
		if (xOff == 0 || xOff == (kCostMapWidth - 1))
		{
			*it = 255;
		}
		if (yOff == 0 || yOff == (kCostMapHeight - 1))
		{
			*it = 255;
		}
	}

	/*std::array<std::uint8_t, kCostMapWidth> _costMapWidthInitializer;
	_costMapWidthInitializer.fill(1);
	costMap.fill(_costMapWidthInitializer);*/

	//// Initializing 4D arrays SUCKS!
	//// 1D
	//std::array<std::uint8_t, kIntFieldSize> _intFieldSize;
	//_intFieldSize.fill(1);
	//// 2D
	//std::array<std::array<std::uint8_t, kIntFieldSize>, kIntFieldSize> _initializedIntField;
	//_initializedIntField.fill(_intFieldSize);
	//// 3D
	//std::array<std::array<std::array<std::uint8_t, kIntFieldSize>, kIntFieldSize>, kIntFieldWidth> _initializedIntFieldsWidth;
	//_initializedIntFieldsWidth.fill(_initializedIntField);
	//// 4D
	//integrationFields.fill(_initializedIntFieldsWidth);

	//for (auto& integrationFieldsHeight : integrationFields)
	//{
	//	for (auto& integrationFieldsWidth : integrationFieldsHeight)
	//	{
	//		for (auto& integrationFieldHeight : integrationFieldsWidth) 
	//		{
	//			for (auto& integrationFieldWidth : integrationFieldHeight)
	//			{
	//				integrationFieldWidth = 1;
	//			}
	//		}
	//	}
	//}
}

void FlowFieldManagmentSystems::render(Graphics& tmp_gfx)
{


	//4D render implementation
	/*for (auto costMapRow{ costMap.begin() }; costMapRow != costMap.end();)
	{
		for (auto costMapColumn{ costMapRow->begin() }; costMapColumn != costMapRow->end();)
		{
			for (int y = (costMapRow - costMap.begin()) * Dude::diameter; y < ((costMapRow - costMap.begin()) * Dude::diameter) + Dude::diameter; y++)
			{
				for (int x = (costMapColumn - costMapRow->begin()) * Dude::diameter; x < ((costMapColumn - costMapRow->begin()) * Dude::diameter) + Dude::diameter; x++)
				{
					if (*costMapColumn == 255)
					{
						tmp_gfx.PutPixel(x, y, 0, 0, 0);
					}
					else if (*costMapColumn <= 254 && *costMapColumn >= 2)
					{
						tmp_gfx.PutPixel(x, y, *costMapColumn, 0, 0);
					}
				}
			}
			costMapColumn++;
		}
		costMapRow++;
	}*/

	// costFields struct render implementation
	//int x = 0, y = 0;

	//for (int y1 = 0; y1 < kFieldsHeight; y1++)// Screen Fields Row / Height
	//{
	//	for (int x1 = 0; x1 < kFieldsWidth; x1++) // Screen Fields Column / Width
	//	{
	//		y = y1 * 200;			
	//		for (int y2 = 0; y2 < kFieldWidth; y2++)// Field Row / Height
	//		{
	//			x = x1 * 200;
	//			for (int x2 = 0; x2 < kFieldWidth; x2++)// Field Column / Width
	//			{					
	//				if (costFields.fields[get2DID(x1, y1, kFieldsWidth)].nodes[get2DID(x2, y2, kFieldWidth)] == 255)
	//				{
	//					tmp_gfx.drawRect(x, y, x + Dude::diameter, y + Dude::diameter, { 255, 255, 255 });
	//				}
	//				else if (costFields.fields[get2DID(x1, y1, kFieldsWidth)].nodes[get2DID(x2, y2, kFieldWidth)] <= 254
	//					&& costFields.fields[get2DID(x1, y1, kFieldsWidth)].nodes[get2DID(x2, y2, kFieldWidth)] >= 2)
	//				{
	//					tmp_gfx.drawRect(x, y, x + Dude::diameter, y + Dude::diameter, { costFields.fields[get2DID(x1, y1, kFieldsWidth)].nodes[get2DID(x2, y2, kFieldWidth)] , 0, 0 });
	//				}
	//				x += 20;
	//			}// Field Column / Width	
	//			y += 20;
	//		}// Field Row / Height
	//	}// Screen Fields Column / Width
	//}// Screen Fields Row / Height

	for (auto it{ newCostMap.begin() }; it != newCostMap.end(); it++)
	{
		unsigned int index = (it - newCostMap.begin());
		unsigned int yOff = (std::floor(index / kCostMapWidth)) * Dude::diameter;
		unsigned int xOff = (index % kCostMapWidth) * Dude::diameter;
		if (*it == 255)
		{
			tmp_gfx.drawRect(xOff, yOff, (xOff + Dude::diameter), (yOff + Dude::diameter), { 255, 255, 255 });
		}
		else if (*it <= 254 && *it >= 2)
		{
			tmp_gfx.drawRect(xOff, yOff, (xOff + Dude::diameter), (yOff + Dude::diameter), { *it, 0, 0 });
		}
	}

	for (auto it{ newIntegrationFields.begin() }; it != newIntegrationFields.end(); it++)
	{
		unsigned int index = (it - newIntegrationFields.begin());
		unsigned int yOff = (std::floor(index / kCostMapWidth)) * Dude::diameter;
		unsigned int xOff = (index % kCostMapWidth) * Dude::diameter;
		if (*it == 255)
		{
			tmp_gfx.drawRect(xOff, yOff, (xOff + Dude::diameter), (yOff + Dude::diameter), { 255, 255, 255 });
		}
		else if (*it <= 254 && *it >= 2)
		{
			tmp_gfx.drawRect(xOff, yOff, (xOff + Dude::diameter), (yOff + Dude::diameter), { (unsigned char)(*it), 0, 0 });
		}
	}

	//int x = 0, y = 0;

	//for (int y1 = 0; y1 < kFieldsHeight; y1++)// Screen Fields Row / Height
	//{
	//	for (int x1 = 0; x1 < kFieldsWidth; x1++) // Screen Fields Column / Width
	//	{
	//		y = y1 * 200;
	//		for (int y2 = 0; y2 < kFieldWidth; y2++)// Field Row / Height
	//		{
	//			x = x1 * 200;
	//			for (int x2 = 0; x2 < kFieldWidth; x2++)// Field Column / Width
	//			{
	//				if (integrationFields.fields[get2DID(x1, y1, kFieldsWidth)].nodes[get2DID(x2, y2, kFieldWidth)] <= 255)
	//				{
	//					tmp_gfx.drawRect(x, y, x + Dude::diameter, y + Dude::diameter, { 0 , (unsigned char)integrationFields.fields[get2DID(x1, y1, kFieldsWidth)].nodes[get2DID(x2, y2, kFieldWidth)], 0 });
	//				}
	//				x += 20;
	//			}// Field Column / Width	
	//			y += 20;
	//		}// Field Row / Height
	//	}// Screen Fields Column / Width
	//}// Screen Fields Row / Height

	//I couldnt get this version to work :(
	/*for (auto field{ costMap.fields.begin() }; field != costMap.fields.end();)
	{
		int iField = field - costMap.fields.begin();
		int fieldYOff = ((iField - (iField % kNodeWidth)) / kNodeWidth) * (Dude::diameter * kIntFieldSize);
		int fieldXOff = (iField % kNodeWidth) * (Dude::diameter * kIntFieldSize);
		for (auto node{ field->nodes.begin()}; node != field->nodes.end();)
		{
			int iNode = node - field->nodes.begin();
			int nodeYOff = ((iNode - (iNode % kIntFieldSize)) / kIntFieldSize) * (Dude::diameter);
			int nodeXOff = (iNode % kIntFieldSize) * (Dude::diameter);
			if (*node == 255)
			{						
				for (int y = fieldYOff + nodeYOff; y < (fieldYOff + nodeYOff) + Dude::diameter; y++)
				{
					for (int x = fieldXOff + nodeXOff; x < (fieldXOff + nodeXOff) + Dude::diameter; x++)
					{
						tmp_gfx.PutPixel(x, y, 0, 0, 0);
					}
				}
			}
			else if (*node <= 254 && *node >= 2)
			{
				for (int y = fieldYOff + nodeYOff; y < (fieldYOff + nodeYOff) + Dude::diameter; y++)
				{
					for (int x = fieldXOff + nodeXOff; x < (fieldXOff + nodeXOff) + Dude::diameter; x++)
					{
						tmp_gfx.PutPixel(x, y, 0, *node, 0);
					}
				}
			}
			node++;
		}
		field++;
	}*/
}

void FlowFieldManagmentSystems::resetIntegrationField(unsigned int fieldID)
{
	integrationFields.fields[fieldID].nodes.fill(65535);
}

void FlowFieldManagmentSystems::resetIntegrationFields()
{
	for (auto& field : integrationFields.fields)
	{
		field.nodes.fill(65535);
	}
}

void FlowFieldManagmentSystems::adjustIntegraionFields(int tmp_x, int tmp_y, unsigned int nodeCostValue)
{
	auto get2DID = [](int x, int y, int w) { return y * w + x; };

	int fieldX = std::floor(tmp_x / Dude::diameter / kFieldWidth);
	int fieldY = std::floor(tmp_y / Dude::diameter / kFieldWidth);
	int nodeX = std::floor((tmp_x / (int)Dude::diameter) % kFieldWidth);
	int nodeY = std::floor((tmp_y / (int)Dude::diameter) % kFieldWidth);

	integrationFields.fields[get2DID(fieldX, fieldY, kFieldsWidth)].nodes[get2DID(nodeX, nodeY, kFieldWidth)] = nodeCostValue;
}

void FlowFieldManagmentSystems::adjustCostMap(int tmp_x, int tmp_y, std::uint8_t nodeCostValue)
{	
	/*unsigned int fieldID = getFieldID(tmp_x, tmp_y);
	unsigned int nodeID = getNodeID(tmp_x, tmp_y);*/

	unsigned int nodeID = get2DID(tmp_x / Dude::diameter, tmp_y / Dude::diameter, kCostMapWidth);

	newCostMap[nodeID] = nodeCostValue;

	//costFields.fields[fieldID].nodes[nodeID] = nodeCostValue;

	//costMap[mapY][mapX] = nodeCostValue;


	/*float fieldX = _x  / Dude::diameter / kIntFieldSize;
	float fieldY = _y / Dude::diameter / kIntFieldSize;
	float nodeX = (_x / (int)Dude::diameter) % 10;
	float nodeY = (_y / (int)Dude::diameter) % 10;

	costMap.fields[std::floor(fieldX * fieldY)].nodes[std::floor(nodeX * nodeY)] = nodeCostValue;*/
}

void FlowFieldManagmentSystems::aStarIntegrationFields( EntStruct& tmp_ents, unsigned int tmp_x, unsigned int tmp_y)
{
	auto getFieldCoord = [&](unsigned int xy) { return (unsigned int)std::floor(xy / Dude::diameter / kFieldWidth); };
	auto getNodeCoord = [&](unsigned int xy) { return (unsigned int)std::floor(xy / (int)Dude::diameter); };

	auto getDistance = [](unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2)
	{
		return (std::sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2)));
	};

	unsigned int fieldX = getFieldCoord(tmp_x);
	unsigned int fieldY = getFieldCoord(tmp_y);
	unsigned int nodeX = getNodeCoord(tmp_x);
	unsigned int nodeY = getNodeCoord(tmp_y);
	unsigned int fieldID = getFieldID(tmp_x, tmp_y);
	unsigned int nodeID = get2DID(tmp_x / Dude::diameter, tmp_y / Dude::diameter, kCostMapWidth);
	
	// Gets every unique field ID from all of the selected dudes.
	// incase there are some dudes that are seperated from the rest.

	


	std::vector<std::array<unsigned int, 4>> uniqueFieldCoords;

	for (auto& dude : tmp_ents.staticSelectedDudesPos)
	{
		if (std::find(uniqueFieldCoords.begin(), uniqueFieldCoords.end(), std::array<unsigned int, 4>({ getFieldCoord(dude.x), getFieldCoord(dude.y), getNodeCoord(dude.x), getNodeCoord(dude.y) })) == uniqueFieldCoords.end())
		{
			uniqueFieldCoords.push_back({ getFieldCoord(dude.x), getFieldCoord(dude.y), getNodeCoord(dude.x), getNodeCoord(dude.y) });
		}
	}

	for (auto& dude : tmp_ents.movingSelectedDudesPos)
	{
		if (std::find(uniqueFieldCoords.begin(), uniqueFieldCoords.end(), std::array<unsigned int, 4>({ getFieldCoord(dude.x), getFieldCoord(dude.y), getNodeCoord(dude.x), getNodeCoord(dude.y) })) == uniqueFieldCoords.end())
		{
			uniqueFieldCoords.push_back({ getFieldCoord(dude.x), getFieldCoord(dude.y), getNodeCoord(dude.x), getNodeCoord(dude.y) });
		}
	}

	resetIntegrationFields();
	
	

	//Go through each unique field ID and calculate a path to the goal
	for (auto& ent : uniqueFieldCoords)
	{
		std::array<int, kCostMapWidth* kCostMapHeight> paths;
		paths.fill(-1);

		if (astar(newCostMap, kCostMapHeight, kCostMapWidth, get2DID(ent[2], ent[3], kCostMapWidth),
			nodeID, (false), paths))
		{
			int currentNode = paths[nodeID];

			calculateIntegrationField(nodeID);

			while (currentNode != -1)
			{
				if ((currentNode % 70) % 10 == 0 || ((int)(std::floor(currentNode / 70)) % 10) == 0)
				{
					calculateIntegrationField(currentNode);
				}
				currentNode = paths[currentNode];
			}
		}
		
	}



	//	Node currentNode;		

	//	calculateIntegrationField(nodeX, nodeY);

	//	// Send the coord of every node that intersects with the edge of a field.
	//	while (currentNode.parent != nullptr)
	//	{
	//		if (currentNode.x % kFieldWidth == 0 || currentNode.y % kFieldWidth == 0)
	//		{
	//			calculateIntegrationField(currentNode.x, currentNode.y);
	//		}
	//		currentNode = *currentNode.parent;
	//	}
	//}
}

void FlowFieldManagmentSystems::calculateIntegrationField(unsigned int nodeIndex)
{
	
	unsigned int fieldsID = std::floor(nodeIndex / kFieldSize);
	//unsigned int fieldID = nodeIndex % kFieldSize;

	unsigned int w = kCostMapWidth, h = kCostMapHeight;
	bool diag_ok = false;

	//unsigned int nodeID = getNodeID(tmp_x, tmp_y);

	for (int i = nodeIndex - (nodeIndex % kCostMapWidth); i < kFieldSize; i++)
	{
		newIntegrationFields[i] = 65535;
	}

	//resetIntegrationField(fieldsID);
	newIntegrationFields[nodeIndex] = 0;

	std::priority_queue<Node> nodes_to_visit;
	nodes_to_visit.emplace(nodeIndex, 0);

	auto nbrs = std::unique_ptr<int[]>(new int[8]);

	while (!nodes_to_visit.empty()) {
		// .top() doesn't actually remove the node
		Node cur = nodes_to_visit.top();

		nodes_to_visit.pop();


		int row = cur.idx / w;
		int col = cur.idx % w;
		int curFieldsID = std::floor(cur.idx / kFieldSize), curFieldID = cur.idx % kFieldSize;
		// check bounds and find up to eight neighbors: top to bottom, left to right
		nbrs[0] = (diag_ok && row > 0 && col > 0 && newCostMap[(cur.idx - w - 1)] != 255) ? cur.idx - w - 1 : -1;
		nbrs[1] = (row > 0 && newCostMap[cur.idx - w] != 255) ? cur.idx - w : -1;
		nbrs[2] = (diag_ok && row > 0 && col + 1 < w && newCostMap[(cur.idx - w + 1)] != 255) ? cur.idx - w + 1 : -1;
		nbrs[3] = (col > 0 && newCostMap[cur.idx - 1] != 255) ? cur.idx - 1 : -1;
		nbrs[4] = (col + 1 < w && newCostMap[(cur.idx + 1)] != 255) ? cur.idx + 1 : -1;
		nbrs[5] = (diag_ok && row + 1 < h && col > 0 && newCostMap[cur.idx + w - 1] != 255) ? cur.idx + w - 1 : -1;
		nbrs[6] = (row + 1 < h && newCostMap[cur.idx + w] != 255) ? cur.idx + w : -1;
		nbrs[7] = (diag_ok && row + 1 < h && col + 1 < w && newCostMap[cur.idx + w + 1] != 255) ? cur.idx + w + 1 : -1;

		for (int i = 0; i < 8; ++i) {
			if (nbrs[i] >= 0 && std::floor(nbrs[i] / kFieldSize) == fieldsID) {
				//int nbrsFieldsID = std::floor(nbrs[i] / kFieldSize), nbrsFieldID = nbrs[i] % kFieldSize;
				// the sum of the cost so far and the cost of this move
				float new_cost = newIntegrationFields[cur.idx] + newCostMap[nbrs[i]];
				if (new_cost < newIntegrationFields[nbrs[i]]) {
					// paths with lower expected cost are explored first
					nodes_to_visit.emplace(nbrs[i], new_cost + 1);

					newIntegrationFields[nbrs[i]] = new_cost;
				}
			}
		}
	}



	/*std::list<Node> openList;

	adjustIntegraionFields(nodeX, nodeY, 0);
	openList.push_back({ nodeIndex, 0 });

	while (openList.size() > 0)
	{
		std::array<Node>

		Node currentID = openList.front();
		openList.pop_front();

		auto nbrs = std::unique_ptr<int[]>(new int[8]);

		nbrs[0] = 0;

		for (auto it{nbrs->begin()}; it != neighbors.end(); it++)
		{
			if ((*it)[4] > currentID[4] + 1)
			{
				if (std::find(openList.begin(), openList.end(), *it) == openList.end())
				{
					(*it)[4] = currentID[4] + 1;
					openList.emplace_back(*it);
				}
				integrationFields.fields[get2DID((*it)[0], (*it)[1], kFieldsWidth)].nodes[get2DID((*it)[2], (*it)[3], kFieldWidth)] = (*it)[4];
			}			
		}
	}*/


	/*integrationFields.fields[get2DID((*it)[0], (*it)[1], kFieldsWidth)].nodes[get2DID((*it)[2], (*it)[3], kFieldWidth)]
		= (*it)[4] + costFields.fields[get2DID((*it)[0], (*it)[1], kFieldsWidth)].nodes[get2DID((*it)[2], (*it)[3], kFieldWidth)];*/
}

void FlowFieldManagmentSystems::calculateVectorField(std::uint8_t[kFieldWidth][kFieldWidth])
{
}
