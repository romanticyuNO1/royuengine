workspace "Royu"
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

project "royuengine" 
	location "royuengine"
	kind "SharedLib"
	language "c++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}


	includedirs
	{
		"%{prj.name}/vendor/spdlog/include"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "10.0.22621.0"

		defines
		{
			"RY_PLAYFROM_WINDOWS",
			"RY_BUILD_DLL"
		}

		postbuildcommands {
			"{MKDIR} \"../bin/" .. outputdir .. "/Sandbox\"",
			"{COPY} %{cfg.buildtarget.relpath} \"../bin/" .. outputdir .. "/Sandbox\""
}

		filter "configurations:Debug"
			defines "RY_DEBUG"
			symbols "On"

		filter "configurations:Release"
			defines "RY_RELEASE"
			optimize "On"

		filter "configurations:Dist"
			defines "RY_DIST"
			optimize "On"


project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"Royuyu/vendor/spdlog/include",
		"Royuyu/src"
	}

	links
	{
		"Royuyu"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "10.0.22621.0"

		defines
		{
			"RY_PLAYFROM_WINDOWS"
		}

		filter "configurations:Debug"
			defines "RY_DEBUG"
			symbols "On"

		filter "configurations:Release"
			defines "RY_RELEASE"
			optimize "On"

		filter "configurations:Dist"
			defines "RY_DIST"
			optimize "On"