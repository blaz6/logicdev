cmake_minimum_required (VERSION 3.24)

project (HelloWorld)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -std=c++23 -l:discord_game_sdk.so")
set (source_dir "${PROJECT_SOURCE_DIR}/src/")
add_compile_definitions (project_name PUBLIC PROJECT_NAME=HelloWorld)

file (GLOB_RECURSE source_files
        "${source_dir}/*.cpp"
        "${source_dir}/discord/*.cpp"
        "${source_dir}/sources/*.cpp"
        )

add_executable (HelloWorld ${source_files})
