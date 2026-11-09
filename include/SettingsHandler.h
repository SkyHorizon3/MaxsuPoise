#pragma once

namespace MaxsuPoise
{
	using WEAPON_TYPE = RE::WEAPON_TYPE;
	using BipedSlot = RE::BipedObjectSlot;
	using EventResult = RE::BSEventNotifyControl;

	class SettingsHandler :
		public REX::Singleton<SettingsHandler>,
		public RE::BSTEventSink<SKSE::ModCallbackEvent>
	{
	public:
		std::map<WEAPON_TYPE, float> weapTypeMultMap;
		std::map<BipedSlot, float> armorSlotMultMap;

		static bool Register();

		EventResult ProcessEvent(const SKSE::ModCallbackEvent* a_event, RE::BSTEventSource<SKSE::ModCallbackEvent>* a_eventSource) override
		{
			if (a_event && _strcmpi(a_event->eventName.c_str(), "dmenu_updateSettings") == 0 && _strcmpi(a_event->strArg.c_str(), Plugin::NAME.data()) == 0) {
				UpdateWeapTypeMult();
			}

			return EventResult::kContinue;
		}

	private:
		void UpdateWeapTypeMult();
		void InitArmorSlotMult();
	};

}