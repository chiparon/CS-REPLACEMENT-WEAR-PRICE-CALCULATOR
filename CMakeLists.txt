cmake_minimum_required(VERSION 3.16)
project(QTCPP_ALCHEMY)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_PREFIX_PATH "C:/Qt/6.9.0/mingw_64/lib/cmake")

# Enable Qt's automatic processing (Qt6 prefers AUTOUIC over qt_wrap_ui)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

# Qt6
find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)

# 源文件和头文件
set(SOURCES
        main.cpp
        src/IoTableDialog.cpp
)

set(HEADERS
        include/IoTableDialog.h
)

set(UIS
        ui/MainWindow.ui
)

# AUTOUIC will process UI files automatically, no qt_wrap_ui required

# 可执行文件
qt_add_executable(QTCPP_ALCHEMY
        ${SOURCES}
        ${HEADERS}
        ${UIS}
)

# 头文件目录
target_include_directories(QTCPP_ALCHEMY PRIVATE include)

# 链接 Qt 库
target_link_libraries(QTCPP_ALCHEMY PRIVATE Qt6::Core Qt6::Gui Qt6::Widgets)
