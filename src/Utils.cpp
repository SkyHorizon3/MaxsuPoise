#include "Utils.h"

namespace MaxsuPoise
{
	float GetActorMass(RE::Actor* a_target)
	{
		if (!a_target || !a_target->GetActorRuntimeData().race)
			return 0.f;

		return a_target->GetActorValue(RE::ActorValue::kMass);
	}

	void CPrint(const char* a_fmt, ...)
	{
		auto console = RE::ConsoleLog::GetSingleton();
		if (console) {
			std::va_list args;
			va_start(args, a_fmt);
			console->VPrint(a_fmt, args);
			va_end(args);
		}
	}

	RE::hkbClipGenerator* ToClipGenerator(RE::hkbNode* a_node)
	{
		constexpr char CLASS_NAME[] = "hkbClipGenerator";

		if (a_node && a_node->GetClassType()) {
			if (_strcmpi(a_node->GetClassType()->name, CLASS_NAME) == 0)
				return skyrim_cast<RE::hkbClipGenerator*>(a_node);
		}

		return nullptr;
	}

}
