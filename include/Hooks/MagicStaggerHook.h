#pragma once

namespace MaxsuPoise
{
	class MagicStaggerHook
	{
	public:
		static void InstallHooks()
		{
			Hooks::Install();
		}

	protected:
		struct Hooks
		{
			struct ProcessStagger
			{
				static void thunk(RE::Actor* a_target, float a_staggerMult, RE::Actor* a_aggressor);

				static inline REL::Relocation<decltype(thunk)> func;
			};

			static void Install()
			{
				REL::Relocation<std::uintptr_t> target1{ RELOCATION_ID(34188, 34982), 0x6F };
				stl::write_thunk_call<ProcessStagger>(target1.address());  // 1.5.97 140628C20
			}
		};

	private:
		constexpr MagicStaggerHook() noexcept = default;
		MagicStaggerHook(const MagicStaggerHook&) = delete;
		MagicStaggerHook(MagicStaggerHook&&) = delete;

		~MagicStaggerHook() = default;

		MagicStaggerHook& operator=(const MagicStaggerHook&) = delete;
		MagicStaggerHook& operator=(MagicStaggerHook&&) = delete;
	};
}