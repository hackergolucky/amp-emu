cmake_minimum_required(VERSION 3.19)

project(amp VERSION 1.0)

find_package(SDL2 2.0.17 EXACT REQUIRED)
message("Found SDL2 includes at: " ${SDL_INCLUDE_DIRS})
message("Found SDL2 libs at: " ${SDL2_LIBRARIES})

file(GLOB_RECURSE AMP_SRCS "source/*.c" "source/*.cpp")

include_directories(
    ${CMAKE_SOURCE_DIR}/include/
    
    ${CMAKE_SOURCE_DIR}/externals/nfde/src/include/
    ${CMAKE_SOURCE_DIR}/externals/imgui/
    ${CMAKE_SOURCE_DIR}/externals/imgui/backends/
    
    ${SDL2_INCLUDE_DIRS}
)

add_subdirectory( ${CMAKE_SOURCE_DIR}/externals/nfde/ )

add_executable(amp ${AMP_SRCS})

if (APPLE)

    message("macOS detected! Looking for AppKit...")

    find_library(MACOS_APPKIT AppKit)
    if (NOT MACOS_APPKIT)
        message(FATAL_ERROR "AppKit not found! Aborting!")
    endif ()

    target_link_libraries(amp ${MACOS_APPKIT})

endif ()

target_link_libraries(amp
    ${SDL2_LIBRARIES}
    nfd
)
