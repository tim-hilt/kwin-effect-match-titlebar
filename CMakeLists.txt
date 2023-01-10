cmake_minimum_required(VERSION 3.16)

project(kwin_effect_match_titlebar)

find_package(ECM REQUIRED NO_MODULE)

add_definitions (-Wall -Wunused -Werror)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_INCLUDE_WHAT_YOU_USE include-what-you-use)
set(CMAKE_CXX_CPPCHECK cppcheck)

set(CMAKE_MODULE_PATH
    ${CMAKE_MODULE_PATH}
    ${ECM_MODULE_PATH}
    ${ECM_KDE_MODULE_DIR}
    ${CMAKE_SOURCE_DIR}/cmake
    ${CMAKE_SOURCE_DIR}/cmake/Modules
)

include(KDEInstallDirs)
include(KDECMakeSettings)
include(KDECompilerSettings NO_POLICY_SCOPE)

add_subdirectory(src)

feature_summary(WHAT ALL)
