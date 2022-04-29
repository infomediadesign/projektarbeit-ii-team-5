# Based on: https://vicrucann.github.io/tutorials/quick-cmake-doxygen/

# First we can indicate the documentation build as an option and set it to ON by default
option(BUILD_DOC "Build documentation" ON)

# Check if Doxygen is installed
find_package(Doxygen)
if (DOXYGEN_FOUND)
    # Set input and output files
    set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/../doxygen/Doxyfile.in)
    set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

    # Include doxygen-awesome.css
    file(DOWNLOAD
            https://raw.githubusercontent.com/jothepro/doxygen-awesome-css/main/doxygen-awesome.css
            ${CMAKE_CURRENT_BINARY_DIR}/doxygen-awesome.css)

    # Request to configure the file
    configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)
    message("Doxygen build started")

    # Note the option ALL which allows to build the docs together with the application
    add_custom_target(docs_doxygen ALL
            COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
            WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
            COMMENT "Generating API documentation with Doxygen"
            VERBATIM)
else (DOXYGEN_FOUND)
    message("Doxygen need to be installed to generate the doxygen documentation")
endif (DOXYGEN_FOUND)
