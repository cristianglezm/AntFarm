cmake_minimum_required(VERSION 3.1)

################################################################################
### User options.
################################################################################

option(BUILD_STATIC "TRUE to statically link to the standard libraries and dependencies, FALSE to use them as DLLs" FALSE)
if(BUILD_STATIC)
	SET(SFML_STATIC_LIBRARIES TRUE)
	SET(BUILD_SHARED_LIBS FALSE)
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static -lpthread -static-libgcc -static-libstdc++ -mwindows")
endif(BUILD_STATIC)

################################################################################
### Project files.
################################################################################

project(AntFarm)

INCLUDE_DIRECTORIES("${CMAKE_SOURCE_DIR}/include")

SET(CMAKE_INCLUDE_PATH ${CMAKE_SOURCE_DIR})
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

FILE(GLOB_RECURSE AntFarm_SOURCES "src/*.cpp" "src/*")
FILE(GLOB_RECURSE AntFarm_INCLUDES "include/*.h" "include/*.hpp")

if(WIN32)
	FILE(GLOB_RECURSE SFML_DEBUG_DLLS "${SFML_ROOT}/bin/sfml-*-d-2.dll")
	FILE(GLOB_RECURSE SFML_RELEASE_DLLS "${SFML_ROOT}/bin/*-2.dll")
	if(NOT SFML_DEBUG_DLLS STREQUAL "")
		LIST(REMOVE_ITEM SFML_RELEASE_DLLS ${SFML_DEBUG_DLLS})
	endif()
endif(WIN32)

add_executable(AntFarm ${AntFarm_SOURCES} ${AntFarm_INCLUDES})

################################################################################
### Testing
################################################################################

#enable_testing()

################################################################################
### Dependencies.
################################################################################

#sfml
find_package(SFML 2.1 COMPONENTS graphics window system network audio REQUIRED)
if(SFML_FOUND)
	include_directories(${SFML_INCLUDE_DIR})
	target_link_libraries(AntFarm ${SFML_LIBRARIES})
endif(SFML_FOUND)

#jsonbox
find_package(JSONBOX REQUIRED)
if(JSONBOX_FOUND)
	include_directories(${JSONBOX_INCLUDE_DIR})
	target_link_libraries(AntFarm ${JSONBOX_LIBRARIES})
endif(JSONBOX_FOUND)

################################################################################
### Enable C++14 and warnings
################################################################################

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall")
if(WIN32)
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static -lpthread -static-libgcc -static-libstdc++ -mwindows")
endif(WIN32)

if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build (Debug or Release)" FORCE)
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -pg")
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -fexpensive-optimizations")
endif()

#################################################################################
### Installing Game
#################################################################################
install(TARGETS AntFarm RUNTIME DESTINATION .
			ARCHIVE DESTINATION .)
install(FILES LICENSE.md README.md DESTINATION .)

if(NOT BUILD_STATIC AND WIN32)
	if(CMAKE_BUILD_TYPE STREQUAL "Debug")
		install(FILES ${SFML_DEBUG_DLLS} DESTINATION .)
	elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
		install(FILES ${SFML_RELEASE_DLLS} DESTINATION .)
	endif()
endif(NOT BUILD_STATIC AND WIN32)

install(DIRECTORY data DESTINATION .)
