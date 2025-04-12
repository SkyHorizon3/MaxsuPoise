#pragma once

namespace MaxsuPoise
{
	enum StaggerLevel : std::uint32_t
	{
		kNone = 0,
		kSmall,
		kMedium,
		kLarge,
		kLargest,
	};

	class StaggerHandler
	{
	public:
		static void ProcessWeaponStagger(const RE::HitData* a_hitdata);
		static void ProcessMagicStagger(RE::Actor* a_target, float a_staggerMult, RE::Actor* a_aggressor);

	private:
		static StaggerLevel GetStaggerLevel(const float& a_DamagePercent);

		StaggerHandler() = delete;

		~StaggerHandler() = delete;
	};

	class ImmuneLevelCalculator
	{
	public:
		static StaggerLevel GetTotalImmuneLevel(RE::Actor* a_target);
		static bool HasActiveEffectWithKeyword(RE::MagicTarget* a_target, RE::BGSKeyword* a_keyword);

	private:
		ImmuneLevelCalculator() = delete;

		~ImmuneLevelCalculator() = delete;

		static StaggerLevel GetAnimImmuneLevel(RE::Actor* a_target);
		static StaggerLevel GetAnimImmuneLevel(RE::hkbClipGenerator* a_clip);

		static inline std::map<std::string, StaggerLevel> ImmuneKeywordMap = {
			{ "MaxsuPoise_ImmuneSmall", StaggerLevel::kSmall },
			{ "MaxsuPoise_ImmuneMedium", StaggerLevel::kMedium },
			{ "MaxsuPoise_ImmuneLarge", StaggerLevel::kLarge },
			{ "MaxsuPoise_ImmuneLargest", StaggerLevel::kLargest }
		};
	};
}

namespace RE
{
	class hkbNode;

	struct hkbNodeInfo
	{
		void* unk00;            //00
		int64_t unk08;          //08
		int64_t unk10;          //10
		void* unk18;            //18
		char unk20[48];         //20
		hkbNode* nodeTemplate;  //50
		hkbNode* nodeClone;     //58
		hkbNode* behavior;      //60
		int64_t unk68;          //68
		int64_t unk70;          //70
		int64_t unk78;          //78
		int64_t unk80;          //80
		bool unk88;             //88
	};
	static_assert(sizeof(hkbNodeInfo) == 0x90);

	class hkCustomAttributes;

	/// Reflection information for any reflected type.
	class hkClass
	{
	public:
		enum FlagValues
		{
			kFlagsNone = 0,
			kFlagsNotSerializable = 1
		};
		using Flags = stl::enumeration<FlagValues, std::uint32_t>;

		const char* name;                            // 00
		const hkClass* parent;                       // 08
		std::int32_t objectSize;                     // 10
		std::int32_t numImplementedInterfaces;       // 14
		const class hkClassEnum* declaredEnums;      // 18
		std::int32_t numDeclaredEnums;               // 20
		std::uint32_t pad24;                         // 24
		const class hkClassMember* declaredMembers;  // 28
		std::int32_t numDeclaredMembers;             // 30
		std::uint32_t pad34;                         // 34
		const void* defaults;                        // 38
		const hkCustomAttributes* attributes;        // 40
		Flags flags;                                 // 48
		std::int32_t describedVersion;               // 4C
	};
	static_assert(sizeof(hkClass) == 0x50);

	inline bool IsStaggering(RE::Actor* actor)
	{
		if (!actor)
			return false;

		auto result = false;
		if (actor->GetGraphVariableBool("IsStaggering", result) && result)
			return result;

		return static_cast<bool>(actor->AsActorState()->actorState2.staggered);
	}
}