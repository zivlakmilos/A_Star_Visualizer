cmake_minimum_required(VERSION 2.6)
project(astartvisualizer)
find_package(Qt4 REQUIRED)

include_directories(${QT_INCLUDES} ${CMAKE_CURRENT_BINARY_DIR})
include_directories(include/)

set(AStartVisualizer_SRCS
	src/main.cpp
	src/mainwindow.cpp
)

qt4_automoc(${AStartVisualizer_SRCS})
add_executable(astartvisualizer ${AStartVisualizer_SRCS})
target_link_libraries(astartvisualizer ${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY})

install(TARGETS astartvisualizer RUNTIME DESTINATION bin)

