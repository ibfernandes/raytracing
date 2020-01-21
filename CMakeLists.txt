cmake_minimum_required(VERSION 3.9)
project(RayTracing)
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT RayTracing)

file(GLOB SOURCE_FILES
    "src/*.h"
    "src/*.cpp"
)

add_executable(RayTracing ${SOURCE_FILES} )
