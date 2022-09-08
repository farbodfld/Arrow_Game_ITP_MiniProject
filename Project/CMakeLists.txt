cmake_minimum_required(VERSION 3.15)
project(Project)

set(CMAKE_CXX_STANDARD 14)

include_directories(Project C:/SDL/SDL2/include)
include_directories(Project C:/SDL/SDL2_image/include)
include_directories(Project C:/SDL/SDL2_mixer/include)
include_directories(Project C:/SDL/SDL2_ttf/include)
link_directories(Project C:/SDL/SDL2/lib/x86)
link_directories(Project C:/SDL/SDL2_image/lib/x86)
link_directories(Project C:/SDL/SDL2_mixer/lib/x86)
link_directories(Project C:/SDL/SDL2_ttf/lib/x86)

add_executable(Project main.cpp)

target_link_libraries(Project -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf)