cmake_minimum_required(VERSION 2.8)

project(AntFarm)

# Set the include directory
INCLUDE_DIRECTORIES("${CMAKE_SOURCE_DIR}/include")

# Set the cmake search paths
SET(CMAKE_INCLUDE_PATH ${CMAKE_SOURCE_DIR})

# Set the directory of Find<Library>.cmake modules
SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/modules")

# find all source files in the src directory
FILE(GLOB_RECURSE AntFarm_SOURCES "src/*.cpp" "src/*")

# find all the files in the includes directory
FILE(GLOB_RECURSE AntFarm_INCLUDES "include/*.h" "include/*.hpp" "include/*")

# Specify default build type if none provided (before project() command)
if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build (Debug or Release)" FORCE)
endif()

# For generators with multiple configurations (like VS), only allow Debug and Release
if(CMAKE_CONFIGURATION_TYPES)
	set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "Limited configurations" FORCE)
	mark_as_advanced(CMAKE_CONFIGURATION_TYPES)
endif()

# set flags for debug or release
if(CMAKE_CONFIGURATION_TYPE STREQUAL "Debug")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g -pg -Wall -Wno-long-long -pedantic")
elseif(CMAKE_CONFIGURATION_TYPE STREQUAL "Release")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -O3 -fexpensive-optimizations -stdlib=libc++")
endif()

# Compiler-specific flags and definitions
if(CMAKE_COMPILER_IS_GNUCXX)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -stdlib=libc++")
endif()

SET(SFML_STATIC_LIBRARIES TRUE)

SET(SFML_ROOT -1 CACHE PATH "SELECT THE ROOT DIR OF SFML")
if(SFML_ROOT LESS 0)
  message("SELECT THE ROOT DIRECTORY OF SFML")
endif()

SET(JSONBOX_ROOT -1 CACHE PATH "SELECT THE ROOT DIR OF JsonBox")
if(JSONBOX_ROOT LESS 0)
  message("SELECT THE ROOT DIRECTORY OF JsonBox")
endif()
# glob all sources
file(GLOB_RECURSE JSONBOX_SOURCES "${JSONBOX_ROOT}/src" "${JSONBOX_ROOT}/src/*.cpp")
file(GLOB_RECURSE JSONBOX_HEADERS "${JSONBOX_ROOT}/include" "${JSONBOX_ROOT}/include/*.h")

include_directories("${JSONBOX_ROOT}/include")

# setup static archive
add_library(JsonBox STATIC ${JSONBOX_SOURCES} ${JSONBOX_HEADERS})
install(TARGETS JsonBox ARCHIVE DESTINATION "lib" COMPONENT lib)

add_executable(AntFarm ${AntFarm_SOURCES} ${AntFarm_INCLUDES})

add_dependencies(AntFarm JsonBox)
target_link_libraries(AntFarm JsonBox)
# Add External libraries
# Detect and add SFML
#Find any version 2.X of SFML
find_package(SFML 2.1 COMPONENTS graphics window system network audio REQUIRED)
if(SFML_FOUND)
  include_directories(${SFML_INCLUDE_DIR})
  target_link_libraries(AntFarm ${SFML_LIBRARIES})
endif()



