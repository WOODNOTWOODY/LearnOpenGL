message(STATUS "Configuring target: core...")

set(TARGET_NAME core)

set(INCLUDE_FILES 
  ${BLADE_DEP_PATH}/dirent
  ${BLADE_PATH}/core
)

include_directories(${INCLUDE_FILES})

file(GLOB_RECURSE HEADER_FILES *.h)
file(GLOB_RECURSE SOURCE_FILES *.cpp)

macro(GROUP_FILES src_files)
	set(cur_dir ${CMAKE_CURRENT_SOURCE_DIR})
	foreach(src_file ${${src_files}})
		string(REGEX REPLACE ${cur_dir}/\(.*\) \\1 sgbd_fpath ${src_file})
		string(REGEX REPLACE "\(.*\)/.*" \\1 sgbd_group_name ${sgbd_fpath})
		string(COMPARE EQUAL ${sgbd_fpath} ${sgbd_group_name} sgbd_nogroup)
			
		string(REPLACE "\\" "/" sgbd_group_name ${sgbd_group_name})

		if(sgbd_nogroup)
			set(sgbd_group_name "/")
		endif(sgbd_nogroup)

	
		if(MSVC)
			string(REPLACE "/" "\\" sgbd_group_name ${sgbd_group_name})
		endif()
		source_group(${sgbd_group_name} FILES ${src_file})
	endforeach(src_file)
endmacro(GROUP_FILES)

set(ALL_FILES ${HEADER_FILES} ${SOURCE_FILES})

GROUP_FILES(ALL_FILES)

add_definitions("-DBLADE_CORE_EXPORTS -DDLLEXPORT")

if (BLADE_STATIC)
	add_library(${TARGET_NAME} STATIC ${ALL_FILES})
else()
	add_library(${TARGET_NAME} SHARED ${ALL_FILES})
endif()

set_target_properties(${TARGET_NAME} PROPERTIES OUTPUT_NAME blade_core)

use_precompiled_header("${CMAKE_CURRENT_SOURCE_DIR}/CoreStd.h" "${CMAKE_CURRENT_SOURCE_DIR}/CoreStd.cpp" SOURCE_FILES)

message(STATUS "Configure success!")


