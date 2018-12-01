cmake_minimum_required(VERSION 3.2)
set(PROJECTNAME "Craft")
project(${PROJECTNAME})

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static")

# Set default build type explicitly to Release
if (NOT CMAKE_BUILD_TYPE)
    set (CMAKE_BUILD_TYPE "Debug" CACHE STRING "Choose the type of build type." FORCE)
endif (NOT CMAKE_BUILD_TYPE)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake_modules/)

#Add files
file(GLOB_RECURSE SOURCES Source/*.cpp)

add_executable(${PROJECTNAME}  main.cpp ${SOURCES})


#find_package( OpenGL REQUIRED )

set(SFML_ROOT "G:/SFML")
# Find SFML
set(SFML_STATIC_LIBRARIES TRUE)
find_package(SFML REQUIRED audio graphics window system)

# glad
set(GLAD_DIR "Source/glad")
add_library("glad" "${GLAD_DIR}/glad.c")
target_include_directories("glad" PRIVATE "${GLAD_DIR}")
target_include_directories(${PROJECT_NAME} PRIVATE "${GLAD_DIR}")
target_link_libraries(${PROJECT_NAME} "glad" "${CMAKE_DL_LIBS}")
#find_package(Threads)


include_directories(${SFML_INCLUDE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(G:/SFML/include/glm)
#include_directories(C:/MinGW/mingw32/include)


target_link_libraries(${PROJECTNAME} ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})