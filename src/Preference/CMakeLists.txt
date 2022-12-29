AUX_SOURCE_DIRECTORY(. SRC_LIST)

add_library(preference STATIC ${SRC_LIST} preference.h preference.ui)

target_link_libraries(preference PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Gui
    Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Network )
