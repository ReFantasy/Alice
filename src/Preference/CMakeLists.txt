aux_source_directory(. SRC_LIST)

qt_add_library(preference STATIC ${SRC_LIST} preference.h preference.ui)

target_link_libraries(
  preference
  PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Gui
          Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Network)

target_include_directories(preference INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
