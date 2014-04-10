include(FindPackageHandleStandardArgs)

# if JSONBOX_ROOT has defined in system environment, use this as a hint
set(JSONBOX_ROOT "$ENV{JSONBOX_ROOT}" ${JSONBOX_ROOT})

set(JSONBOX_INCLUDE_DIRS "${JSONBOX_ROOT}/JsonBox.h" "${JSONBOX_ROOT}/include")
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
  set(JSONBOX_LIBRARY_DEBUG "${JSONBOX_ROOT}/lib/JsonBox-d.a")
  set(JSONBOX_LIBRARIES ${JSONBOX_LIBRARY_DEBUG})
endif()
if(CMAKE_BUILD_TYPE STREQUAL "Release")
 set(JSONBOX_LIBRARY_RELEASE "${JSONBOX_ROOT}/lib/JsonBox.a")
 set(JSONBOX_LIBRARIES ${JSONBOX_LIBRARY_RELEASE})
endif()

find_package_handle_standard_args(JSONBOX DEFAULT_MSG JSONBOX_INCLUDE_DIRS JSONBOX_LIBRARIES)
