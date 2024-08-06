cmake_minimum_required(VERSION 3.23)
project("PAx")

find_package(spdlog CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)
# find_package(Readline REQUIRED)
# find_package(LLVM CONFIG REQUIRED)

add_library(dbg_macro INTERFACE)
find_path(DBG_MACRO_INCLUDE_DIRS "dbg.h")
target_include_directories(dbg_macro INTERFACE ${DBG_MACRO_INCLUDE_DIRS})

add_executable(${PROJECT_NAME})
set_target_properties(${PROJECT_NAME} PROPERTIES C_STANDARD 23)
set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 23)
target_compile_options(${PROJECT_NAME} PRIVATE $<$<CXX_COMPILER_ID:MSVC>:/utf-8>)
target_link_libraries(${PROJECT_NAME} PRIVATE
    dbg_macro
    spdlog::spdlog
    glad::glad
    glfw
    imgui::imgui
)
target_sources(${PROJECT_NAME} PRIVATE
    src/main.cc
)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_LIST_DIR}/include)