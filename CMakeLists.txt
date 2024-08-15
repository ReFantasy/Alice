cmake_minimum_required(VERSION 3.5)

project(
  AliceTranslation
  VERSION 0.1
  LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# 设置编译命令导出选项 for neovim and clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(QT NAMES Qt6 REQUIRED COMPONENTS Core Gui Widgets Network
                                              Concurrent)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Gui Widgets
                                                       Network Concurrent)
qt_standard_project_setup()

if(APPLE)
  add_compile_options(-x objective-c++)
  set(CMAKE_EXE_LINKER_FLAGS
      "-framework Cocoa -framework AppKit -framework CoreData -framework Foundation"
  )
endif()

add_subdirectory(src)
