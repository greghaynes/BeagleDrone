PROJECT(beagledrone-gui)

SET(UI_SRCS
    ui/joysticksdialog.ui
    ui/mainwindow.ui)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt5Widgets REQUIRED)

qt5_wrap_ui(UI_HDRS ${UI_SRCS})

add_executable(beagledrone-gui main.cpp ${UI_HDRS})

target_link_libraries(beagledrone-gui Qt5::Widgets)

