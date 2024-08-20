cmake_minimum_required(VERSION 3.10)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/CMakeModules/")
# Project Name
project(shmup C)

find_package(SDL2 REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_mixer REQUIRED)

set(IncludeDirs
    include
    lib
    ${SDL2_INCLUDE_DIR}
	${SDL2_TTF_INCLUDE_DIR}
	${SDL2_IMAGE_INCLUDE_DIR}
	${SDL2_MIXER_INCLUDE_DIR}
)

set(SourceFiles
    src/main.c
    src/game.c
    src/drawable.c
)
    
set(SDL2_LIB libsdl)
add_executable(shmup ${SourceFiles})

target_include_directories(shmup PRIVATE ${IncludeDirs})
target_link_libraries(
    shmup
    ${SDL2_LIBRARY}
	${SDL2_TTF_LIBRARY}
	${SDL2_IMAGE_LIBRARY}
	${SDL2_MIXER_LIBRARY}
)