workspace "MDL-Validator"
	configurations { "Debug", "Release" }
	startproject "mdl-validator"
	includedirs { "include" }
	filter { "system:Windows" }
		platforms { "Win64" }
    filter { "system:Linux" }
        platforms { "Linux64" }
	filter { "action:vs2019" }
		location "build/vs2019"
    filter { "action:codelite" }
		toolset "gcc"
	filter { "toolset:gcc" }
		links { "stdc++fs" }

include "source/mdl-validator/mdl-validator.lua"