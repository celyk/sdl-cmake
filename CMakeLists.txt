cmake_minimum_required(VERSION 3.2)

project(App)

set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY BOTH)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE BOTH)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} "includes/GLEW/")
set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} "includes/GLM/")

set(SDL2_DIR "includes/SDL2")
add_subdirectory(${SDL2_DIR})

find_library(SDL2 SDL2)
find_package(GLM REQUIRED)

set(LIBS SDL2main)
set(INCLUDES ${GLM_INCLUDE_DIRS})

file(GLOB_RECURSE SOURCE_FILES src/*.cpp)
file(GLOB_RECURSE HEADER_FILES src/*.h)

if(ANDROID)
	# On android the final binary is a shared library not an executable.
	add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES} ${HEADER_FILES})
	set(LIBS ${LIBS} SDL2 GLESv3)
	set(RESOURCE_DIR "${CMAKE_SOURCE_DIR}/build/android/thing4/app/src/main/assets")
else()
	find_package(OpenGL REQUIRED)
	set(GLEW_USE_STATIC_LIBS TRUE)
	find_package(GLEW REQUIRED)
	add_executable(${PROJECT_NAME} ${SOURCE_FILES} ${HEADER_FILES})
	set(LIBS ${LIBS} SDL2-static opengl32 GLEW::GLEW wsock32)
	set(INCLUDES ${INCLUDES} ${GLEW_INCLUDE_DIRS})
	set(RESOURCE_DIR $<TARGET_FILE_DIR:${PROJECT_NAME}>)
endif()

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_directory
	"${CMAKE_SOURCE_DIR}/resources"
	${RESOURCE_DIR})

target_include_directories(${PROJECT_NAME} PRIVATE ${INCLUDES})
target_link_libraries(${PROJECT_NAME} PRIVATE ${LIBS})