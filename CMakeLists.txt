cmake_minimum_required(VERSION 2.8.11)

set(PROJECT iqAeroMapEditor)

project(${PROJECT})
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
find_package(Qt5Widgets REQUIRED)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/Modules)
find_package(GeographicLib REQUIRED)
include_directories(${GeographicLib_INCLUDE_DIR})

file(GLOB SOURCES . *.cpp)
file(GLOB HEADERS . *.h)
file(GLOB FORMS . *.ui)
file(GLOB RESOURCES . *.qrc)

qt5_wrap_ui(FORMS_HEADERS ${FORMS})
qt5_add_resources(RESOURCES_HEADERS ${RESOURCES})

add_executable(${PROJECT} ${SOURCES} ${FORMS_HEADERS} ${RESOURCES_HEADERS})

target_link_libraries(${PROJECT} Qt5::Widgets ${GeographicLib_LIBRARY})
