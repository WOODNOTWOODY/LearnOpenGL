message(STATUS "Configuring deps: glfw3...")

set(GLFW_VERSION_MAJOR "3")
set(GLFW_VERSION_MINOR "3")
set(GLFW_VERSION "${GLFW_VERSION_MAJOR}.${GLFW_VERSION_MINOR}")

set(TARGET_NAME glfw3)

set(common_HEADERS 
	${BLADE_DEP_PATH}/glfw/src/internal.h 
	${BLADE_DEP_PATH}/glfw/src/mappings.h
    ${BLADE_DEP_PATH}/glfw/src/glfw_config.h
    ${BLADE_DEP_PATH}/glfw/include/GLFW/glfw3.h
    ${BLADE_DEP_PATH}/glfw/include/GLFW/glfw3native.h
)
set(common_SOURCES 
	${BLADE_DEP_PATH}/glfw/src/context.c 
	${BLADE_DEP_PATH}/glfw/src/init.c 
	${BLADE_DEP_PATH}/glfw/src/input.c 
	${BLADE_DEP_PATH}/glfw/src/monitor.c 
	${BLADE_DEP_PATH}/glfw/src/vulkan.c 
	${BLADE_DEP_PATH}/glfw/src/window.c
)

set(glfw_HEADERS 
	${common_HEADERS} 
	${BLADE_DEP_PATH}/glfw/src/win32_platform.h 
	${BLADE_DEP_PATH}/glfw/src/win32_joystick.h
	${BLADE_DEP_PATH}/glfw/src/wgl_context.h 
	${BLADE_DEP_PATH}/glfw/src/egl_context.h 
	${BLADE_DEP_PATH}/glfw/src/osmesa_context.h
)
set(glfw_SOURCES 
	${common_SOURCES} 
	${BLADE_DEP_PATH}/glfw/src/win32_init.c 
	${BLADE_DEP_PATH}/glfw/src/win32_joystick.c
	${BLADE_DEP_PATH}/glfw/src/win32_monitor.c 
	${BLADE_DEP_PATH}/glfw/src/win32_time.c 
	${BLADE_DEP_PATH}/glfw/src/win32_thread.c 
	${BLADE_DEP_PATH}/glfw/src/win32_window.c
	${BLADE_DEP_PATH}/glfw/src/wgl_context.c 
	${BLADE_DEP_PATH}/glfw/src/egl_context.c 
	${BLADE_DEP_PATH}/glfw/src/osmesa_context.c
)

add_library(${TARGET_NAME} STATIC ${glfw_SOURCES} ${glfw_HEADERS})
set_target_properties(${TARGET_NAME} PROPERTIES
                      OUTPUT_NAME ${TARGET_NAME}
                      VERSION ${GLFW_VERSION}
                      SOVERSION ${GLFW_VERSION_MAJOR}
                      POSITION_INDEPENDENT_CODE ON
                      FOLDER deps)
					 
target_compile_definitions(${TARGET_NAME} PRIVATE _GLFW_USE_CONFIG_H)
					  
message(STATUS "Configure success!")


