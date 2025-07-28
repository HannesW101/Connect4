cmake_minimum_required(VERSION 3.28)
project(Connect4 LANGUAGES CXX)

# Set output directory for executables
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Enable C++20 standard globally
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Download and build SFML
include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.1
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM
)
FetchContent_MakeAvailable(SFML)

# Add your executable with all source files
add_executable(Game 
    main.cpp 
    src/main_menu.cpp
 "include/constants.h" "src/button.cpp")
 
 # Copy assets to build directory
 file(COPY assets DESTINATION ${CMAKE_BINARY_DIR}/bin)

# Include your custom headers
target_include_directories(Game PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Link required SFML libraries
target_link_libraries(Game PRIVATE
    SFML::Graphics
    SFML::Window
    SFML::System  
    SFML::Audio
)