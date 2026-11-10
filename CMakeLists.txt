cmake_minimum_required(VERSION 3.14)
project(StormPhysics C CXX)   # C is needed for glad.c

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)   # helps VS Code IntelliSense / clangd

# Default to an optimized build
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

# ---------------------------------------------------------------------------
# Storm physics library  (libstorm.a)
#   Picks up every .cpp in src/storm/ automatically, so new files like
#   particle.cpp are included without editing this file.
# ---------------------------------------------------------------------------
file(GLOB STORM_SOURCES CONFIGURE_DEPENDS ${CMAKE_SOURCE_DIR}/src/storm/*.cpp)

add_library(storm STATIC ${STORM_SOURCES})
target_include_directories(storm PUBLIC ${CMAKE_SOURCE_DIR}/inc)   # #include <storm/core.h>
set_target_properties(storm PROPERTIES POSITION_INDEPENDENT_CODE ON)

# ---------------------------------------------------------------------------
# glad  (OpenGL loader)  -> inc/glad/glad.h, inc/KHR/khrplatform.h, src/demos/glad.c
# ---------------------------------------------------------------------------
add_library(glad STATIC ${CMAKE_SOURCE_DIR}/src/demos/glad.c)
target_include_directories(glad PUBLIC ${CMAKE_SOURCE_DIR}/inc)
target_link_libraries(glad PUBLIC ${CMAKE_DL_LIBS})

# ---------------------------------------------------------------------------
# GLFW
#   inc/GLFW only has the headers; the compiled library still has to come
#   from somewhere. Uses Homebrew's copy if installed (`brew install glfw`),
#   otherwise downloads and builds it.
# ---------------------------------------------------------------------------
find_package(glfw3 3.3 QUIET)
if(NOT glfw3_FOUND)
    message(STATUS "GLFW not found on system - fetching it")
    include(FetchContent)
    set(GLFW_BUILD_DOCS     OFF CACHE BOOL "" FORCE)
    set(GLFW_BUILD_TESTS    OFF CACHE BOOL "" FORCE)
    set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
    FetchContent_Declare(glfw
        GIT_REPOSITORY https://github.com/glfw/glfw.git
        GIT_TAG        3.4
    )
    FetchContent_MakeAvailable(glfw)
endif()

if(APPLE)
    add_compile_definitions(GL_SILENCE_DEPRECATION)
endif()

# ---------------------------------------------------------------------------
# Demos
#   Each folder in src/demos/ becomes its own program, e.g.
#     src/demos/ballistic/ballistic.cpp  ->  bin/ballistic
#   .cpp files directly in src/demos/ (shared app/timing code) are linked
#   into every demo.
# ---------------------------------------------------------------------------
file(GLOB DEMO_COMMON_SOURCES CONFIGURE_DEPENDS ${CMAKE_SOURCE_DIR}/src/demos/*.cpp)

file(GLOB DEMO_DIRS LIST_DIRECTORIES true ${CMAKE_SOURCE_DIR}/src/demos/*)
foreach(dir ${DEMO_DIRS})
    if(IS_DIRECTORY ${dir})
        get_filename_component(demo ${dir} NAME)
        file(GLOB DEMO_SOURCES CONFIGURE_DEPENDS ${dir}/*.cpp)
        if(DEMO_SOURCES)
            add_executable(${demo} ${DEMO_SOURCES} ${DEMO_COMMON_SOURCES})
            target_link_libraries(${demo} PRIVATE storm glad glfw)
        endif()
    endif()
endforeach()