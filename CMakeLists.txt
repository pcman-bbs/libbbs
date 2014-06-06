cmake_minimum_required(VERSION 2.8)
project(libbbs)

set(PROJECT_VERSION_MAJOR "0")
set(PROJECT_VERSION_MINOR "0")
set(PROJECT_VERSION_PATCH "0")
set(PROJECT_VERSION "${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}")

include(GNUInstallDirs)

include_directories(${PROJECT_SOURCE_DIR}/include)
file(GLOB bbs_inc ${PROJECT_SOURCE_DIR}/include/*)
file(GLOB bbs_src ${PROJECT_SOURCE_DIR}/src/*)
add_library(bbs ${bbs_src})

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
