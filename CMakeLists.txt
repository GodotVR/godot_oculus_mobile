cmake_minimum_required(VERSION 3.6)

# Default android abi is arm64-v8a
if (NOT ANDROID_ABI)
    set(ANDROID_ABI "arm64-v8a")
endif (NOT ANDROID_ABI)

# Default android platform is android-23
if (NOT ANDROID_PLATFORM)
    set(ANDROID_PLATFORM "android-23")
endif (NOT ANDROID_PLATFORM)

# Default build type is Debug
if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif (NOT CMAKE_BUILD_TYPE)

if (CMAKE_BUILD_TYPE MATCHES Debug)
    add_definitions(-D_DEBUG)
    set(VRAPI_LIB_BUILD_TYPE Debug)
else ()
    add_definitions(-DNDEBUG)
    set(VRAPI_LIB_BUILD_TYPE Release)
endif (CMAKE_BUILD_TYPE MATCHES Debug)

if (NOT (ANDROID_STL STREQUAL "c++_shared"))
    set(ANDROID_STL "c++_shared")
endif (NOT (ANDROID_STL STREQUAL "c++_shared"))

# Check if ANDROID_NDK is set.
if (NOT ANDROID_NDK)
    # Set to ANDROID_NDK_HOME environment variable if it's set.
    if (DEFINED ENV{ANDROID_NDK_HOME})
        set(ANDROID_NDK $ENV{ANDROID_NDK_HOME})
    else (DEFINED ENV{ANDROID_NDK_HOME})
        message(WARNING "ANDROID_NDK_HOME is not set")
    endif (DEFINED ENV{ANDROID_NDK_HOME})
endif (NOT ANDROID_NDK)

# Check if CMAKE_TOOLCHAIN_FILE is set.
if (NOT CMAKE_TOOLCHAIN_FILE)
    set(CMAKE_TOOLCHAIN_FILE "${ANDROID_NDK}/build/cmake/android.toolchain.cmake")
endif (NOT CMAKE_TOOLCHAIN_FILE)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

project(godot_ovrmobile)

# Set the default output directory.
if (NOT CMAKE_LIBRARY_OUTPUT_DIRECTORY)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/demo/addons/${CMAKE_PROJECT_NAME}/libs/${ANDROID_ABI}")
endif (NOT CMAKE_LIBRARY_OUTPUT_DIRECTORY)

# Create the default output directory if necessary.
if (NOT (EXISTS ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}))
    file(MAKE_DIRECTORY ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
endif (NOT (EXISTS ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}))

###############################################################################
## PROJECT SETUP
## The variables below should be updated based on the setup instructions
## in the project README.

# Sets the path to the VrApi root directory. Update this variable if the api is in another location.
set(OVR_ROOT_DIR "${CMAKE_SOURCE_DIR}/ovr_sdk_mobile/1.24.0/VrApi")

# Location to the Godot headers directory. The default location is "${CMAKE_SOURCE_DIR}/godot_headers"
set(GODOT_HEADERS_DIR "${CMAKE_SOURCE_DIR}/godot_headers")
###############################################################################

set(OVR_HEADERS_DIR "${OVR_ROOT_DIR}/Include" CACHE STRING "")

set(GODOT_COMPILE_FLAGS)
set(GODOT_LINKER_FLAGS)

set(GODOT_LINKER_FLAGS "-Wl")

set(GODOT_COMPILE_FLAGS "-fPIC -g -Wwrite-strings")
set(GODOT_COMPILE_FLAGS "${GODOT_COMPILE_FLAGS} -Wchar-subscripts -Wcomment -Wdisabled-optimization")
set(GODOT_COMPILE_FLAGS "${GODOT_COMPILE_FLAGS} -Wformat -Wformat=2 -Wformat-security -Wformat-y2k")
set(GODOT_COMPILE_FLAGS "${GODOT_COMPILE_FLAGS} -Wimport -Winit-self -Winline -Winvalid-pch")
set(GODOT_COMPILE_FLAGS "${GODOT_COMPILE_FLAGS} -Wlong-long -Wmissing-braces -Wmissing-format-attribute")
set(GODOT_COMPILE_FLAGS "${GODOT_COMPILE_FLAGS} -Wmissing-include-dirs -Wmissing-noreturn -Wpacked -Wpointer-arith")
set(GODOT_COMPILE_FLAGS "${GODOT_COMPILE_FLAGS} -Wredundant-decls -Wreturn-type -Wsequence-point")
set(GODOT_COMPILE_FLAGS "${GODOT_COMPILE_FLAGS} -Wswitch -Wswitch-enum -Wtrigraphs")
set(GODOT_COMPILE_FLAGS "${GODOT_COMPILE_FLAGS} -Wuninitialized -Wunknown-pragmas -Wunreachable-code -Wunused-label")
set(GODOT_COMPILE_FLAGS "${GODOT_COMPILE_FLAGS} -Wunused-value -Wvariadic-macros -Wvolatile-register-var -Wno-error=attributes")
set(GODOT_COMPILE_FLAGS "${GODOT_COMPILE_FLAGS} -fno-omit-frame-pointer -O0")

if (NOT CMAKE_SYSTEM_NAME STREQUAL "Android")
    set(GODOT_COMPILE_FLAGS "${GODOT_COMPILE_FLAGS} -Wno-ignored-attributes")
endif ()

if (CMAKE_BUILD_TYPE MATCHES Debug)
    set(GODOT_COMPILE_FLAGS "${GODOT_COMPILE_FLAGS} -fno-omit-frame-pointer -O0")
else ()
    set(GODOT_COMPILE_FLAGS "${GODOT_COMPILE_FLAGS} -O3")
endif (CMAKE_BUILD_TYPE MATCHES Debug)

# OVR library
set(VRAPI_LIB_PATH "${OVR_ROOT_DIR}/Libs/Android/${ANDROID_ABI}/${VRAPI_LIB_BUILD_TYPE}/libvrapi.so")
add_library(vrapi SHARED IMPORTED GLOBAL)
set_target_properties(vrapi PROPERTIES IMPORTED_LOCATION ${VRAPI_LIB_PATH})

# Get Sources
file(GLOB_RECURSE SOURCES src/*.c**)
file(GLOB_RECURSE HEADERS src/*.h**)

add_library(${PROJECT_NAME}
        SHARED
        ${SOURCES} ${HEADERS})

target_include_directories(${PROJECT_NAME}
        PRIVATE
        src
        )

# Put godot headers as SYSTEM PUBLIC to exclude warnings from irrelevant headers
target_include_directories(${PROJECT_NAME}
        SYSTEM PUBLIC
        ${GODOT_HEADERS_DIR}
        ${OVR_HEADERS_DIR}
        )

target_link_libraries(${PROJECT_NAME}
        android
        log
        EGL
        GLESv3
        vrapi)

# Add the compile flags
set_property(TARGET ${PROJECT_NAME} APPEND_STRING PROPERTY COMPILE_FLAGS ${GODOT_COMPILE_FLAGS})
set_property(TARGET ${PROJECT_NAME} APPEND_STRING PROPERTY LINK_FLAGS ${GODOT_LINKER_FLAGS})

# Copy the VrApi shared library to the output directory.
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different ${VRAPI_LIB_PATH} $<TARGET_FILE_DIR:${PROJECT_NAME}>)

set(BITS 32)
if (CMAKE_SIZEOF_VOID_P EQUAL 8)
    set(BITS 64)
endif (CMAKE_SIZEOF_VOID_P EQUAL 8)
