project(aui_server)

find_package(PkgConfig)

pkg_check_modules(GTKMM gtkmm-3.0) 

SET(CMAKE_C_COMPILER gcc-6)
SET(CMAKE_CXX_COMPILER g++-6)

add_subdirectory(src)

