#pragma once

namespace Plugin
{
	namespace Patches
	{
		namespace GameScript
		{
			namespace Actor
			{
				class ChangeHeadPart
				{
				public:
					static void Apply() {
						static REL::Relocation<std::uintptr_t> target{ REL::ID { 1428321, 2251577 } };

						MH_CreateHook(
							reinterpret_cast<void*>(target.address()),
							reinterpret_cast<void*>(&Thunk),
							reinterpret_cast<void**>(&orig)
						);

						REX::INFO("Hook applied at {:016X}", target.address());
					}
				private:
					static void Thunk(RE::BSScript::IVirtualMachine& a_vm, unsigned int a_stackId, RE::Actor* a_actor, RE::BGSHeadPart* a_headpart, bool a_bRemovePart, bool a_bRemoveExtraParts) {
						if (a_headpart)
						{
							auto* npc = a_actor->GetNPC()->GetRootFaceNPC();

							// apply/remove head parts
							if (a_bRemovePart) {
								npc->RemoveHeadPart(a_headpart, a_bRemoveExtraParts);
							}
							else {
								npc->AddUniqueHeadType(a_headpart);
							}

							auto* playerCharacter = RE::PlayerCharacter::GetSingleton();
							if (a_actor != playerCharacter) {
								npc->AddChange(RE::CHANGE_TYPES::kNPCFace);
							}

							a_actor->Reset3D(false, static_cast<std::int32_t>(RE::RESET_3D_FLAGS::kHead), true, 0);
						}
						else
						{
							a_vm.PostError(
								"Cannot ChangeHeadPart with a None item",
								a_stackId,
								RE::BSScript::ErrorLogger::Severity::kError
							);
						}
					}

					inline static REL::Relocation <decltype(&Thunk)> orig;
				};
			}
		}
	}
}