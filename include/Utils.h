#pragma once
#include "AnnoInfo.h"

namespace MaxsuPoise
{
	float GetActorMass(RE::Actor* a_target);

	void CPrint(const char* a_fmt, ...);

	RE::hkbClipGenerator* ToClipGenerator(RE::hkbNode* a_node);
}