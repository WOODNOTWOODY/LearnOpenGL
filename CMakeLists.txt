cmake_minimum_required(VERSION 3.2.0)
set(CMAKE_ALLOW_LOOSE_LOOP_CONSTRUCTS TRUE)
set_property(GLOBAL PROPERTY USE_FOLDERS TRUE)

message(STATUS "#####################################################")
message(STATUS "#Blade Build System")
message(STATUS "#####################################################")
message(STATUS "Configuring build system...")
message(STAUTS "CMake version: ${CMAKE_VERSION}")

set(BLADE_PLATFORM_WIN32 FALSE)

project(Blade)

if(MSVC)
	if(WIN32)
		set(BLADE_PLATFORM_WIN32 TRUE)
		message(STATUS "Platform: Win32")

		# compiler building setting
		# Flags used by the compiler during all build types.
		set(CMAKE_CXX_FLAGS "/DWIN32 /D_WINDOWS /W4 /wd4819 /wd4100 /wd4201 /wd4127 /Zm256 /EHsc /GR- /fp:fast")
		# Flags used by the compiler during debug builds.
		set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} /D_DEBUG /MDd /Zi /Ob0 /Od /RTC1 /Oi")
		# Flags used by the compiler during release minsize builds.
		set(CMAKE_CXX_FLAGS_MINSIZEREL "${CMAKE_CXX_FLAGS} /MD /O1 /Ob1 /DNDEBUG")
		# Flags used by the compiler during release builds (/MD /Ob1 /Oi /Ot /Oy /Gs will produce slightly less optimized but smaller files).
		set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} /MD /O2 /Ob2 /DNDEBUG")
		# Flags used by the compiler during Release with Debug Info builds.
		set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS} /MD /Zi /O2 /Ob1 /DNDEBUG")
		# Flags used by the compiler during all build types.
		set(CMAKE_C_FLAGS "/DWIN32 /D_WINDOWS /W3 /wd4819 /Zm256")
		# Flags used by the compiler during debug builds.
		set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS} /D_DEBUG /MDd /Zi /Ob0 /Od /RTC1")
		# Flags used by the compiler during release minsize builds.
		set(CMAKE_C_FLAGS_MINSIZEREL "${CMAKE_C_FLAGS} /MD /O1 /Ob1 /DNDEBUG")
		# Flags used by the compiler during release builds (/MD /Ob1 /Oi /Ot /Oy /Gs will produce slightly less optimized but smaller files).
		set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS} /MD /O2 /Ob2 /DNDEBUG")
		# Flags used by the compiler during Release with Debug Info builds.
		set(CMAKE_C_FLAGS_RELWITHDEBINFO "${CMAKE_C_FLAGS} /MD /Zi /O2 /Ob1 /DNDEBUG")
			
		# Enable intrinsics on MSVC in debug mode
		if (CMAKE_CL_64)
			# Visual Studio bails out on debug builds in 64bit mode unless
			# this flag is set...
			set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /bigobj")
			set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS_RELWITHDEBINFO} /bigobj")
		endif ()
	endif()
endif()

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

macro(use_precompiled_header PrecompiledHeader PrecompiledSource Sources)
	if (MSVC AND NOT NMAKE)
		get_filename_component(PRECMP_HEADER ${PrecompiledHeader} NAME)

		foreach(src_file ${${Sources}})
			set_source_files_properties(${src_file} PPROPERTIES COMPILE_FLAGS /Yu"${PRECMP_HEADER}")
		endforeach(src_file)
		set_source_files_properties(${PrecompiledSource} PPROPERTIES COMPILE_FLAGS /Yc"${PRECMP_HEADER}")
	endif ()
endmacro(use_precompiled_header)

set(BLADE_ROOT_PATH "${PROJECT_SOURCE_DIR}")
set(BLADE_BUILD_PATH "${PROJECT_BINARY_DIR}")
set(BLADE_PATH "${BLADE_ROOT_PATH}/blade")
set(BLADE_DEP_PATH "${BLADE_ROOT_PATH}/blade/deps")
set(BLADE_BIN_PATH "${BLADE_BUILD_PATH}")
set(BLADE_LIB_PATH "${BLADE_BUILD_PATH}/lib")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${BLADE_BIN_PATH}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${BLADE_LIB_PATH}")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${BLADE_LIB_PATH}")

set(BLADE_BIN_DEBUG "${BLADE_BUILD_PATH}/Debug")
set(BLADE_BIN_RELEASE "${BLADE_BUILD_PATH}/Release")
set(BLADE_LIB_DEBUG "${BLADE_BUILD_PATH}/lib/Debug")
set(BLADE_LIB_RELEASE "${BLADE_BUILD_PATH}/lib/Release")

message(STATUS "\${CMAKE_BUILD_TYPE}: ${CMAKE_BUILD_TYPE}")
message(STATUS "\${BLADE_ROOT_PATH}: ${BLADE_ROOT_PATH}")
message(STATUS "\${BLADE_BUILD_PATH}: ${BLADE_BUILD_PATH}")
message(STATUS "\${BLADE_PATH}: ${BLADE_PATH}")
message(STATUS "\${BLADE_DEP_PATH}: ${BLADE_DEP_PATH}")
message(STATUS "\${BLADE_BIN_PATH}: ${BLADE_BIN_PATH}")
message(STATUS "\${BLADE_LIB_PATH}: ${BLADE_LIB_PATH}")

add_subdirectory(blade)
add_subdirectory(game)
