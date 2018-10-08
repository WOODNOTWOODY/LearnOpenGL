# add dependences
#set(BLADE_DEP_TARGETS glad glfw)
#foreach(TARGET ${BLADE_DEP_TARGETS})
#	add_subdirectory(deps/${TARGET})
#endforeach()

add_subdirectory(core)
add_subdirectory(gles3_render)
