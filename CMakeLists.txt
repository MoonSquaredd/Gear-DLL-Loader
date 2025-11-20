cmake_minimum_required(VERSION 3.15)

project(Gear_DLL_Loader)

set(CMAKE_C_FLAGS "-m32")

set(SOURCES source/source.c)
file(GLOB_RECURSE HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/api/**.h")

add_library(DBGHELP SHARED ${SOURCES})

target_include_directories(DBGHELP
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/api>
)

if(MSVC)
    target_link_options(DBGHELP PRIVATE 
        /DEF:${CMAKE_CURRENT_SOURCE_DIR}/exports.def
    )
elseif(MINGW)
    target_sources(DBGHELP PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/exports.def
    )
endif()

target_sources(DBGHELP
    PUBLIC
    FILE_SET HEADERS
    TYPE HEADERS
    BASE_DIRS api
    FILES ${HEADERS}
)
