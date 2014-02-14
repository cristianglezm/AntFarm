#################################################################################
##
## Copyright (C) 2014 Cristian Gonzalez Moreno (Cristian.glez.m@gmail.com)
## 
## This software is provided 'as-is', without any express or implied
## warranty. In no event will the authors be held liable for any damages
## arising from the use of this software.
## 
## Permission is granted to anyone to use this software for any purpose,
## including commercial applications, and to alter it and redistribute it
## freely, subject to the following restrictions:
## 
## 1. The origin of this software must not be misrepresented; you must not
##    claim that you wrote the original software. If you use this software
##    in a product, an acknowledgment in the product documentation would be
##    appreciated but is not required.
## 
## 2. Altered source versions must be plainly marked as such, and must not be
##    misrepresented as being the original software.
## 
## 3. This notice may not be removed or altered from any source distribution.
##
#################################################################################

cmake_minimum_required(VERSION 2.8)

# Specify default build type if none provided (before project() command)
if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build (Debug or Release)" FORCE)
endif()

# For generators with multiple configurations (like VS), only allow Debug and Release
if(CMAKE_CONFIGURATION_TYPES)
	set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "Limited configurations" FORCE)
	mark_as_advanced(CMAKE_CONFIGURATION_TYPES)
endif()

project(AntFarm)

set(ANTFARM_EXTERNAL_PATH "${CMAKE_SOURCE_DIR}/../External" CACHE PATH "Path to the folder containing external libraries.")
set(CMAKE_INSTALL_PREFIX "${CMAKE_SOURCE_DIR}/dist" CACHE PATH "Path to the folder where we want to run the executable from.")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_INSTALL_PREFIX})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_INSTALL_PREFIX})

# Compiler-specific flags and definitions
if(CMAKE_COMPILER_IS_GNUCXX)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wno-long-long -pedantic")
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -stdlib=libc++")
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
	add_definitions(-DDEBUG)
endif()

# Add External libraries
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)

include_directories(${TYR_EXTERNAL_PATH}/SFML/include)
include_directories(${TYR_EXTERNAL_PATH}/boost)
include_directories(${TYR_EXTERNAL_PATH}/glm)
include_directories(${TYR_EXTERNAL_PATH}/yaml-cpp/include)
include_directories(${TYR_EXTERNAL_PATH}/lua/src)
include_directories(${GLEW_INCLUDE_DIR} ${OPENGL_INCLUDE_DIR})

link_directories(${TYR_EXTERNAL_PATH}/SFML/Build/lib)
link_directories(${TYR_EXTERNAL_PATH}/yaml-cpp)
link_directories(${TYR_EXTERNAL_PATH}/lua/src)
link_directories(${GLEW_LIBRARY} ${OPENGL_LINK_PATH})


add_subdirectory(Tyr)
add_subdirectory(Test)
add_subdirectory(Game)
