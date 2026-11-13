#pragma once

namespace MaxsuPoise
{
	class HitEventHandler
	{
	public:
		static void InstallHooks()
		{
			Hooks::Install();
		}

	protected:
		struct Hooks
		{
			struct ProcessHitEvent
			{
				static void thunk(RE::Actor* target, RE::HitData* hitData);

				static inline REL::Relocation<decltype(thunk)> func;
			};

			static void Install()
			{
				REL::Relocation<std::uintptr_t> target1{ RELOCATION_ID(37673, 38627), REL::Relocate(0x3C0, 0x4A8, 0x3C0) };
				stl::write_thunk_call<ProcessHitEvent>(target1.address());  // 1.5.97 140628C20
			}
		};

	private:
		constexpr HitEventHandler() noexcept = default;
		HitEventHandler(const HitEventHandler&) = delete;
		HitEventHandler(HitEventHandler&&) = delete;

		~HitEventHandler() = default;

		HitEventHandler& operator=(const HitEventHandler&) = delete;
		HitEventHandler& operator=(HitEventHandler&&) = delete;
	};
}