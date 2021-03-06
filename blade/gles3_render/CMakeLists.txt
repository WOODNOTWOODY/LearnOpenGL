message(STATUS "Configuring render: gles3_render...")

set(TARGET_NAME gles3_render)

# include files
set(INCLUDE_FILES
#	${BLADE_DEP_PATH}/glfw/include
#	${BLADE_DEP_PATH}/glad/include
	${BLADE_PATH}/core
	${BLADE_PATH}/gles3_render
)

if(WIN32)
	list(APPEND INCLUDE_FILES ${BLADE_DEP_PATH}/pvrsdk/include)

if(BLADE_CPU_X64)
	set(PVRSDK_LIB_DIR "x86_64")
else()
	set(PVRSDK_LIB_DIR "x86_32")
endif()
	
	link_libraries(
		${BLADE_DEP_PATH}/pvrsdk/windows/${PVRSDK_LIB_DIR}/lib/libEGL.lib
		${BLADE_DEP_PATH}/pvrsdk/windows/${PVRSDK_LIB_DIR}/lib/libGLESv2.lib
	)
endif()

include_directories(${INCLUDE_FILES})

file(GLOB HEADER_FILES *.h)
file(GLOB SOURCE_FILES *.cpp)
set(ALL_FILES ${HEADER_FILES} ${SOURCE_FILES})

add_definitions("-DBLADE_GLES3RENDER_EXPORTS")

if(BLADE_STATIC)
	add_library(${TARGET_NAME} STATIC ${ALL_FILES})
else()
	add_library(${TARGET_NAME} SHARED ${ALL_FILES})
endif()

target_link_libraries(${TARGET_NAME} ${BLADE_DEP_TARGETS})
target_link_libraries(${TARGET_NAME} core)

set_target_properties(${TARGET_NAME} PROPERTIES OUTPUT_NAME blade_gles3_render)

use_precompiled_header("${CMAKE_CURRENT_SOURCE_DIR}/GLES3RenderStd.h" "${CMAKE_CURRENT_SOURCE_DIR}/GLES3RenderStd.cpp" SOURCE_FILES)

message(STATUS "Configure success!")

