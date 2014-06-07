cmake_minimum_required(VERSION 2.8)
project(libbbs)

set(PROJECT_VERSION_MAJOR "0")
set(PROJECT_VERSION_MINOR "0")
set(PROJECT_VERSION_PATCH "0")
set(PROJECT_VERSION "${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}")

include(CheckCCompilerFlag)
include(FindPkgConfig)
include(GNUInstallDirs)

if(${CMAKE_C_COMPILER_ID} STREQUAL "GNU" OR ${CMAKE_C_COMPILER_ID} STREQUAL "Clang")
    set(CMAKE_C_FLAGS "-g -O2 -Wall -Werror -fPIC -std=c99 ${CMAKE_C_FLAGS}")

    set(CMAKE_SHARED_LINKER_FLAGS "-Wl,--version-script=${PROJECT_SOURCE_DIR}/src/libbbs.ver ${CMAKE_SHARED_LINKER_FLAGS}")

    option(ENABLE_GCOV "Coverage support" false)
    if(ENABLE_GCOV)
        set(CMAKE_C_FLAGS "-coverage ${CMAKE_C_FLAGS}")
    endif()

    # Use NO_UNDEFINED=no when running with address sanitizer
    option(NO_UNDEFINED "No undefined symbol in object file" true)
    if(NO_UNDEFINED)
        set(saved_CMAKE_REQUIRED_FLAGS ${CMAKE_REQUIRED_FLAGS})
        set(CMAKE_REQUIRED_FLAGS "-Wl,--no-undefined")
        check_c_compiler_flag("" HAVE_NO_UNDEFINED)
        set(CMAKE_REQUIRED_FLAGS ${saved_CMAKE_REQUIRED_FLAGS})

        if(HAVE_NO_UNDEFINED)
            set(CMAKE_SHARED_LINKER_FLAGS "-Wl,--no-undefined ${CMAKE_SHARED_LINKER_FLAGS}")
        endif()
    endif()
endif()

set(pkgconfig_src ${PROJECT_SOURCE_DIR}/bbs.pc.in)
set(pkgconfig ${PROJECT_BINARY_DIR}/bbs.pc)
configure_file(${pkgconfig_src} ${pkgconfig})

# libbbs
include_directories(${PROJECT_SOURCE_DIR}/include)
file(GLOB bbs_inc ${PROJECT_SOURCE_DIR}/include/*)
file(GLOB bbs_src ${PROJECT_SOURCE_DIR}/src/*)
add_library(bbs SHARED ${bbs_src})
set_target_properties(${bbs} PROPERTIES
    SOVERSION 0
    VERSION 0.0.0
)

# testing
pkg_check_modules(CHECK check)

if ("${CHECK_FOUND}")
    include_directories(${CHECK_INCLUDE_DIRS})

    enable_testing()
    option(USE_VALGRIND "Use valgrind when testing" true)

    if (USE_VALGRIND)
        find_program(VALGRIND valgrind)
    endif()

    file(GLOB bbs_test_src ${PROJECT_SOURCE_DIR}/tests/*)

    foreach(test_src ${bbs_test_src})
        get_filename_component(test_name ${test_src} NAME_WE)
        add_executable(${test_name} ${test_src})
        target_link_libraries(${test_name} bbs ${CHECK_LIBRARIES} pthread)

        add_test(${test_name} ${test_name})
        if (VALGRIND)
            add_test("valgrind-${test_name}" ${VALGRIND} --error-exitcode=255 --leak-check=full ${PROJECT_BINARY_DIR}/${test_name})
        endif()
    endforeach()
endif()

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
