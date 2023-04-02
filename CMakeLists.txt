cmake_minimum_required(VERSION 3.5)

project(simple_example)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)

include_directories(${GTK3_INCLUDE_DIRS})

find_package(ImageMagick COMPONENTS Magick++ REQUIRED)
include_directories(${ImageMagick_INCLUDE_DIRS})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GTK_CFLAGS_OTHER}")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${GTK_LDFLAGS_OTHER} ${Magick++_LDFLAGS}")

set(SOURCES
    Image.cpp
    Image.h
    Watermark.cpp
    Watermark.h
    FileDialogProvide.cpp
    FileDialogProvide.h
    InputDegrees.cpp
    InputDegrees.h
    InputSize.cpp
    InputSize.h
    InputWindow.h
    main.cpp
)

add_executable(simple_example ${SOURCES})

target_link_libraries(simple_example ${GTK3_LIBRARIES} ${ImageMagick_LIBRARIES})