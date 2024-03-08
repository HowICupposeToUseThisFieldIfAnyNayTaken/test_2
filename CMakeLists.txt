cmake_minimum_required(VERSION 3.5)

project(test_2 LANGUAGES C)

add_executable(test_2 proto.c
    directives.h
    proto.h
    main.c
    directives.c)

include(GNUInstallDirs)
install(TARGETS test_2
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
