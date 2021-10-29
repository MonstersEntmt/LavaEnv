require("Premake/cleanAction")
require("Premake/formatTidyAction")

workspace("Lava")
	configurations({ "Debug", "Release", "Dist" })
	platforms({ "x86", "x64" })
	
	cppdialect("C++20")
	rtti("Off")
	exceptionhandling("On")
	flags("MultiProcessorCompile")
	runclangformat(false)
	runclangtidy(false)
	
	filter("configurations:Debug")
		defines({ "LAVA_CONFIG=LAVA_CONFIG_DEBUG" })
		optimize("Off")
		symbols("On")
		
	filter("configurations:Release")
		defines({ "LAVA_CONFIG=LAVA_CONFIG_RELEASE" })
		optimize("Full")
		symbols("On")
		
	filter("configurations:Dist")
		defines({ "LAVA_CONFIG=LAVA_CONFIG_DIST" })
		optimize("Full")
		symbols("Off")
		
	filter("system:windows")
		defines({ "LAVA_SYSTEM=LAVA_SYSTEM_WINDOWS" })
		
	filter("system:macosx")
		defines({ "LAVA_SYSTEM=LAVA_SYSTEM_MACOSX" })
		
	filter("system:linux")
		defines({ "LAVA_SYSTEM=LAVA_SYSTEM_LINUX" })
	
	filter("toolset:msc")
		defines({ "LAVA_TOOLSET=LAVA_TOOLSET_MSVC" })
	
	filter("toolset:clang")
		defines({ "LAVA_TOOLSET=LAVA_TOOLSET_CLANG" })
	
	filter("toolset:gcc")
		defines({ "LAVA_TOOLSET=LAVA_TOOLSET_GCC" })
	
	filter("platforms:x86")
		defines({ "LAVA_PLATFORM=LAVA_PLATFORM_X86" })
	
	filter("platforms:x64")
		defines({ "LAVA_PLATFORM=LAVA_PLATFORM_AMD64" })
	
	filter({})
	
	startproject("LavaTest")
	
	project("LavaEnv")
		kind("StaticLib")
		location("%{wks.location}/LavaEnv/")
		targetdir("%{wks.location}/Bin/%{cfg.system}-%{cfg.buildcfg}-%{cfg.platform}/")
		objdir("%{wks.location}Bin/Int-%{cfg.system}-%{cfg.buildcfg}-%{cfg.platform}/%{prj.name}")
		
		includedirs({
			"%{prj.location}/Source/",
			"%{prj.location}/Include/"
		})
		
		files({ "%{prj.location}/**" })
		
		filter("files:**.h")
			runclangformat(true)
		
		filter("files:**.cpp")
			runclangformat(true)
			runclangtidy(true)
		
		filter({})
	
	project("LavaTest")
		kind("ConsoleApp")
		location("%{wks.location}/LavaTest/")
		targetdir("%{wks.location}/Bin/%{cfg.system}-%{cfg.buildcfg}-%{cfg.platform}/")
		objdir("%{wks.location}Bin/Int-%{cfg.system}-%{cfg.buildcfg}-%{cfg.platform}/%{prj.name}")
		
		links({ "LavaEnv" })
		sysincludedirs({ "%{wks.location}/LavaEnv/Include/" })
		
		includedirs({ "%{prj.location}/Source/" })
		
		files({ "%{prj.location}/**" })
		
		filter("files:**.h")
			runclangformat(true)
		
		filter("files:**.cpp")
			runclangformat(true)
			runclangtidy(true)
		
		filter({})
