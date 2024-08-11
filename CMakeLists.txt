cmake_minimum_required(VERSION 3.10.0)

project(test)

set(CMAKE_DEBUG_POSTFIX d)
#add_library(compilter_flags INTERFACE)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_definitions(-DDEBUG)
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20")

find_package(Qt5 CONFIG REQUIRED COMPONENTS Core Widgets)

set( SOURCES
     src/main.cpp
     src/mainwindow.cpp )

set( HEADERS
     src/mainwindow.h )

set(APP_ICON_RESOURCE_WINDOWS "resources/resources.qrc")
add_executable(test ${SOURCES} ${HEADERS} ${APP_ICON_RESOURCE_WINDOWS})

set_target_properties( test PROPERTIES DEBUG_POSTFIX {CMAKE_DEBUG_POSTFIX} )

target_compile_options(test PRIVATE -Wall -Wextra -Wpedantic -pthread -Wno-unused-variable )

target_link_libraries(test Qt5::Widgets)
