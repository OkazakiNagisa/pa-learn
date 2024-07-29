# add_subdirectory("${CMAKE_CURRENT_LIST_DIR}/SDL")
# find_package(SDL2)
include(FetchContent)
FetchContent_Declare(SDL2 SOURCE_DIR "${CMAKE_CURRENT_LIST_DIR}/SDL")
FetchContent_MakeAvailable(SDL2)

add_library(ImGui)
target_sources(ImGui PRIVATE
        "${CMAKE_CURRENT_LIST_DIR}/imgui/imgui/imgui.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/imgui/imgui/imgui_demo.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/imgui/imgui/imgui_draw.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/imgui/imgui/imgui_widgets.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/imgui/imgui/imgui_tables.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/imgui/imgui/backends/imgui_impl_sdl2.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/imgui/imgui/backends/imgui_impl_opengl3.cpp"
        )
target_link_libraries(ImGui PRIVATE SDL2::SDL2-static)
target_include_directories(ImGui PRIVATE "${CMAKE_CURRENT_LIST_DIR}/imgui/imgui")
target_include_directories(ImGui INTERFACE "${CMAKE_CURRENT_LIST_DIR}/imgui")
target_include_directories(ImGui INTERFACE "${CMAKE_CURRENT_LIST_DIR}/imgui/imgui") # compatibility