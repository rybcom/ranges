
solution_name = "ranges"
solution_dir ="%{wks.location}"  
platform_specifier = "%{cfg.buildcfg}_%{cfg.platform}"

workspace (solution_name)
	
	architecture "x64"
	platforms "win64"
	startproject "range_test"


	targetdir ("intermediate/bin/" .. platform_specifier .. "/%{prj.name}")
	objdir ("intermediate/obj/" .. platform_specifier .. "/%{prj.name}")

	filter "system:windows"
			systemversion "latest"


	includedirs
	{
		"src/%{prj.name}/public",
		"src/%{prj.name}/private",
	}

	configurations 
	{	
		"debug" ,
		"release",
		"profiler" 
	}
	
	files 
	{
		"src/%{prj.name}/**.cpp",
		"src/%{prj.name}/**.h",
		"src/%{prj.name}/**.inl",
	}

	filter "configurations:debug"
  		optimize "Off"
  		defines {
  				"CONFIGURATION_DEBUG=true",
  				"CONFIGURATION_PROFILER=false",
  				"CONFIGURATION_RELEASE=false",
  				}

	filter "configurations:profiler"
  		optimize "Full"
  		defines {
  				"CONFIGURATION_DEBUG=false",
  				"CONFIGURATION_PROFILER=true",
  				"CONFIGURATION_RELEASE=false",
  				}
  		
	filter "configurations:release"
  		optimize "Full"
  		defines {
  				"CONFIGURATION_DEBUG=false",
  				"CONFIGURATION_PROFILER=false",
  				"CONFIGURATION_RELEASE=true",
  				}



		----------------------------------------------
	  	--										    --
	  	--					range_test 	 			--
	  	--											--
	  	----------------------------------------------

		project "range_test"
			location "intermediate/project_files"
			kind "ConsoleApp"
			language "C++"
			cppdialect "C++17"
		
			files 
			{
				"src/%{prj.name}/**.h",
				"src/%{prj.name}/**.cpp",
			}

			includedirs
			{
				"tools/ranges",
				"tools/catch2",
			}

