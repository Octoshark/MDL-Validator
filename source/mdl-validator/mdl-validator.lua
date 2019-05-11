project "mdl-validator"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	location "./"
	targetname "mdl-validator"
	
	vpaths {
		[ "Header Files" ] = { "**.hpp" },
		[ "Source Files" ] = { "**.cpp" }
	}
	
	files {
			"main.cpp"
		}
	
	filter { "action:vs2019" }
		location "../../build/vs2019"

	filter { "configurations:Debug"	}
		symbols "On"
		
	filter { "configurations:Release" }
		optimize "On"
	
	filter { "platforms:Win64", "configurations:Debug" }
		targetdir "%{cfg.location}/%{prj.name}/debug_win64"
		objdir "%{cfg.location}/%{prj.name}/debug_win64/obj"
		architecture "x64"

	filter { "platforms:Win64", "configurations:Release" }
		targetdir "%{cfg.location}/%{prj.name}/release_win64"
		objdir "%{cfg.location}/%{prj.name}/release_win64/obj"
		architecture "x64"

	filter { "system:Windows" }
		defines { "_CRT_SECURE_NO_WARNINGS", "_SCL_SECURE_NO_WARNINGS" }