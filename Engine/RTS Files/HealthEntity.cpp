#include "HealthEntity.h"

HealthEntity::HealthEntity(int _uuid, int _entNum, float _health, float _damageTaking) :
	uuid(_uuid),
	entNum(_entNum),
	health(_health),
	damageTaking(_damageTaking)
{
}
