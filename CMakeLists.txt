cmake_minimum_required(VERSION 2.8.8)
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

    set(CMAKE_SHARED_LINKER_FLAGS "-Wl,--version-script=${PROJECT_SOURCE_DIR}/libbbs.ver ${CMAKE_SHARED_LINKER_FLAGS}")

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

add_library(bbs OBJECT
    ${bbs_inc}
    ${bbs_src}
)

add_library(bbs_shared SHARED
    $<TARGET_OBJECTS:bbs>
    ${PROJECT_SOURCE_DIR}/libbbs.ver
)
set_target_properties(bbs_shared PROPERTIES
    OUTPUT_NAME bbs
    SOVERSION 0
    VERSION 0.0.0
)

# testing
pkg_check_modules(CHECK check)

if ("${CHECK_FOUND}")
    include_directories(${CHECK_INCLUDE_DIRS} ${PROJECT_SOURCE_DIR}/src)

    enable_testing()
    option(USE_VALGRIND "Use valgrind when testing" true)

    add_custom_target(check COMMAND ${CMAKE_CTEST_COMMAND})

    if (USE_VALGRIND)
        find_program(VALGRIND valgrind)
    endif()

    file(GLOB test_api_src ${PROJECT_SOURCE_DIR}/tests/api/*)

    foreach(test_src ${test_api_src})
        get_filename_component(test_name ${test_src} NAME_WE)
        add_executable(${test_name} ${test_src})
        add_dependencies(check ${test_name})
        target_link_libraries(${test_name} bbs_shared ${CHECK_LIBRARIES} pthread)

        add_test(${test_name} ${test_name})
        if (VALGRIND)
            add_test("valgrind-${test_name}" ${VALGRIND} --error-exitcode=255 --leak-check=full --suppressions=${PROJECT_SOURCE_DIR}/valgrind.supp ${PROJECT_BINARY_DIR}/${test_name})
        endif()
    endforeach()

    file(GLOB test_private_src ${PROJECT_SOURCE_DIR}/tests/private/*)
    foreach(test_src ${test_private_src})
        get_filename_component(test_name ${test_src} NAME_WE)
        add_executable(${test_name} ${test_src} $<TARGET_OBJECTS:bbs>)
        add_dependencies(check ${test_name})
        target_link_libraries(${test_name} ${CHECK_LIBRARIES} pthread)

        add_test(${test_name} ${test_name})
        if (VALGRIND)
            add_test("valgrind-${test_name}" ${VALGRIND} --error-exitcode=255 --leak-check=full --suppressions=${PROJECT_SOURCE_DIR}/valgrind.supp ${PROJECT_BINARY_DIR}/${test_name})
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
