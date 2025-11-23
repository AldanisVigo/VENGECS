cmake_minimum_required(VERSION 3.6)
project(VENGecs LANGUAGES CXX)

# Use C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Put compiled binary in bin folder
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

# Collect all C++ files inside src
file(GLOB_RECURSE SOURCES
    ${CMAKE_SOURCE_DIR}/src/*.cpp
)

# Create the executable
add_executable(VENGecs ${SOURCES})

# ---- SDL2 Integration ----
find_package(SDL2 REQUIRED)
if(SDL2_FOUND)
    include_directories(${SDL2_INCLUDE_DIRS})
    target_link_libraries(VENGecs ${SDL2_LIBRARIES})
endif()

# ---- SDL2_image Integration (Homebrew) ----
# Adjust these paths to match your Homebrew installation
set(SDL2_IMAGE_INCLUDE_DIR /opt/homebrew/Cellar/sdl2_image/2.8.8/include)
set(SDL2_IMAGE_LIBRARY /opt/homebrew/Cellar/sdl2_image/2.8.8/lib/libSDL2_image.dylib)

include_directories(${SDL2_IMAGE_INCLUDE_DIR})
target_link_libraries(VENGecs ${SDL2_IMAGE_LIBRARY})

# ---- SDL2_mixer Integration ----
set(SDL2_MIXER_INCLUDE_DIR /opt/homebrew/Cellar/sdl2_mixer/2.8.1_1/include)
set(SDL2_MIXER_LIBRARY /opt/homebrew/Cellar/sdl2_mixer/2.8.1_1/lib/libSDL2_mixer.dylib)

include_directories(${SDL2_MIXER_INCLUDE_DIR})
target_link_libraries(VENGecs ${SDL2_MIXER_LIBRARY})

# ---- Run Target ----
add_custom_target(run
    COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/VENGecs
    WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
)
