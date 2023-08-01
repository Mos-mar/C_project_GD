cmake_minimum_required(VERSION 3.5)

project(ProjetLibGD LANGUAGES C)
list(APPEND CMAKE_MODULE_PATH "/usr/include/")
find_package(gd)
add_executable(ProjetLibGD main.c)
target_link_libraries (ProjetLibGD gd m)


install(TARGETS ProjetLibGD
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}


  )
