add_executable(tallis src/tallis.cc src/version.cc src/args.cc)
target_link_libraries(tallis PRIVATE libtallis)
set(GENERATED_HEADER_DIR ${CMAKE_CURRENT_BINARY_DIR}/generated_header)
configure_file(config.h.in ${GENERATED_HEADER_DIR}/config.h)
target_include_directories(tallis PRIVATE 
    "$<BUILD_INTERFACE:${GENERATED_HEADER_DIR}>"
    "$<INSTALL_INTERFACE:include>"
)

include(FetchContent)
FetchContent_Declare(
    CLI11
    SOURCE_DIR "${CMAKE_CURRENT_BINARY_DIR}/external/CLI11"
    DOWNLOAD_NO_EXTRACT TRUE
    URL "https://github.com/CLIUtils/CLI11/releases/latest/download/CLI11.hpp"
)
FetchContent_MakeAvailable(CLI11)
target_include_directories(tallis PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/external)
