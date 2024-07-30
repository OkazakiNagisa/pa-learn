cmake_minimum_required(VERSION 3.23)
project("PAx")

find_package(SDL2 CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)

add_library(dbg_macro INTERFACE)
find_path(DBG_MACRO_INCLUDE_DIRS "dbg.h")
target_include_directories(dbg_macro INTERFACE ${DBG_MACRO_INCLUDE_DIRS})

add_executable(${PROJECT_NAME})
set_target_properties(${PROJECT_NAME} PROPERTIES C_STANDARD 23)
set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 23)
target_compile_options(${PROJECT_NAME} PRIVATE $<$<CXX_COMPILER_ID:MSVC>:/utf-8>)
target_link_libraries(${PROJECT_NAME} PRIVATE
    dbg_macro
    opengl32.lib
    imgui::imgui
    SDL2::SDL2
    SDL2::SDL2main
)
target_sources(${PROJECT_NAME} PRIVATE
    src/main.cpp
)