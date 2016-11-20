cmake_minimum_required(VERSION 2.8)
project(astartvisualizer)

find_package(Qt4 COMPONENTS QtCore QtGui REQUIRED)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")

include_directories(${QT_INCLUDES} ${CMAKE_CURRENT_BINARY_DIR})
include_directories(include/)

INCLUDE(${QT_USE_FILE})

set(AStartVisualizer_SRCS
    src/main.cpp
    src/mainwindow.cpp
    src/wastar.cpp
    src/zexception.cpp
    src/cell.cpp
    src/dnew.cpp
)

set(AStartVisualizer_HEADERS
    include/mainwindow.h
    include/wastar.h
    include/cell.h
    include/dnew.h
)

foreach(MOCheader ${AStartVisualizer_HEADERS})
    QT4_WRAP_CPP(MOCsrc ${MOCheader})
endforeach(MOCheader)

add_executable(${PROJECT_NAME} ${AStartVisualizer_SRCS} ${MOCsrc})
target_link_libraries(${PROJECT_NAME} ${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY})

install(TARGETS ${PROJECT_NAME}  RUNTIME DESTINATION bin)
