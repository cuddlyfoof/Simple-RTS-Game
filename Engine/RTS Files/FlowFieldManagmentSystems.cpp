#include "FlowFieldManagmentSystems.h"
#include "Dude.h"
#include <cmath>
#include <list>
#include <algorithm>

std::vector<std::array<unsigned int, 5>> FlowFieldManagmentSystems::getNeighbors(std::array<unsigned int, 5> node)
{
	std::vector<std::array<unsigned int, 5>> neighbors;
	
	// Get west neightbor if it is within the field and is not a wall
	if (node[2] > 0 
		&& costFields.fields[get2DID(node[0], node[1], kFieldsWidth)].nodes[get2DID(node[2] - 1, node[3], kFieldWidth)] != 255)
	{
		neighbors.push_back({ node[0], node[1], node[2] - 1, node[3], integrationFields.fields[get2DID(node[0], node[1], kFieldsWidth)].nodes[get2DID(node[2] - 1, node[3], kFieldWidth)] });
	}
	// East
	if (node[2] < kFieldWidth - 1
		&& costFields.fields[get2DID(node[0], node[1], kFieldsWidth)].nodes[get2DID(node[2] + 1, node[3], kFieldWidth)] != 255)
	{
		neighbors.push_back({ node[0], node[1], node[2] + 1, node[3], integrationFields.fields[get2DID(node[0], node[1], kFieldsWidth)].nodes[get2DID(node[2] + 1, node[3], kFieldWidth)] });
	}
	// North
	if (node[3] > 0 
		&& costFields.fields[get2DID(node[0], node[1], kFieldsWidth)].nodes[get2DID(node[2], node[3] - 1, kFieldWidth)] != 255)
	{
		neighbors.push_back({ node[0], node[1], node[2], node[3] - 1, integrationFields.fields[get2DID(node[0], node[1], kFieldsWidth)].nodes[get2DID(node[2], node[3] - 1, kFieldWidth)] });
	}
	// South
	if (node[3] < kFieldWidth -1
		&& costFields.fields[get2DID(node[0], node[1], kFieldsWidth)].nodes[get2DID(node[2], node[3] + 1, kFieldWidth)] != 255)
	{
		neighbors.push_back({ node[0], node[1], node[2], node[3] + 1, integrationFields.fields[get2DID(node[0], node[1], kFieldsWidth)].nodes[get2DID(node[2], node[3] + 1, kFieldWidth)] });
	}

	return neighbors;
}

