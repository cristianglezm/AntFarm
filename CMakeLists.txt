cmake_minimum_required(VERSION 2.8)

project(AntFarm)

# Set the include directory
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/include)

# Set the cmake search paths
SET(CMAKE_INCLUDE_PATH ${CMAKE_SOURCE_DIR}/include)

# Set the directory of Find<Library>.cmake modules
SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/modules")

# find all source files in the src directory
FILE(GLOB AntFarm_SRC "src/*.cpp")

# find all the files in the includes directory
FILE(GLOB AntFarm_INCLUDES "include/*.h" "include/*.hpp")

# Specify default build type if none provided (before project() command)
if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build (Debug or Release)" FORCE)
endif()

# For generators with multiple configurations (like VS), only allow Debug and Release
if(CMAKE_CONFIGURATION_TYPES)
	set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "Limited configurations" FORCE)
	mark_as_advanced(CMAKE_CONFIGURATION_TYPES)
endif()

# Compiler-specific flags and definitions
if(CMAKE_COMPILER_IS_GNUCXX)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wno-long-long -pedantic")
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -stdlib=libc++")
endif()

add_definitions(-DSFML_STATIC)

# Add External libraries
# Detect and add SFML
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/modules" ${CMAKE_MODULE_PATH})
#Find any version 2.X of SFML
find_package(SFML 2 REQUIRED system window graphics network audio)
if(SFML_FOUND)
  include_directories(${SFML_INCLUDE_DIR})
  target_link_libraries(${EXECUTABLE_NAME} ${SFML_LIBRARIES})
endif()

#add_subdirectory(test)
add_subdirectory(include)
add_subdirectory(src)
