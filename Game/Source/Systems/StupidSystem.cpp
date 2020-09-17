#include "StupidSystem.h"

void StupidSystem::Init()
{
}

void StupidSystem::Process(StupidComponent& component)
{
	component.CharValue--;
}