unsigned int FlowFieldManagmentSystems::get2DID(unsigned int tmp_x, unsigned int tmp_y, unsigned int tmp_w)
{
	return tmp_y * tmp_w + tmp_x;
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
	auto get2DID = [](int x, int y, int w) { return y * w + x; };

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

	int x = 0, y = 0;

	for (int y1 = 0; y1 < kFieldsHeight; y1++)// Screen Fields Row / Height
	{
		for (int x1 = 0; x1 < kFieldsWidth; x1++) // Screen Fields Column / Width
		{
			y = y1 * 200;			
			for (int y2 = 0; y2 < kFieldWidth; y2++)// Field Row / Height
			{
				x = x1 * 200;
				for (int x2 = 0; x2 < kFieldWidth; x2++)// Field Column / Width
				{					
					if (costFields.fields[get2DID(x1, y1, kFieldsWidth)].nodes[get2DID(x2, y2, kFieldWidth)] == 255)
					{
						tmp_gfx.drawRect(x, y, x + Dude::diameter, y + Dude::diameter, { 255, 255, 255 });
					}
					else if (costFields.fields[get2DID(x1, y1, kFieldsWidth)].nodes[get2DID(x2, y2, kFieldWidth)] <= 254
						&& costFields.fields[get2DID(x1, y1, kFieldsWidth)].nodes[get2DID(x2, y2, kFieldWidth)] >= 2)
					{
						tmp_gfx.drawRect(x, y, x + Dude::diameter, y + Dude::diameter, { costFields.fields[get2DID(x1, y1, kFieldsWidth)].nodes[get2DID(x2, y2, kFieldWidth)] , 0, 0 });
					}
					x += 20;
				}// Field Column / Width	
				y += 20;
			}// Field Row / Height
		}// Screen Fields Column / Width
	}// Screen Fields Row / Height

	x = 0, y = 0;

	for (int y1 = 0; y1 < kFieldsHeight; y1++)// Screen Fields Row / Height
	{
		for (int x1 = 0; x1 < kFieldsWidth; x1++) // Screen Fields Column / Width
		{
			y = y1 * 200;
			for (int y2 = 0; y2 < kFieldWidth; y2++)// Field Row / Height
			{
				x = x1 * 200;
				for (int x2 = 0; x2 < kFieldWidth; x2++)// Field Column / Width
				{
					if (integrationFields.fields[get2DID(x1, y1, kFieldsWidth)].nodes[get2DID(x2, y2, kFieldWidth)] <= 255)
					{
						tmp_gfx.drawRect(x, y, x + Dude::diameter, y + Dude::diameter, { 0 , (unsigned char)integrationFields.fields[get2DID(x1, y1, kFieldsWidth)].nodes[get2DID(x2, y2, kFieldWidth)], 0 });
					}
					x += 20;
				}// Field Column / Width	
				y += 20;
			}// Field Row / Height
		}// Screen Fields Column / Width
	}// Screen Fields Row / Height

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
	unsigned int fieldID = getFieldID(tmp_x, tmp_y);
	unsigned int nodeID = getNodeID(tmp_x, tmp_y);

	costFields.fields[fieldID].nodes[nodeID] = nodeCostValue;

	//costMap[mapY][mapX] = nodeCostValue;


	/*float fieldX = _x  / Dude::diameter / kIntFieldSize;
	float fieldY = _y / Dude::diameter / kIntFieldSize;
	float nodeX = (_x / (int)Dude::diameter) % 10;
	float nodeY = (_y / (int)Dude::diameter) % 10;

	costMap.fields[std::floor(fieldX * fieldY)].nodes[std::floor(nodeX * nodeY)] = nodeCostValue;*/
}

void FlowFieldManagmentSystems::calculateIntegrationField(unsigned int tmp_x, unsigned int tmp_y)
{
	unsigned int fieldX = std::floor(tmp_x / Dude::diameter / kFieldWidth);
	unsigned int fieldY = std::floor(tmp_y / Dude::diameter / kFieldWidth);
	unsigned int nodeX = std::floor((tmp_x / (int)Dude::diameter) % kFieldWidth);
	unsigned int nodeY = std::floor((tmp_y / (int)Dude::diameter) % kFieldWidth);
	unsigned int fieldID = getFieldID(tmp_x, tmp_y);
	//unsigned int nodeID = getNodeID(tmp_x, tmp_y);

	resetIntegrationFields();
	std::list<std::array<unsigned int, 5>> openList;

	adjustIntegraionFields(tmp_x, tmp_y, 0);
	openList.push_back({ fieldX, fieldY, nodeX, nodeY, 0 });

	while (openList.size() > 0)
	{
		std::array<unsigned int, 5> currentID = openList.front();
		openList.pop_front();

		std::vector<std::array<unsigned int, 5>> neighbors = getNeighbors(currentID);

		for (auto it{neighbors.begin()}; it != neighbors.end(); it++)
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
	}


	/*integrationFields.fields[get2DID((*it)[0], (*it)[1], kFieldsWidth)].nodes[get2DID((*it)[2], (*it)[3], kFieldWidth)]
		= (*it)[4] + costFields.fields[get2DID((*it)[0], (*it)[1], kFieldsWidth)].nodes[get2DID((*it)[2], (*it)[3], kFieldWidth)];*/
}

void FlowFieldManagmentSystems::calculateVectorField(std::uint8_t[kFieldWidth][kFieldWidth])
{
}
