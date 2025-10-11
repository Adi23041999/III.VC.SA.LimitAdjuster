workspace "OpenLimitAdjuster"
	configurations { "Release", "Debug", }
	platforms { "GTA3", "GTAVC", "GTASA" }
    location( "build" )
	startproject "OpenLimitAdjuster"
	files {
		"src/**",
        "doc/**",
	}

project "OpenLimitAdjuster"
	kind "SharedLib"
	language "C++"
	targetextension ".asi"
	characterset ("MBCS")
	cppdialect "C++latest"
	linkoptions "/SAFESEH:NO"
	buildoptions { "-std:c++latest", "/permissive" }
	defines { "_CRT_SECURE_NO_WARNINGS", "_CRT_NON_CONFORMING_SWPRINTFS", "_USE_MATH_DEFINES", "RW", "_SILENCE_CXX23_ALIGNED_STORAGE_DEPRECATION_WARNING" }
	--disablewarnings { "4244", "4800", "4305", "4073", "4838", "4996", "4221", "4430", "26812", "26495", "6031" }
    flags { "NoPCH" }
    excludes { 
		"sample.cpp",
		"game_iii/CLinkList.h",
		"game_vc/CLinkList.h",
		"game_sa/CLinkList.h",
	}

    defines { "rsc_CompanyName=\"LimitAdjuster\"" }
    defines { "rsc_LegalCopyright=\"MIT License\""} 
    defines { "rsc_FileVersion=\"1.0.0.0\"", "rsc_ProductVersion=\"1.0.0.0\"" }
    defines { "rsc_InternalName=\"%{prj.name}\"", "rsc_ProductName=\"%{prj.name}\"", "rsc_OriginalFilename=\"%{prj.name}.dll\"" }
    defines { "rsc_FileDescription=\"This is a open source limit adjuster for Grand Theft Auto III, Vice City and San Andreas\"" }
    defines { "rsc_UpdateUrl=\"https://github.com/ThirteenAG/III.VC.SA.LimitAdjuster\"" }

    defines { "PLUGIN_SGV_10EN" }

    includedirs {
        "src/**.*",
		"$(PLUGIN_SDK_DIR)/shared/",
		"$(PLUGIN_SDK_DIR)/shared/game/",
		"$(PLUGIN_SDK_DIR)/injector/",
	}

    flags {
        staticruntime "on",
        "NoImportLib",
        rtti ("Off"),
        "NoBufferSecurityCheck"
    }

    defines {
        "INJECTOR_GVM_HAS_TRANSLATOR",
        'INJECTOR_GVM_PLUGIN_NAME=\"Open Limit Adjuster\"'    -- (additional quotes needed for gmake)
    }

    defines {
        "_CRT_SECURE_NO_WARNINGS",
        "_SCL_SECURE_NO_WARNINGS"
    }

    includedirs {
        "src",
        "src/shared",
        --"src/shared/cpatch",
        "src/shared/structs",
    }

	libdirs { "$(PLUGIN_SDK_DIR)/output/lib" }

    largeaddressaware "on"

	filter "configurations:Debug"
		defines { "DEBUG" }
		symbols "on"

	filter "configurations:Release"
		defines { "NDEBUG" }
		symbols "on"
		optimize "speed"
		linktimeoptimization "on"
		inlining "auto"
		runtime "Release"

	filter { "configurations:Debug", "platforms:GTA3" }
		links { "plugin_iii_d" }

	filter { "configurations:Release", "platforms:GTA3" }
		links { "plugin_iii" }

	filter { "configurations:Debug", "platforms:GTAVC" }
		links { "plugin_vc_d" }

	filter { "configurations:Release", "platforms:GTAVC" }
		links { "plugin_vc" }

	filter { "configurations:Debug", "platforms:GTASA" }
		links { "plugin_sa_d" }

	filter { "configurations:Release", "platforms:GTASA" }
		links { "plugin_sa" }

	filter { "platforms:GTA3" }
		targetdir "output/bin/GTA3/"
		objdir ("output/bin/GTA3/GTA3/")
		targetname "III.OpenLimitAdjuster"
		defines { "III", "GTA3" }
		debugdir "$(GTA_III_DIR)"
		debugcommand "$(GTA_III_DIR)/gta3.exe"
		--debugcommand "D:/Projects/3D/GTA/Liberty City Countryside/GTA 3 UL/gta3 1.0.exe"
		--debugdir "D:/Projects/3D/GTA/Liberty City Countryside/GTA 3 UL"
		includedirs {
			"$(PLUGIN_SDK_DIR)/plugin_III/",
			"$(PLUGIN_SDK_DIR)/plugin_III/game_III/",
			"$(PLUGIN_SDK_DIR)/plugin_III/game_III/rw",
		}
		postbuildcommands {
		"copy /y \"$(TargetPath)\" \"$(GTA_III_DIR)\\scripts\\III.OpenLimitAdjuster.asi\"",
		"copy /y \"$(TargetPath)\" \"D:\\Projects\\3D\\GTA\\Liberty City Countryside\\GTA 3 UL\\III.OpenLimitAdjuster.asi\"",
		}

	filter { "platforms:GTAVC" }
		targetdir "output/bin/GTAVC/"
		objdir ("output/bin/GTAVC/GTAVC/")
		targetname "VC.OpenLimitAdjuster"
		defines { "VC", "GTAVC" }
		debugdir "$(GTA_VC_DIR)"
		debugcommand "$(GTA_VC_DIR)/gtaVC.exe"
		includedirs {
        	"$(PLUGIN_SDK_DIR)/plugin_VC/",
			"$(PLUGIN_SDK_DIR)/plugin_VC/game_VC/",
			"$(PLUGIN_SDK_DIR)/plugin_VC/game_VC/rw",
		}
		postbuildcommands {
		"copy /y \"$(TargetPath)\" \"$(GTA_VC_DIR)\\scripts\\VC.OpenLimitAdjuster.asi\"",
		}

	filter { "platforms:GTASA" }
		targetdir "output/bin/GTASA/"
		objdir ("output/bin/GTASA/GTASA/")
		targetname "SA.OpenLimitAdjuster"
		defines { "DEBUG", "SA", "GTASA" }
		debugdir "$(GTA_SA_DIR)"
		debugcommand "$(GTA_SA_DIR)/gtasa.exe"
		includedirs {
        	"$(PLUGIN_SDK_DIR)/plugin_SA/",
			"$(PLUGIN_SDK_DIR)/plugin_SA/game_SA/",
			"$(PLUGIN_SDK_DIR)/plugin_SA/game_SA/rw",
		}
		postbuildcommands {
		"copy /y \"$(TargetPath)\" \"$(GTA_SA_DIR)\\scripts\\SA.OpenLimitAdjuster.asi\"",
		}	
    
--    configuration "vs*"
--        buildoptions { "/arch:IA32" }           -- disable the use of SSE/SSE2 instructions
