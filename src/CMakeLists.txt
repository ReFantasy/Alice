add_subdirectory(translate_engine)
add_subdirectory(Preference)

set(PROJECT_SOURCES main.cpp mainwindow.cpp mainwindow.h)

if(APPLE)
  list(APPEND PROJECT_SOURCES
       ./Platform/global_clipboard_message_for_mac.h)
  list(APPEND PROJECT_SOURCES
       ./Platform/global_clipboard_message_for_mac.mm)
endif()

qt_add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})

target_link_libraries(
  ${PROJECT_NAME}
  PRIVATE engine
          preference
          Qt${QT_VERSION_MAJOR}::Core
          Qt${QT_VERSION_MAJOR}::Gui
          Qt${QT_VERSION_MAJOR}::Widgets
          Qt${QT_VERSION_MAJOR}::Network
          Qt6::Concurrent)

set_target_properties(${PROJECT_NAME} PROPERTIES WIN32_EXECUTABLE ON
                                                 MACOSX_BUNDLE ON)
