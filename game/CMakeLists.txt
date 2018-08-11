message(STATUS "Configuring sample: game...")

set(TARGET_NAME game)

# include files
set(INCLUDE_FILES
	${BLADE_DEP_PATH}/glfw/include
	${BLADE_DEP_PATH}/glad/include
	${BLADE_PATH}
	${BLADE_PATH}/core
)

include_directories(${INCLUDE_FILES})

file(GLOB HEADER_FILES *.h)
file(GLOB SOURCE_FILES *.cpp)
set(ALL_FILES ${HEADER_FILES} ${SOURCE_FILES})

use_precompiled_header("${CMAKE_CURRENT_SOURCE_DIR}/StdAfx.h" "${CMAKE_CURRENT_SOURCE_DIR}/StdAfx.cpp" SOURCE_FILES)

add_executable(${TARGET_NAME} ${ALL_FILES})

target_link_libraries(${TARGET_NAME} core gles3_render)

message(STATUS "Configure success!")
