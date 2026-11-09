#include "SettingsHandler.h"
#include "SimpleIni.h"

namespace MaxsuPoise
{
	bool SettingsHandler::Register()
	{
		UpdateWeapTypeMult();
		InitArmorSlotMult();

		auto eventSource = SKSE::GetModCallbackEventSource();
		if (!eventSource) {
			SKSE::log::error("EventSource not found!");
			return false;
		}

		auto singleton = GetSingleton();
		eventSource->AddEventSink(singleton);

		SKSE::log::info("Register {}", typeid(singleton).name());

		return true;
	}

	static std::optional<RE::WEAPON_TYPE> WeaponTypeFromString(std::string_view nameIn)
	{
		constexpr std::array<std::pair<std::string_view, RE::WEAPON_TYPE>, 10> weaponTypeNames{ {
			{ "kHandToHandMelee", RE::WEAPON_TYPE::kHandToHandMelee },
			{ "kOneHandSword", RE::WEAPON_TYPE::kOneHandSword },
			{ "kOneHandDagger", RE::WEAPON_TYPE::kOneHandDagger },
			{ "kOneHandAxe", RE::WEAPON_TYPE::kOneHandAxe },
			{ "kOneHandMace", RE::WEAPON_TYPE::kOneHandMace },
			{ "kTwoHandSword", RE::WEAPON_TYPE::kTwoHandSword },
			{ "kTwoHandAxe", RE::WEAPON_TYPE::kTwoHandAxe },
			{ "kBow", RE::WEAPON_TYPE::kBow },
			{ "kStaff", RE::WEAPON_TYPE::kStaff },
			{ "kCrossbow", RE::WEAPON_TYPE::kCrossbow },
		} };

		for (const auto& [name, type] : weaponTypeNames) {
			if (clib_util::string::iequals(name, nameIn)) {
				return type;
			}
		}
		return std::nullopt;
	}

	static std::optional<RE::BGSBipedObjectForm::BipedObjectSlot> BipedObjectSlotFromString(std::string_view nameIn)
	{
		using Slot = RE::BGSBipedObjectForm::BipedObjectSlot;

		constexpr std::array<std::pair<std::string_view, Slot>, 33> slotNames{ {
			{ "kNone", Slot::kNone },
			{ "kHead", Slot::kHead },
			{ "kHair", Slot::kHair },
			{ "kBody", Slot::kBody },
			{ "kHands", Slot::kHands },
			{ "kForearms", Slot::kForearms },
			{ "kAmulet", Slot::kAmulet },
			{ "kRing", Slot::kRing },
			{ "kFeet", Slot::kFeet },
			{ "kCalves", Slot::kCalves },
			{ "kShield", Slot::kShield },
			{ "kTail", Slot::kTail },
			{ "kLongHair", Slot::kLongHair },
			{ "kCirclet", Slot::kCirclet },
			{ "kEars", Slot::kEars },
			{ "kModMouth", Slot::kModMouth },
			{ "kModNeck", Slot::kModNeck },
			{ "kModChestPrimary", Slot::kModChestPrimary },
			{ "kModBack", Slot::kModBack },
			{ "kModMisc1", Slot::kModMisc1 },
			{ "kModPelvisPrimary", Slot::kModPelvisPrimary },
			{ "kDecapitateHead", Slot::kDecapitateHead },
			{ "kDecapitate", Slot::kDecapitate },
			{ "kModPelvisSecondary", Slot::kModPelvisSecondary },
			{ "kModLegRight", Slot::kModLegRight },
			{ "kModLegLeft", Slot::kModLegLeft },
			{ "kModFaceJewelry", Slot::kModFaceJewelry },
			{ "kModChestSecondary", Slot::kModChestSecondary },
			{ "kModShoulder", Slot::kModShoulder },
			{ "kModArmLeft", Slot::kModArmLeft },
			{ "kModArmRight", Slot::kModArmRight },
			{ "kModMisc2", Slot::kModMisc2 },
			{ "kFX01", Slot::kFX01 },
		} };

		for (const auto& [name, slot] : slotNames) {
			if (clib_util::string::iequals(name, nameIn)) {
				return slot;
			}
		}
		return std::nullopt;
	}

	void SettingsHandler::UpdateWeapTypeMult()
	{
		const auto path = std::format("Data/SKSE/Plugins/{}.ini", Plugin::NAME);

		CSimpleIniA ini;
		ini.SetUnicode();
		if (ini.LoadFile(path.c_str()) < 0) {
			return;
		}

		const auto section = ini.GetSection("WeaponTypeMult");
		if (!section) {
			return;
		}

		for (const auto& [keyEntry, value] : *section) {
			const auto weapEnum = WeaponTypeFromString(keyEntry.pItem);
			if (!weapEnum) {
				continue;
			}
			weapTypeMultMap[*weapEnum] = clib_util::string::to_num<float>(value);
		}
	}

	void SettingsHandler::InitArmorSlotMult()
	{
		const auto path = std::format("Data/SKSE/Plugins/{}_ArmorSlot.ini", Plugin::NAME);

		CSimpleIniA ini;
		ini.SetUnicode();
		if (ini.LoadFile(path.c_str()) < 0) {
			return;
		}

		const auto section = ini.GetSection("ArmorSlotMult");
		if (!section) {
			return;
		}

		for (const auto& [keyEntry, value] : *section) {
			const auto armorSlot = BipedObjectSlotFromString(keyEntry.pItem);
			if (!armorSlot) {
				continue;
			}
			armorSlotMultMap[*armorSlot] = clib_util::string::to_num<float>(value);
		}
	}

}
