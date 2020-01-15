cmake_minimum_required(VERSION 3.16)

project(learn-cmake-conan CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})

file(GLOB SOURCES "src/*.cpp")
 
include("build/conanbuildinfo.cmake")
conan_basic_setup()
 
add_executable(learn-cmake-conan ${SOURCES})
target_link_libraries(${PROJECT_NAME} PUBLIC ${CONAN_LIBS})

target_include_directories(${PROJECT_NAME} PUBLIC include/)

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
	target_compile_options(${PROJECT_NAME} PRIVATE -Werror -Wall -Wextra -pedantic-errors)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
	target_compile_options(${PROJECT_NAME} PRIVATE /W4)
endif()

set_target_properties(${PROJECT_NAME}
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin"
)

message("TAMERE ${CMAKE_SOURCE_DIR}")