# Set the minimum required version of CMake
cmake_minimum_required(VERSION 3.12)

# Define the project
project(src VERSION 1.0 LANGUAGES CXX)

# Add source to this project's executable
add_executable(Cmake
    "main.cpp" 
    "Player.cpp"   # Add new source file
    "Game.cpp"
    "Globals.cpp"
    "Raycaster.cpp"
    "Utils.cpp"
)

# Set C++ standard
set_property(TARGET Cmake PROPERTY CXX_STANDARD 20)

# Link libraries
target_link_libraries(Cmake PRIVATE
  "${CMAKE_SOURCE_DIR}/lib/sfml-graphics.lib"
  "${CMAKE_SOURCE_DIR}/lib/sfml-audio.lib"
  "${CMAKE_SOURCE_DIR}/lib/sfml-network.lib"
  "${CMAKE_SOURCE_DIR}/lib/sfml-system.lib"
  "${CMAKE_SOURCE_DIR}/lib/sfml-window.lib"
  "${CMAKE_SOURCE_DIR}/lib/openal32.lib"
  "${CMAKE_SOURCE_DIR}/lib/sfml-main.lib"
)

# Include directories
target_include_directories(Cmake PRIVATE 
    "${CMAKE_SOURCE_DIR}/include"
    "${CMAKE_SOURCE_DIR}/src"   # Add path to source directory
    "${CMAKE_SOURCE_DIR}/images"
)

# Post-build command to copy SFML DLLs to the output directory
add_custom_command(TARGET Cmake POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_SOURCE_DIR}/bin/sfml-graphics-2.dll"
        "${CMAKE_SOURCE_DIR}/bin/sfml-audio-2.dll"
        "${CMAKE_SOURCE_DIR}/bin/sfml-network-2.dll"
        "${CMAKE_SOURCE_DIR}/bin/sfml-system-2.dll"
        "${CMAKE_SOURCE_DIR}/bin/sfml-window-2.dll"
        "${CMAKE_SOURCE_DIR}/bin/openal32.dll"
        $<TARGET_FILE_DIR:Cmake>)

set(IMAGES
    "${CMAKE_SOURCE_DIR}/images/wallTexture.png"
    "${CMAKE_SOURCE_DIR}/images/MapPlayer16.png"
    #"${CMAKE_SOURCE_DIR}/images/image3.bmp"
)

# Post-build command to copy images to the output directory
add_custom_command(TARGET Cmake POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${IMAGES}
        $<TARGET_FILE_DIR:Cmake>)