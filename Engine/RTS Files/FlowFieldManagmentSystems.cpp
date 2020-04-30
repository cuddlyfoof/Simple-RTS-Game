#include "FlowFieldManagmentSystems.h"
#include "Dude.h"
#include <cmath>

FlowFieldManagmentSystems::FlowFieldManagmentSystems()
{
	std::array<std::uint8_t, kCostMapWidth> _costMapWidthInitializer;
	_costMapWidthInitializer.fill(1);
	costMap.fill(_costMapWidthInitializer);

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

void FlowFieldManagmentSystems::adjustCostMap(std::array<std::array<std::uint8_t, kCostMapWidth>, kCostMapHeight> _costMap, int _x, int _y, std::uint8_t nodeCostValue)
{
	int mapX = _x / std::ceil(Dude::diameter);
	int mapY = _y / std::ceil(Dude::diameter);

	_costMap[mapY][mapX] = nodeCostValue;
}

void FlowFieldManagmentSystems::calculateIntegrationField(std::uint8_t[kIntFieldSize][kIntFieldSize])
{
}

void FlowFieldManagmentSystems::calculateVectorField(std::uint8_t[kIntFieldSize][kIntFieldSize])
{
}
