cmake_minimum_required(VERSION 3.21)
project(X_Tetris C)

find_package(raylib 4.0 REQUIRED)

set(CMAKE_C_STANDARD 90)

add_compile_options(-Wall -pedantic)

add_executable(X_Tetris Sources/main.c
        Libraries/auxiliary.h
        Sources/auxiliary.c
        Libraries/tetramino.h
        Libraries/field.h
        Sources/field.c
        Sources/tetramino.c
        Libraries/dataStructure.h
        Libraries/scoreboard.h
        Sources/scoreboard.c
        Libraries/menu.h
        Sources/menu.c
        Libraries/palette.h
        Sources/bot.c
        Libraries/bot.h)

target_link_libraries(${PROJECT_NAME} raylib)

# Checks if OSX and links appropriate frameworks (only required on MacOS)
if (APPLE)
    target_link_libraries(${PROJECT_NAME} "-framework IOKit")
    target_link_libraries(${PROJECT_NAME} "-framework Cocoa")
    target_link_libraries(${PROJECT_NAME} "-framework OpenGL")
endif()

