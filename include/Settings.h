#pragma once

namespace Plugin
{
	namespace Settings
	{
		REX::TOML::I32 LogLevel{ "General"sv, "iLogLevel"sv, static_cast<std::int32_t>(REX::ELogLevel::Info) };
	}
}