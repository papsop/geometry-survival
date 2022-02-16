workspace "Dungeons & Geometry"
    configurations { "Debug", "Release" }
    platforms { "Win64" }
    startproject "Game"

    filter "platforms:Win64"
        architecture "x64"

local bindir = "./bin/" .. "%{cfg.platform}" .. "/" .. "%{cfg.buildcfg}"
local intdir = "./bin-int/" .. "%{cfg.platform}" .. "/" .. "%{cfg.buildcfg}"

-- Global settings
language "C++"
cppdialect "C++17"
systemversion "latest"
symbols "On"

targetdir(bindir)
objdir(intdir)

libdirs { "./lib" }
includedirs { "./include", "./src" }

filter "configurations:Debug"
    links { "sfml-graphics-d.lib", "sfml-window-d.lib", "sfml-system-d.lib" }

filter "configurations:Release"
    links { "sfml-graphics.lib", "sfml-window.lib", "sfml-system.lib" }

    
------------------
-- GAME
------------------

project "Game"
    kind "ConsoleApp"
    location "./src/Game"
    includedirs { "./src/Engine" }

    links { "Engine" }
    files {
        "./src/Game/**.cpp",
        "./src/Game/**.h"
    }

------------------
-- ENGINE
------------------

project "Engine"
    kind "StaticLib"
    location "src/Engine"

    files {
        "./src/Engine/**.cpp",
        "./src/Engine/**.h",
    }