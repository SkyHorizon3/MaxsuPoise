#include "LoadGame.h"
#include "Hooks/HitEventHandler.h"
#include "Hooks/MagicStaggerHook.h"
#include "Hooks/PerkEntry_Hooks.h"
#include "Hooks/PoiseRegenHandler.h"
#include "SettingsHandler.h"

namespace MaxsuPoise
{
	void EventCallback(SKSE::MessagingInterface::Message* msg)
	{
		if (msg->type == SKSE::MessagingInterface::kPostPostLoad) {
			constexpr auto bdiDLLName = "BehaviorDataInjector.dll";
			const auto bdiPlugin = REX::W32::GetModuleHandleA(bdiDLLName);
			if (!bdiPlugin) {
				SKSE::log::error("Not \"{}\" Loaded!", bdiDLLName);
				return;
			}

			MaxsuPoise::SettingsHandler::Register();

			SKSE::AllocTrampoline(56);
			MaxsuPoise::HitEventHandler::InstallHooks();
			MaxsuPoise::MagicStaggerHook::InstallHooks();
			MaxsuPoise::PoiseRegenHandler::CharacterEx::InstallHook();
			MaxsuPoise::PoiseRegenHandler::PlayerEx::InstallHook();
			MaxsuPoise::PerkEntryHook::Install();
		}
	}

}
