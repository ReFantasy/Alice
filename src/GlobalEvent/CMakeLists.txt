
AUX_SOURCE_DIRECTORY(. SRC_LIST)

add_library(monitor STATIC ${SRC_LIST} monitor_event.h)

target_link_libraries(monitor PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Gui
    Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Network )
