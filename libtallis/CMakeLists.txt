add_library(libtallis
    src/lt_init.cc
    src/lt_window.cc
    src/lt_instance.cc
    src/lt_engine.cc
    src/lt_callback.cc
    src/lt_input.cc
    src/lt_device.cc)

target_include_directories(libtallis
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

find_package(Vulkan REQUIRED)
target_include_directories(libtallis PRIVATE Vulkan::Headers)
target_link_libraries(libtallis PRIVATE Vulkan::Vulkan)

include(FetchContent)
FetchContent_Declare(
    GLFW
    SOURCE_DIR "${CMAKE_CURRENT_BINARY_DIR}/external/GLFW"
    GIT_REPOSITORY "https://github.com/glfw/glfw")
FetchContent_MakeAvailable(GLFW)
target_link_libraries(libtallis PUBLIC glfw)
target_include_directories(libtallis PUBLIC ${CMAKE_CURRENT_BINARY_DIR}/external)
