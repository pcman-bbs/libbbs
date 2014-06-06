cmake_minimum_required(VERSION 2.8)
project(libbbs)

set(PROJECT_VERSION_MAJOR "0")
set(PROJECT_VERSION_MINOR "0")
set(PROJECT_VERSION_PATCH "0")
set(PROJECT_VERSION "${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}")

include(CheckCCompilerFlag)
include(GNUInstallDirs)

if(${CMAKE_C_COMPILER_ID} STREQUAL "GNU" OR ${CMAKE_C_COMPILER_ID} STREQUAL "Clang")
    set(CMAKE_C_FLAGS "-g -O2 -Wall -Werror -fPIC -std=c99 ${CMAKE_C_FLAGS}")

    option(ENABLE_GCOV "Coverage support" false)
    if(ENABLE_GCOV)
        set(CMAKE_C_FLAGS "-coverage ${CMAKE_C_FLAGS}")
    endif()

    check_c_compiler_flag(-fvisibility=hidden FVISIBILITY_HIDDEN)
    if(${FVISIBILITY_HIDDEN})
        set(CMAKE_C_FLAGS "-fvisibility=hidden ${CMAKE_C_FLAGS}")
    endif()
endif()

include_directories(${PROJECT_SOURCE_DIR}/include)
file(GLOB bbs_inc ${PROJECT_SOURCE_DIR}/include/*)
file(GLOB bbs_src ${PROJECT_SOURCE_DIR}/src/*)
add_library(bbs SHARED ${bbs_src})
set_target_properties(${bbs} PROPERTIES
    SOVERSION 0
    VERSION 0.0.0
)

set(pkgconfig_src ${PROJECT_SOURCE_DIR}/bbs.pc.in)
set(pkgconfig ${PROJECT_BINARY_DIR}/bbs.pc)
configure_file(${pkgconfig_src} ${pkgconfig})

# install
install(FILES ${bbs_inc} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/bbs)
install(FILES ${pkgconfig} DESTINATION ${CMAKE_INSTALL_LIBDIR}/pkgconfig)
install(TARGETS ${bbs} DESTINATION ${CMAKE_INSTALL_LIBDIR})

# package
set(CPACK_SOURCE_GENERATOR TGZ)
set(CPACK_SOURCE_IGNORE_FILES "^${PROJECT_SOURCE_DIR}/.git")

set(CPACK_PACKAGE_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${PROJECT_VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH ${PROJECT_VERSION_PATCH})

include(CPack)
