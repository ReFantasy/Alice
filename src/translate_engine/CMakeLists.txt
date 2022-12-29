AUX_SOURCE_DIRECTORY(. SRC_LIST)

add_library(engine STATIC ${SRC_LIST} engine.h interface.h)

target_link_libraries(engine PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Gui
    Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Network )
