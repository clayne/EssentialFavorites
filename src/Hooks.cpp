#include "Hooks.h"
#include "Settings.h"

namespace EssentialFavorites
{
	struct IsQuestObject
	{
		static bool thunk(RE::InventoryEntryData* a_data)
		{
			auto result = func(a_data);
			if (!result && a_data) {
				result = a_data->IsFavorited();
			}
			return result;
		}
		static inline REL::Relocation<decltype(thunk)> func;
	};

	namespace Alchemy
	{
		void Patch()
		{
			REL::Relocation<std::uintptr_t> func{ RELOCATION_ID(50453, 51358), 0x106 };
			stl::write_thunk_call<IsQuestObject>(func.address());

			logger::info("patched alchemy");
		}
	}

	namespace Barter
	{
		void Patch()
		{
			REL::Relocation<std::uintptr_t> func{ RELOCATION_ID(50061, 51001), OFFSET(0x25, 0x2B) };
			stl::write_thunk_call<IsQuestObject>(func.address());

			logger::info("patched bartering");
		}
	}

	namespace Crafting
	{
		void Patch()
		{
			REL::Relocation<std::uintptr_t> func{ RELOCATION_ID(15811, 16049), 0x07 };
			stl::write_thunk_call<IsQuestObject>(func.address());

			logger::info("patched crafting");
		}
	}

	namespace Disarm
	{
		void Patch()
		{
			REL::Relocation<std::uintptr_t> func{ RELOCATION_ID(36523, 37523), OFFSET(0x71, 0x70) };
			stl::write_thunk_call<IsQuestObject>(func.address());

			logger::info("patched disarming");
		}
	}

	namespace Dropped
	{
		void Patch()
		{
			REL::Relocation<std::uintptr_t> func{ RELOCATION_ID(50978, 51857), OFFSET(0x38, 0x34) };
			stl::write_thunk_call<IsQuestObject>(func.address());

			logger::info("patched drop object");
		}
	}

	namespace Enchanting
	{
		struct IsQuestObject
		{
			static bool thunk(RE::InventoryEntryData* a_data)
			{
				auto result = func(a_data);
				if (!result && a_data) {
					result = a_data->IsEnchanted() && a_data->IsFavorited();
				}
				return result;
			}
			static inline REL::Relocation<decltype(thunk)> func;
		};

	    void Patch()
		{
			REL::Relocation<std::uintptr_t> func{ RELOCATION_ID(50454, 51359), OFFSET(0x133, 0x140) };
			stl::write_thunk_call<Enchanting::IsQuestObject>(func.address());

			logger::info("patched enchanting");
		}
	}

	namespace Gifting
	{
		void Patch()
		{
			REL::Relocation<std::uintptr_t> func{ RELOCATION_ID(50688, 51583), OFFSET(0x1C, 0xC3) };
			stl::write_thunk_call<IsQuestObject>(func.address());

			logger::info("patched gifting");
		}
	}

	void Install()
	{
		const auto settings = Settings::GetSingleton();

		if (settings->noAlchemy) {
			Alchemy::Patch();
		}
		if (settings->noBarter) {
			Barter::Patch();
		}
		if (settings->noCrafting) {
			Crafting::Patch();
		}
		if (settings->noDisarmed) {
			Disarm::Patch();
		}
		if (settings->noDisenchanting) {
			Enchanting::Patch();
		}
		if (settings->noDrop) {
			Dropped::Patch();
		}
		if (settings->noGifting) {
			Gifting::Patch();
		}
	}
}
