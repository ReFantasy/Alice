aux_source_directory(. SRC_LIST)

qt_add_library(engine STATIC ${SRC_LIST} engine.h interface.h)

target_link_libraries(engine PRIVATE Qt${QT_VERSION_MAJOR}::Network)
target_include_directories(engine INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
