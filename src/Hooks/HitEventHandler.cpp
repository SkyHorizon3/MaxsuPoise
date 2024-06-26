#include "Hooks/HitEventHandler.h"
#include "StaggerHandler.h"

namespace MaxsuPoise
{
	void HitEventHandler::Hooks::ProcessHitEvent::thunk(RE::Actor* target, RE::HitData* hitData)
	{
		StaggerHandler::ProcessWeaponStagger(hitData);
		hitData->stagger = static_cast<uint32_t>(0.00);

		func(target, hitData);
	}
}