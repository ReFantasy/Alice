cmake_minimum_required(VERSION 3.5)

project(AliceTranslation VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)



find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Gui Widgets Network)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Gui Widgets Network)



IF (APPLE)
add_compile_options(-x objective-c++)
set(CMAKE_EXE_LINKER_FLAGS "-framework Cocoa -framework AppKit -framework CoreData -framework Foundation")
#include_directories("/opt/homebrew/opt/openssl@1.1/include")
#link_directories("/opt/homebrew/opt/openssl@1.1/lib")
#link_libraries(ssl crypto)
ENDIF ()

add_subdirectory(src)

