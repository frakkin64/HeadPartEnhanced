-- include subprojects
includes("lib/commonlibf4")

-- set project constants
set_project("HeadPartEnhanced")
set_version("1.1.0")
set_license("GPL-3.0")
set_languages("c++23")
set_warnings("allextra")

-- add common rules
add_rules("mode.debug", "mode.releasedbg")
add_rules("plugin.vsxmake.autoupdate")

-- config options
set_config("commonlib_toml", true)

-- packages
add_requires("minhook")

-- define targets
target("HeadPartEnhanced")
    add_rules("commonlibf4.plugin", {
        name = "HeadPartEnhanced",
        author = "frakkin64",
        description = "F4SE plugin using CommonLibF4"
    })

    -- add src files
    add_files("src/**.cpp")
    add_headerfiles("src/**.h", "include/**.h")
    add_includedirs("src", "include")
    set_pcxxheader("src/pch.h")

    add_packages("minhook")
