if os.host() == "linux" then
   require "codeblocks"
end


workspace "MiniECS"

	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
	}

	outputdir = "%{cfg.architecture}-%{cfg.system}-%{cfg.buildcfg}"
	targetoutputdir = "_bin/" .. outputdir
	objectoutputdir = "_obj/" .. outputdir
	runnableoutputdir = "_exe/" .. outputdir

    projectengine = "Engine"
    projectgame = "Game"

	project ("" .. projectengine)
		location ("" .. projectengine)
		targetname ("" .. projectengine)
		kind "SharedLib"
		language "C++"

        cppdialect "C++17"
        staticruntime "Off"
        systemversion "latest"

		targetdir (targetoutputdir .. "/%{prj.name}")
		objdir (objectoutputdir .. "/%{prj.name}")

        filter "configurations:*"
			prebuildcommands
            {
                "{MKDIR} %{wks.location}/" .. runnableoutputdir,
            }

            postbuildcommands
            {
                ("{COPY} %{cfg.buildtarget.relpath} ../" .. runnableoutputdir),
            }

            files
            {
                "%{prj.name}/Source/**.h",
                "%{prj.name}/Source/**.cpp",
				"%{prj.name}/Include/**.h",
                "%{prj.name}/Include/**.cpp",
            }

		filter "configurations:Debug"
			defines "BUILD_DEBUG"

		filter "configurations:Release"
			defines "BUILD_RELEASE"

-- platforms

		filter "system:windows"
			defines
			{
				"PLATFORM_WINDOWS",
				"BUILD_DLL",
			}

        filter "system:macosx"
            defines
            {
                "PLATFORM_MAC",
            }

            xcodebuildsettings
            {
                ["INSTALL_PATH"] = "@executable_path";
            }

		filter "system:linux"

			defines
			{
				"PLATFORM_LINUX",
			}

	project "Game"
		location "Game"
		kind "ConsoleApp"
		language "C++"

        cppdialect "C++17"
        staticruntime "On"
        systemversion "latest"

		targetdir (targetoutputdir .. "/%{prj.name}")
		objdir (objectoutputdir .. "/%{prj.name}")

        filter "configurations:*"
            prebuildcommands
            {
				"{MKDIR} %{wks.location}/" .. runnableoutputdir,
            }

            postbuildcommands
            {
				("{COPY} %{cfg.buildtarget.relpath} ../" .. runnableoutputdir),
            }

            files
            {
                "%{prj.name}/Source/**.h",
                "%{prj.name}/Source/**.cpp",
            }

		filter "configurations:Debug"
			defines "BUILD_DEBUG"

		filter "configurations:Release"
			defines "BUILD_RELEASE"

-- platforms

		filter "system:*"
            includedirs
            {
				"%{wks.location}/" .. projectengine .. "/Include/",
            }

            links
            {
                projectengine,
            }

		filter "system:windows"
			defines
			{
				"PLATFORM_WINDOWS",
				"WIN32_LEAN_AND_MEAN",
				"WIN64_LEAN_AND_MEAN",
				"VC_EXTRALEAN",
			}

            libdirs
            {
				targetoutputdir .. "/" .. projectengine,
            }

        filter "system:macosx"
            defines
            {
                "PLATFORM_MAC",
            }

            xcodebuildsettings
            {
                ["INSTALL_PATH"] = "@executable_path";
            }

		filter "system:linux"

			defines
			{
				"PLATFORM_LINUX",
			}
