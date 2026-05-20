-- premake5.lua
workspace "sead-examples"
    platforms {
        "SDL_x86",
        "Win_x86",

        "SDL_x86_64",
        "Win_x86_64",

        "SDL_ARM32",
        "Win_ARM32",

        "SDL_ARM64",
        "Win_ARM64",
    }

    configurations {
        "Debug",
        "Develop",
        "Release",
    }

    startproject "sead-examples"

    toolset "clang"
    stl "libc++"

    -- TODO: Remove
    buildoptions {
    -- suppressed errors
        "-Wno-invalid-offsetof",
        "-Wno-undefined-var-template",
        "-Wno-missing-braces",
    -- keep, but as warnings
        "-Wno-error=switch",
        "-Wno-error=unused-private-field",
        "-Wno-error=unused-const-variable",
        "-Wno-error=logical-op-parentheses",
        "-Wno-error=bitwise-op-parentheses",
        "-Wno-error=delete-non-abstract-non-virtual-dtor",
    }

    filter "platforms:*_x86"
        architecture "x86"
        stl "gnu"

    filter "platforms:*_x86_64"
        architecture "x86_64"
        vectorextensions "AVX2"

    filter "platforms:*_ARM32"
        architecture "ARM"

    filter "platforms:*_ARM64"
        architecture "ARM64"

project "sead-examples"
    language "C++"
    cppdialect "C++20"

    multiprocessorcompile "on"
    staticruntime "on"
    exceptionhandling "off"
    rtti "off"
    fatalwarnings { "all" }

    targetdir "bin/%{prj.name}-%{cfg.platform}-%{cfg.buildcfg}/out"
    objdir "bin/%{prj.name}-%{cfg.platform}-%{cfg.buildcfg}/int"
    debugdir "./workdir"

    includedirs {
        "libs/sead/include",

        "include",
    }

    files {
        "src/**.cpp",
    }

    links {
        "sead",
    }

    filter "system:windows"
        systemversion "latest"

    filter "system:linux"
        systemversion "latest"

    filter "system:macosx"
        systemversion "11.0"

    filter "platforms:SDL_*"
        defines {
            "SEAD_PLATFORM_SDL",
            "SEAD_USE_GL",
        }

        includedirs {
            "libs/sead/libs/glad/include",
            "libs/sead/libs/SDL3/repo/include",
        }

        links {
            -- "glad",
            "SDL3",
        }

        libdirs {
            "libs/sead/libs/SDL3/lib",
        }

    filter "platforms:Win_*"
        defines {
            "SEAD_PLATFORM_WINDOWS",
            "SEAD_USE_GL",
        }

        includedirs {
            "libs/sead/libs/glad/include",
        }

        links {
            -- "glad",
        }

    filter "configurations:Debug"
        kind "ConsoleApp"
        defines { "SEAD_TARGET_DEBUG" }
        runtime "debug"
        optimize "debug"
        symbols "on"
        linktimeoptimization "off"

    filter "configurations:Develop"
        kind "ConsoleApp"
        defines { "SEAD_TARGET_DEBUG" } -- TODO: Use SEAD_TARGET_DEVELOP
        runtime "release"
        optimize "speed"
        symbols "on"
        linktimeoptimization "off"

    filter "configurations:Release"
        kind "WindowedApp"
        defines { "SEAD_TARGET_RELEASE", "NDEBUG" }
        runtime "release"
        optimize "speed"
        symbols "off"
        linktimeoptimization "on"

    filter { "system:windows", "configurations:Release" }
        entrypoint "mainCRTStartup"

group "Dependencies"
    include "libs/sead"
group ""
