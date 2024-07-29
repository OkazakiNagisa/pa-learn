cmake_minimum_required(VERSION 3.23)
project("PAx")

add_subdirectory(third_party)

add_executable(${PROJECT_NAME})
set_target_properties(${PROJECT_NAME} PROPERTIES C_STANDARD 23)
set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 23)
target_compile_options(${PROJECT_NAME} PRIVATE $<$<CXX_COMPILER_ID:MSVC>:/utf-8>)
target_link_libraries(${PROJECT_NAME} PRIVATE
    ImGui
    SDL2::SDL2-static
    opengl32.lib
    SDL2::SDL2main
)
target_sources(${PROJECT_NAME} PRIVATE
    src/main.cpp
)