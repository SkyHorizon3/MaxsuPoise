#pragma once

namespace MaxsuPoise
{
	class PerkEntryHook
	{
		PerkEntryHook() = delete;
		~PerkEntryHook() = delete;

	public:
		static void Install()
		{
			constexpr auto address = RELOCATION_ID(36700, 37710);
			REL::Relocation<std::uintptr_t> target1{ address, REL::Relocate(0x9A, 0xA1, 0x9A) };
			REL::Relocation<std::uintptr_t> target2{ address, REL::Relocate(0xAE, 0xB9, 0xAE) };

			stl::write_thunk_call<ApplyPerkEntryPoint_Aggressor>(target1.address());  // 1.5.97 1405FA1B0
			stl::write_thunk_call<ApplyPerkEntryPoint_Target>(target2.address());     // 1.5.97 1405FA1B0
		}

	private:
		struct ApplyPerkEntryPoint_Aggressor
		{
			static void thunk(std::int32_t, RE::Actor*, RE::Actor*, float&)
			{
				return;
			}
			static inline REL::Relocation<decltype(thunk)> func;
		};

		struct ApplyPerkEntryPoint_Target
		{
			static void thunk(std::int32_t, RE::Actor*, RE::Actor*, float&)
			{
				return;
			}
			static inline REL::Relocation<decltype(thunk)> func;
		};
	};

}