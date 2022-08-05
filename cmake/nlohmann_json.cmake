include(FetchContent)

FetchContent_Declare(json
        URL "https://github.com/nlohmann/json/archive/refs/tags/v3.11.1.tar.gz"
)

FetchContent_GetProperties(json)
if(NOT json_POPULATED)
    set(JSON_BuildTests FALSE)
    FetchContent_Populate(json)
    add_subdirectory(${json_SOURCE_DIR} ${json_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()