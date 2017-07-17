cmake_minimum_required(VERSION 2.6)
project(brickbreak)

set(brickbreak_VERSION_MAJOR 1)
set(brickbreak_VERSION_MINOR 0)
configure_file(
  "${PROJECT_SOURCE_DIR}/config.h.in"
  "${PROJECT_BINARY_DIR}/config.h"
)
include_directories("${PROJECT_BINARY_DIR}")

file(GLOB SRC
  "src/*.hpp"
  "src/*.cpp"
)

# Define sources and executable
set(EXECUTABLE_NAME "brickbreak")
add_executable(${EXECUTABLE_NAME} ${SRC})

# Detect and add SDL / SDL_Image
set(CMAKE_MODULE_PATH
  "${CMAKE_SOURCE_DIR}/cmake_modules"
  ${CMAKE_MODULE_PATH})

if (APPLE)
find_library(SDL2 SDL2)
find_library(SDL2_IMAGE SDL2_image)
find_library(SDL2_TTF SDL2_ttf)
target_link_libraries(
  ${EXECUTABLE_NAME}
  ${SDL2}
  ${SDL2_IMAGE}
  ${SDL2_TTF}
)
endif ()

install(TARGETS ${EXECUTABLE_NAME} DESTINATION bin)
