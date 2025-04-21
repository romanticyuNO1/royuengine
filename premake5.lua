workspace "royuengine"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

	filter "system:windows"
        buildoptions { "/utf-8" }

outputdir = "%{cfg.buildcfg}_%{cfg.system}_%{cfg.architecture}"

includeDir = {}
includeDir["glfw"] = "royuengine/vendor/glfw/include"
includeDir["glad"] = "royuengine/vendor/glad/include"
includeDir["imgui"] = "royuengine/vendor/imgui"

include "royuengine/vendor/glfw"
include "royuengine/vendor/glad"
include "royuengine/vendor/imgui"

project "royuengine" 
	location "royuengine"
	kind "SharedLib"
	language "c++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin_int/" .. outputdir .. "/%{prj.name}")

	pchheader "rypch.h"
	pchsource "royuengine/src/rypch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"royuengine/vendor/spdlog/include",
		"royuengine/src",
		"%{includeDir.glfw}",
		"%{includeDir.glad}",
		"%{includeDir.imgui}"
	}

	links
	{
		"glfw",
		"opengl32.lib",
		"glad",
		"imgui",
		--"ucrtd.lib",   
		--"msvcrt.lib", 
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On" 
		systemversion "latest"

		defines
		{
			"RY_PLAYFROM_WINDOWS",
			"RY_BUILD_DLL",
			"GLFW_INCLUDE_NONE",
		}

		postbuildcommands {
			"{MKDIR} \"../bin/" .. outputdir .. "/sandbox\"",
			"{COPY} %{cfg.buildtarget.relpath} \"../bin/" .. outputdir .. "/sandbox\""
}

		filter "configurations:Debug"
			defines "RY_DEBUG"
			buildoptions "/MDd"
			symbols "On"

		filter "configurations:Release"
			defines "RY_RELEASE"
			buildoptions "/MD"
			optimize "On"

		filter "configurations:Dist"
			defines "RY_DIST"
			buildoptions "/MD"
			optimize "On"


project "sandbox"
	location "sandbox"
	kind "ConsoleApp"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin_int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"royuengine/src",
		"royuengine/vendor/spdlog/include"
	}

	links
	{
		"royuengine",
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"RY_PLAYFROM_WINDOWS",
		}

		filter "configurations:Debug"
			defines "RY_DEBUG"
			buildoptions "/MDd"
			symbols "On"

		filter "configurations:Release"
			defines "RY_RELEASE"
			buildoptions "/MD"
			optimize "On"

		filter "configurations:Dist"
			defines "RY_DIST"
			buildoptions "/MD"
			optimize "On"