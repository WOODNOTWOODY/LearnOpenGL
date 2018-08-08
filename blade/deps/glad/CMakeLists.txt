message(STATUS "Configuring dependence target: glad...")

set(TARGET_NAME glad)

# include files
set(INCLUDE_FILES
	${BLADE_DEP_PATH}/glad/include
)

include_directories(${INCLUDE_FILES})

set(SOURCE_FILES
	src/glad.c
)

add_library(${TARGET_NAME} STATIC ${SOURCE_FILES})

set_target_properties(${TARGET_NAME} PROPERTIES OUTPUT_NAME glad)

set_target_properties(${TARGET_NAME} PROPERTIES FOLDER deps)

message(STATUS "Configure success!")


