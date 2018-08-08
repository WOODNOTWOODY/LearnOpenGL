message(STATUS "Configuring sample: game...")

set(TARGET_NAME game)

# include files
set(INCLUDE_FILES
	${BLADE_PATH}
)

include_directories(${INCLUDE_FILES})

file(GLOB HEADER_FILES *.h)
file(GLOB SOURCE_FILES *.cpp)
set(ALL_FILES ${HEADER_FILES} ${SOURCE_FILES})

use_precompiled_header("${CMAKE_CURRENT_SOURCE_DIR}/StdAfx.h" "${CMAKE_CURRENT_SOURCE_DIR}/StdAfx.cpp" SOURCE_FILES)

add_executable(${TARGET_NAME} WIN32 ${ALL_FILES})

message(STATUS "Configure success!")
