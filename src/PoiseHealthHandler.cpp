#include "PoiseHealthHandler.h"
#include "SettingsHandler.h"
#include "Utils.h"

namespace MaxsuPoise
{
	inline constexpr const char* CURRENT_POISE_HEALTH_GV = "MaxsuPoise_PoiseHealth";

	float PoiseHealthHandler::GetCurrentPoiseHealth(RE::Actor* a_target)
	{
		float result = 0.f;
		if (!a_target || !a_target->GetGraphVariableFloat(CURRENT_POISE_HEALTH_GV, result))
			SKSE::log::warn("Not Graph Variable Float Found: {}", CURRENT_POISE_HEALTH_GV);

		return result;
	}

	bool PoiseHealthHandler::SetCurrentPoiseHealth(RE::Actor* a_target, const float& a_in)
	{
		return a_target && a_target->SetGraphVariableFloat(CURRENT_POISE_HEALTH_GV, a_in);
	}

	float PoiseHealthHandler::GetTotalPoiseHealth(RE::Actor* a_target)
	{
		if (!a_target)
			return 0.f;

		auto actorPoiseHealth = GetBasePoiseHealth() * GetActorMass(a_target) * a_target->GetScale();
		auto armorPoiseHealth = GetTotalArmorPoiseHealth(a_target);
		return actorPoiseHealth + armorPoiseHealth;
	}

	float PoiseHealthHandler::GetBasePoiseHealth()
	{
		const auto gs = "fMaxsuPoise_BasePoiseHealth"_gs;
		return gs.has_value() ? *gs : 40.f;
	}

	float PoiseHealthHandler::GetTotalArmorPoiseHealth(RE::Actor* a_target)
	{
		float result = 0.f;

		if (!a_target)
			return result;

		auto baseArmorPoiseHealth = GetBaseArmorPoiseHealth();
		auto heavyArmorBouns = GetHeavyArmorBouns();

		for (const auto& pair : SettingsHandler::GetSingleton()->armorSlotMultMap) {
			auto slot = pair.first;
			auto armor = a_target->GetWornArmor(slot);
			auto armorHealth = baseArmorPoiseHealth * pair.second;
			if (armor && (armor->IsLightArmor() || armor->IsHeavyArmor())) {
				result += armor->IsLightArmor() ? armorHealth : armorHealth * (1 + heavyArmorBouns);
			} else {
				armor = a_target->GetSkin(slot);
				if (armor && (armor->IsLightArmor() || armor->IsHeavyArmor()))
					result += armor->IsLightArmor() ? armorHealth : armorHealth * (1 + heavyArmorBouns);
			}
		}

		return result;
	}

	float PoiseHealthHandler::GetBaseArmorPoiseHealth()
	{
		const auto gs = "fMaxsuPoise_BaseArmorPoiseHealth"_gs;
		return gs.has_value() ? *gs : 50.f;
	}

	float PoiseHealthHandler::GetHeavyArmorBouns()
	{
		const auto gs = "fMaxsuPoise_HeavyArmorPoiseBonus"_gs;
		return gs.has_value() ? *gs : 0.5f;
	}
}