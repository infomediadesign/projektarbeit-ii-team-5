find_package(raylib_cpp QUIET)

if (NOT raylib_cpp_FOUND)
    include(FetchContent)
    FetchContent_Declare(
            raylib_cpp
            # Download a specific release
            URL https://github.com/RobLoach/raylib-cpp/archive/refs/tags/v4.1.0.zip
            # Or download current working state
            # URL https://github.com/RobLoach/raylib-cpp.git
    )
    FetchContent_MakeAvailable(raylib_cpp)
endif()
