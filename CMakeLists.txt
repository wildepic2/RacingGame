cmake_minimum_required(VERSION 4.2)
project(RacingGame C)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)

#Automatically generate GitHub Actions Workflow
set(WORKFLOW_PATH "${CMAKE_SOURCE_DIR}/.github/workflows/build.yml")
set(WORKFLOW_CONTENT [=[
name: Build and Package

on:
  push:
    branches: [ "master" ]
  pull_request:
    branches: [ "master" ]

jobs:
  build:
    strategy:
      matrix:
        os: [ubuntu-latest, windows-latest]
        include:
          - os: ubuntu-latest
            artifact_name: RacingGame-linux-v${{ github.run_number }}
            executable_name: RacingGame
          - os: windows-latest
            artifact_name: RacingGame-windows-v${{ github.run_number }}
            executable_name: RacingGame.exe

    runs-on: ${{ matrix.os }}

    steps:
    - uses: actions/checkout@v4

    # This step ensures CMake 4.2 is installed regardless of the runner's default
    - name: Setup CMake 4.2
      uses: lukka/get-cmake@latest
      with:
        cmakeVersion: 4.2.0

    - name: Install Linux Dependencies
      if: runner.os == 'Linux'
      run: |
        sudo apt-get update
        sudo apt-get install -y libasound2-dev libx11-dev libxinerama-dev libxcursor-dev libxi-dev libxrandr-dev libgl1-mesa-dev libglu1-mesa-dev

    - name: Configure CMake
      run: cmake -B build -DCMAKE_BUILD_TYPE=Release

    - name: Build
      run: cmake --build build --config Release

    - name: Prepare Package Folder
      run: |
        mkdir dist
        if [ "${{ runner.os }}" == "Windows" ]; then
          cp build/Release/${{ matrix.executable_name }} dist/
        else
          cp build/${{ matrix.executable_name }} dist/
        fi
        if [ -d "assets" ]; then cp -r assets dist/; fi
      shell: bash

    - name: Upload Artifacts
      uses: actions/upload-artifact@v4
      with:
        name: ${{ matrix.artifact_name }}
        path: dist/
]=])

# Create the .github/workflows directory and write the file
file(MAKE_DIRECTORY "${CMAKE_SOURCE_DIR}/.github/workflows")
file(WRITE ${WORKFLOW_PATH} "${WORKFLOW_CONTENT}")
message(STATUS "GitHub Workflow generated at: ${WORKFLOW_PATH}")

# 1. Define the path and the content of the main file
set(MAIN_FILE "${CMAKE_SOURCE_DIR}/src/main.c")
set(MAIN_CODE [=[
#include "raylib.h"

int main(void)
{
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Changeme!");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("Hello World!", 350, 200, 20, BLACK);
        DrawFPS(10, 10);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
]=])

#Create the directory and the file if it doesn't exist
if(NOT EXISTS ${MAIN_FILE})
    file(MAKE_DIRECTORY "${CMAKE_SOURCE_DIR}/src")
    file(MAKE_DIRECTORY "${CMAKE_SOURCE_DIR}/assets")
    file(WRITE ${MAIN_FILE} "${MAIN_CODE}")
    message(STATUS "Generated missing source file: ${MAIN_FILE}")
endif()

# 3. Raylib Setup (FetchContent)
include(FetchContent)
set(RAYLIB_VERSION 5.5)
FetchContent_Declare(
        raylib
        URL https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.tar.gz
        DOWNLOAD_EXTRACT_TIMESTAMP ON
)

set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(raylib)

# 4. Build Configuration
add_executable(${PROJECT_NAME} ${MAIN_FILE}
        src/state.h
        src/menuManager.c
        src/menuManager.h
        src/gameManager.c
        src/gameManager.h
        src/state.c)
target_link_libraries(${PROJECT_NAME} PRIVATE raylib)

# Compiler Warnings
if (MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /W4)
else()
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic)
endif()

#Optional: assets-Ordner neben die ausführbare Datei kopieren
if(EXISTS "${CMAKE_SOURCE_DIR}/assets")
    add_custom_command(
            TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${CMAKE_SOURCE_DIR}/assets"
            "$<TARGET_FILE_DIR:${PROJECT_NAME}>/assets"
            COMMENT "Copying assets to output directory"
    )
endif()