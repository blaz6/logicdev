cmake_minimum_required (VERSION 3.18)

project (logicdev)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -std=c++23")
set (source_dir "${PROJECT_SOURCE_DIR}/src/")

file (GLOB_RECURSE source_files
        "${source_dir}/*.cpp"
        "${source_dir}/discord/*.cpp"
        "${source_dir}/sources/*.cpp"
        )
add_subdirectory(lib/DPP)

add_executable (${PROJECT_NAME} ${source_files})
target_link_libraries(${PROJECT_NAME} dpp)
target_include_directories(${PROJECT_NAME} PRIVATE libs/DPP/include)
set_target_properties(${PROJECT_NAME} PROPERTIES
	CXX_STANDARD 23
	CXX_STANDARD_REQUIRED ON
)