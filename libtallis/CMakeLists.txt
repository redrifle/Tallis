add_library(libtallis
    src/lt_init.cc
    src/lt_window.cc
    src/lt_instance.cc
    src/lt_engine.cc
    src/lt_callback.cc
    src/lt_input.cc
    src/lt_device.cc
    src/lt_cleanup.cc
    src/lt_mem.cc
    src/lt_surface.cc
    src/lt_swapchain.cc
    src/vma_impl.cc
    src/lt_resource.cc)

target_include_directories(libtallis
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

find_package(Vulkan REQUIRED)
target_include_directories(libtallis PRIVATE Vulkan::Headers)
target_link_libraries(libtallis PUBLIC Vulkan::Vulkan)

include(FetchContent)
FetchContent_Declare(
    GLFW
    SOURCE_DIR "${CMAKE_CURRENT_BINARY_DIR}/external/GLFW"
    GIT_REPOSITORY "https://github.com/glfw/glfw")
FetchContent_MakeAvailable(GLFW)
target_link_libraries(libtallis PUBLIC glfw)

FetchContent_Declare(
    vma
    SOURCE_DIR "${CMAKE_CURRENT_BINARY_DIR}/external/vma"
    GIT_REPOSITORY "https://github.com/GPUOpen-LibrariesAndSDKs/VulkanMemoryAllocator")
FetchContent_MakeAvailable(vma)
set(VMA_BUILD_SAMPLES OFF CACHE INTERNAL "")
set(VMA_BUILD_DOCUMENTATION OFF CACHE INTERNAL "")
target_link_libraries(libtallis PUBLIC GPUOpen::VulkanMemoryAllocator)

target_include_directories(libtallis PUBLIC ${CMAKE_CURRENT_BINARY_DIR}/external)
