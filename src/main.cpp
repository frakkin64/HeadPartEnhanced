#include <MinHook.h>
#include "Settings.h"
#include "Patches/GameScript/Actor/ChangeHeadPart.h"

F4SE_PLUGIN_QUERY(const F4SE::QueryInterface* a_f4se, F4SE::PluginInfo* a_info)
{
	if (const auto data = F4SE::PluginVersionData::GetSingleton()) {
		a_info->infoVersion = F4SE::PluginInfo::kVersion;
		a_info->name = data->GetPluginName().data();
		a_info->version = data->GetPluginVersion().pack();
	}

	const auto ver = a_f4se->RuntimeVersion();
	if (ver < REL::Version(F4SE::RUNTIME_1_10_163)) {
		return false;
	}

	return true;
}

F4SE_PLUGIN_LOAD(const F4SE::LoadInterface* a_f4se)
{
	const auto config = REX::TOML::SettingStore::GetSingleton();
	config->Init("Data/F4SE/Plugins/HeadPartEnhanced.toml", "Data/F4SE/Plugins/HeadPartEnhanced_custom.toml");
	config->Load();

	const auto initInfo = F4SE::InitInfo{
		.logLevel = REX::ELogLevel { Plugin::Settings::LogLevel.GetValue() }
	};

	F4SE::Init(a_f4se, initInfo);

	// Apply hooks
	MH_Initialize();
	Plugin::Patches::GameScript::Actor::ChangeHeadPart::Apply();
	MH_EnableHook(MH_ALL_HOOKS);

	return true;
}
