#include "Hooks/HitEventHandler.h"
#include "StaggerHandler.h"

namespace MaxsuPoise
{
	void HitEventHandler::Hooks::ProcessHitEvent::thunk(RE::Actor* target, RE::HitData* hitData)
	{
		StaggerHandler::ProcessWeaponStagger(hitData);
		hitData->stagger = 0.0f;

		func(target, hitData);
	}
}