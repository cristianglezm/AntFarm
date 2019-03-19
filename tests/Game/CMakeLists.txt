SET(SRC_TEST_ROOT "${PROJECT_SOURCE_DIR}/tests/Game")

# all source files
FILE(GLOB_RECURSE UNITTEST_SOURCES "${SRC_TEST_ROOT}/src/*.cpp")
FILE(GLOB_RECURSE UNITTEST_INCLUDES "${SRC_TEST_ROOT}/include/*.hpp")

# define the UNITTEST target
set(UNITTEST_SRC ${UNITTEST_SOURCES} ${UNITTEST_INCLUDES})
set(antfarm_SRC ${AntFarm_SOURCES} ${AntFarm_INCLUDES})

LIST(REMOVE_ITEM antfarm_SRC "${PROJECT_SOURCE_DIR}/src/main.cpp")

add_executable(UnitTests ${UNITTEST_SRC} ${antfarm_SRC})

target_include_directories(UnitTests PUBLIC "${SRC_TEST_ROOT}/include")

find_package(SFML 2.4 COMPONENTS graphics window system network audio REQUIRED)
if(SFML_FOUND)
    target_include_directories(UnitTests PUBLIC ${SFML_INCLUDE_DIR})
    target_link_libraries(UnitTests ${SFML_LIBRARIES})
endif(SFML_FOUND)

find_package(JSONBOX REQUIRED)
if(JSONBOX_FOUND)
    target_include_directories(UnitTests PUBLIC ${JSONBOX_INCLUDE_DIR})
    target_link_libraries(UnitTests ${JSONBOX_LIBRARIES})
endif(JSONBOX_FOUND)

SET(CMAKE_CXX_STANDARD 17)
SET(CMAKE_CXX_STANDARD_REQUIRED ON)
SET(CMAKE_CXX_EXTENSIONS OFF)

if(WIN32)
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static -lpthread -static-libgcc -static-libstdc++ -mwindows -Wall")
endif(WIN32)

if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build (Debug or Release)" FORCE)
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -pg")
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -fexpensive-optimizations")
endif()

add_test(UnitTests UnitTests)