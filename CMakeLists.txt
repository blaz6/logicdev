cmake_minimum_required (VERSION 3.18)

project (logicdev)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -std=c++23 -l:discord_game_sdk.so")
set (source_dir "${PROJECT_SOURCE_DIR}/src/")

file (GLOB_RECURSE source_files
        "${source_dir}/*.cpp"
        "${source_dir}/discord/*.cpp"
        "${source_dir}/sources/*.cpp"
        )

add_executable (logicdev ${source_files})