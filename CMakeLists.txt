cmake_minimum_required( VERSION 3.22 )

project( midas )

set( CMAKE_C_STANDARD_REQUIRED ON )
set( CMAKE_C_STANDARD 99 )

set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin )

set( SOURCE_DIR ${CMAKE_SOURCE_DIR}/src )
set( SOURCES
    ${SOURCE_DIR}/main.c
)

add_executable( ${PROJECT_NAME} ${SOURCES} )

set_target_properties(
    ${PROJECT_NAME}
    PROPERTIES
        PREFIX vpr-
        SUFFIX .exe
)

install(
    TARGETS     ${PROJECT_NAME}
    DESTINATION ${CMAKE_INSTALL_PREFIX}/bin
)
